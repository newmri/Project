#include "stdafx.h"
#include "Unit.h"
#include "Tile.h"
#include "Structure.h"

void CUnit::Init()
{
	m_eCurrId = UNIT::IDLE;

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);
	m_tAnimationInfo = new ANIMATION_INFO[pAnim->nStateNum];
	for (int i = 0; i < pAnim->nStateNum; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(m_tAnimationInfo[i]));

	m_tInfo.fSpeed = TILE_SIZE / 2.f;
	m_bMove = false;
	m_tInfo.fAngle = BOTTOM;
	m_nMaxAttackCnt = 10;
	m_pControlTarget = nullptr;
	m_bIsRetunning = false;

	m_eCommand = BASIC;

	m_dwBuildTime = 0;
	m_nBuildCnt = 0;
}

void CUnit::LateInit()
{
	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);
	// Set Animation Name
	for (int i = 0; i < pAnim->nStateNum; ++i) {
	
		m_tAnimationInfo[i].tName = new char*[pAnim[i].nAnimationNum];
		ZeroMemory(m_tAnimationInfo[i].tName, pAnim[i].nAnimationNum);

		for (int j = 0; j < pAnim[i].nAnimationNum; ++j) {

			m_tAnimationInfo[i].tName[j] = new char[STR_LEN];
			strcpy_s(m_tAnimationInfo[i].tName[j], strlen(m_tAnimationInfo[i].tName[j]), pAnim[i].tName[j]);
			m_tAnimationInfo[i].nAnimationNum = pAnim[i].nAnimationNum;
			m_tAnimationInfo[i].nImageW = pAnim[i].nImageW;
			m_tAnimationInfo[i].nImageH = pAnim[i].nImageH;
			m_tAnimationInfo[i].dwAnimationTime = GetTickCount();
			m_tAnimationInfo[i].nCnt = 0;

		}

	}

	UpdateRect();

	// Swap Tail
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	m_tSelectRect.left = m_tRect.left + fScrollX + TILE_SIZE;
	m_tSelectRect.top = (m_tRect.top + fScrollY) + TILE_SIZE;
	m_tSelectRect.right = m_tSelectRect.left + TILE_SIZE;
	m_tSelectRect.bottom = m_tSelectRect.top + TILE_SIZE;

	INTPOINT pos;
	pos.x = m_tSelectRect.left;
	pos.y = m_tSelectRect.top;

	m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);

	for (int posY = m_tSelectRect.top; posY < m_tSelectRect.bottom; posY += TILE_SIZE) {

		for (int posX = m_tSelectRect.left; posX < m_tSelectRect.right; posX += TILE_SIZE) {

			int x = (posX - static_cast<int>(fScrollX)) / TILE_SIZE;
			int y = (posY - static_cast<int>(fScrollY)) / TILE_SIZE;
			int k = TILEMANAGER->GetTileNum().x;
			int nIdx = x + TILEMANAGER->GetTileNum().x * y;

			CObj* pTile = TILEMANAGER->SelectTile(nIdx);

			if (nullptr == pTile) return;

			dynamic_cast<CTile*>(pTile)->SetTileUnMovable();
		}
	}

	m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 10);
	m_tAnimationInfo[m_eCurrId].nCnt -= 2;


	// Command Icon
	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(SCV_COMMAND_ICON);
	FLOATPOINT tPos(0.795f, 0.875f);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		COMMAND_INFO* pTemp = new COMMAND_INFO;
		memcpy(&pTemp->tImage.tInfo, &p[i], sizeof(IMAGE_INFO));

		pTemp->tImage.tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * tPos.fX);
		pTemp->tImage.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * tPos.fY);
		pTemp->tImage.tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.05f);
		pTemp->tImage.tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.025);
		pTemp->tImage.tColor = RGB(0, 0, 0);

		pTemp->tClickArea.x = pTemp->tImage.tPos.x + pTemp->tImage.tDrawSize.x;
		pTemp->tClickArea.y = pTemp->tImage.tPos.y + pTemp->tImage.tDrawSize.y;

		if (i & 1) {
			pTemp->bRender = true;
			tPos.fX += 0.070f;
		}
	

		if (((i + 1) % 6) == 0) {
			tPos.fX = 0.795f;
			tPos.fY += 0.04f;
		}
		if (9 == i) {
			tPos.fX = 0.795f;
			tPos.fY += 0.04f;
		}
		if (9 < i) {
			pTemp->bRender = true;
			tPos.fX += 0.070f;

		}


		m_commandList.push_back(pTemp);
	}



	// Basic Build
	 p = BITMAPMANAGER->GetImageInfo(SCV_BASIC_BUILD_ICON);
	 tPos.fX = 0.795f;
	 tPos.fY = 0.875f;
	for (int i = 0; i < p[0].nImageNum; ++i) {
		BUILD_INFO* pTemp = new BUILD_INFO;
		memcpy(&pTemp->tImage.tInfo, &p[i], sizeof(IMAGE_INFO));

		pTemp->tImage.tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * tPos.fX);
		pTemp->tImage.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * tPos.fY);
		pTemp->tImage.tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.05f);
		pTemp->tImage.tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.025);
		pTemp->tImage.tColor = RGB(0, 0, 0);

		pTemp->tClickArea.x = pTemp->tImage.tPos.x + pTemp->tImage.tDrawSize.x;
		pTemp->tClickArea.y = pTemp->tImage.tPos.y + pTemp->tImage.tDrawSize.y;

		if (i & 1) tPos.fX += 0.070f;
		


		if (((i + 1) % 6) == 0) {
			tPos.fX = 0.795f;
			tPos.fY += 0.04f;
		}

		m_buildList[0].push_back(pTemp);
	}
	m_buildList[0][1]->nMineCost = 400;
	m_buildList[0][3]->nMineCost = 100;
	m_buildList[0][5]->nMineCost = 150;
	m_buildList[0][7]->nMineCost = 125;
	m_buildList[0][9]->nMineCost = 100;
	m_buildList[0][11]->nMineCost = 75;
	m_buildList[0][13]->nMineCost = 150;


	p = BITMAPMANAGER->GetImageInfo(BARRACK_BUILD);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		STATIC_UI_IMAGE_INFO* pInfo = new STATIC_UI_IMAGE_INFO;

		memcpy(&pInfo->tInfo, &p[i], sizeof(IMAGE_INFO));
		m_buildImageList[BARRACK].push_back(pInfo);

	}
}

int CUnit::Update()
{
	CObj::LateInit();

	Move();
	Attack();
	Build();
	return 0;
}

void CUnit::LateUpdate()
{
}

void CUnit::Render()
{
	if (0 == m_tAnimationInfo[m_eCurrId].nImageW) return;

	UpdateRect();
	HDC hDC = RENDERMANAGER->GetMemDC();


	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(hDC,
		static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
		static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));

	if(m_bBuild)
	BITMAPMANAGER->GetImage()[m_buildImageList[m_eBuildId][m_nBuildCnt]->tInfo.szName]->TransparentBlt(hDC,
		m_BuildPos.x - TILE_SIZE,
		m_BuildPos.y - TILE_SIZE / 2,
		m_buildImageList[m_eBuildId][m_nBuildCnt]->tInfo.nImageW,
		m_buildImageList[m_eBuildId][m_nBuildCnt]->tInfo.nImageH,
		0,
		0,
		m_buildImageList[m_eBuildId][m_nBuildCnt]->tInfo.nImageW,
		m_buildImageList[m_eBuildId][m_nBuildCnt]->tInfo.nImageH, RGB(0, 0, 0));


}

void CUnit::Release()
{
}

bool CUnit::CheckCommand(POINT tMousePos)
{
	int nCnt = 0;
	if (BASIC == m_eCommand) {
		for (auto& d : m_commandList) {

			if (tMousePos.x >= d->tImage.tPos.x && tMousePos.x <= d->tClickArea.x &&
				tMousePos.y >= d->tImage.tPos.y && tMousePos.y <= d->tClickArea.y) {
				if (!strcmp(d->tImage.tInfo.szName, "ScvCommand10")) {
					m_eCommand = BASIC_BUILD;
				}
				nCnt++;

				return true;

			}
		}
	}

	else{
		for (auto& d : m_buildList[m_eCommand]) {

			if (tMousePos.x >= d->tImage.tPos.x && tMousePos.x <= d->tClickArea.x &&
				tMousePos.y >= d->tImage.tPos.y && tMousePos.y <= d->tClickArea.y) {

				// Barrack
				if (!strcmp(d->tImage.tInfo.szName, "BasicBuild06")) {
					MOUSEMANAGER->SetBuild(BARRACK);
				}

				else if (!strcmp(d->tImage.tInfo.szName, "BasicBuild16")) m_eCommand = BASIC;
				

				return true;

			}
		}
	}

	return false;
}

void CUnit::RenderUI()
{
	HDC hDC = RENDERMANAGER->GetMemDC();
	if (BASIC == m_eCommand) {
		for (auto& d : m_commandList) {
			if (d->bRender)
				BITMAPMANAGER->GetImage()[d->tImage.tInfo.szName]->TransparentBlt(hDC,
					d->tImage.tPos.x,
					d->tImage.tPos.y,
					d->tImage.tDrawSize.x,
					d->tImage.tDrawSize.y,
					0,
					0,
					d->tImage.tInfo.nImageW,
					d->tImage.tInfo.nImageH, d->tImage.tColor);

		}
	}
	else {
		for (auto& d : m_buildList[m_eCommand]) {
			if (d->nMineCost <= SCENEMANAGER->GetReSourcesValue(MINE))
				BITMAPMANAGER->GetImage()[d->tImage.tInfo.szName]->TransparentBlt(hDC,
					d->tImage.tPos.x,
					d->tImage.tPos.y,
					d->tImage.tDrawSize.x,
					d->tImage.tDrawSize.y,
					0,
					0,
					d->tImage.tInfo.nImageW,
					d->tImage.tInfo.nImageH, d->tImage.tColor);

		}


	}
}

void CUnit::Move()
{
	if (!m_route.empty()) {
		m_commandList[0]->bRender = true;
		m_commandList[1]->bRender = false;

		m_eCurrId = UNIT::IDLE;

		// Rotate
		m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 10);
		if (360 == m_tInfo.fAngle) m_tAnimationInfo[m_eCurrId].nCnt -= 3;
		else m_tAnimationInfo[m_eCurrId].nCnt -= 1;


		float x = cosf(m_tInfo.fAngle * PI / 180.f) * m_tInfo.fSpeed;
		float y = sinf(m_tInfo.fAngle * PI / 180.f) * m_tInfo.fSpeed;


		INTPOINT pos;
		pos.x = m_tSelectRect.left;
		pos.y = m_tSelectRect.top;
		m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);

		m_nBoforeIdx = m_tSelectRectIdx.x + TILEMANAGER->GetTileNum().x * m_tSelectRectIdx.y;
		if (!dynamic_cast<CTile*>(TILEMANAGER->SelectTile(m_nBoforeIdx))->IsClickable())
			TILEMANAGER->SetTileMovable(m_nBoforeIdx);

		if (m_cnt < m_maxCnt) {

			if (m_dwTime + 10 < GetTickCount()) {
				m_tInfo.tPos.fX += m_tMovePos.fX;
				m_tInfo.tPos.fY += m_tMovePos.fY;
				m_tSelectRect.left += m_tMovePos.fX;
				m_tSelectRect.right += m_tMovePos.fX;
				m_tSelectRect.top += m_tMovePos.fY;
				m_tSelectRect.bottom += m_tMovePos.fY;
				m_dwTime = GetTickCount();
				m_cnt++;
			}

		}
		else {

			int nIdx = m_tSelectRectIdx.x + TILEMANAGER->GetTileNum().x * m_tSelectRectIdx.y;
			TILEMANAGER->SetTileUnMovable(nIdx);

			m_route.pop_front();
			if (m_route.empty()) {
				m_commandList[0]->bRender = false;
				m_commandList[1]->bRender = true;
				if (m_bIsRetunning) {
					SCENEMANAGER->UpdateResourcesValue(MINE, 5);
					// Return to mineral
					m_bIsRetunning = false;
					m_nAttackAnim = 1;
					m_dwAttackTime = GetTickCount();
					m_nAttackCnt = 0;

					INTPOINT src;
					src.x = m_tSelectRect.left;
					src.y = m_tSelectRect.top;

					INTPOINT dest[3];

					for (int i = 0; i < 3; ++i) dest[i] = m_tReturnPos;

					node_t* node[4];

					// L B R
					dest[0].x -= TILE_SIZE;
					dest[1].y += TILE_SIZE;
					dest[2].x += TILE_SIZE;

					for (int i = 0; i < 3; ++i) {
						node[i] = PATHMANAGER->FindPath(src, dest[i]);
					}


					for (int i = 0; i < 3; ++i) {
						if (0 > node[i]->value_factor) node[i]->value_factor = 999;
					}

					int min = node[0]->value_factor;

					for (int i = 0; i < 3; ++i) {
						if (min > node[i]->value_factor) min = node[i]->value_factor;
					}


					for (int j = 0; j < 3; ++j) {
						if (min == node[j]->value_factor) {
							node[j] = PATHMANAGER->FindPath(src, dest[j]);
							SetMove(node[j]);
							float fAngle;
							if (0 == j) fAngle = RIGHT;
							else if (1 == j) fAngle = TOP;
							else if (2 == j) fAngle = LEFT;


							SetAttack(m_tReturnPos, fAngle);

							return;


						}
					}

				
				}
				// Attack
				if (m_bAttack) {
					m_eCurrId = UNIT::ATTACK;
					m_bAttack = false;
					m_tInfo.fAngle = m_fAttackAngle;
					int angle = m_tInfo.fAngle;
					angle = static_cast<int>(m_tInfo.fAngle);
					switch (angle) {
					case TOP: m_tAnimationInfo[m_eCurrId].nCnt = 8; break;
					case LEFT: m_tAnimationInfo[m_eCurrId].nCnt = 16; break;
					case RIGHT: m_tAnimationInfo[m_eCurrId].nCnt = 0; break;

					}

					m_nAttackAnim = 1;
					m_dwAttackTime = GetTickCount();
					m_nAttackCnt = 0;
					OBJLIST p = OBJMANAGER->GetObj(CONTROL);
					m_pControlTarget = p.front();
					
				}

				// Build
				if (m_bBuild) {
					m_eCurrId = UNIT::BUILD;

					m_tInfo.fAngle = m_fAttackAngle;
					int angle = m_tInfo.fAngle;
					angle = static_cast<int>(m_tInfo.fAngle);
					switch (angle) {
					case TOP: m_tAnimationInfo[m_eCurrId].nCnt = 8; break;
					case LEFT: m_tAnimationInfo[m_eCurrId].nCnt = 16; break;
					case RIGHT: m_tAnimationInfo[m_eCurrId].nCnt = 0; break;

					}

					m_nAttackAnim = 1;
					m_dwBuildTime = GetTickCount();
					m_dwAttackTime = GetTickCount();

					m_nAttackCnt = 0;
				}
				return;
			}
			pos.x = m_tSelectRect.left;
			pos.y = m_tSelectRect.top;

			INTPOINT idx = TILEMANAGER->GetIndex(pos);

			FLOATPOINT tSrc(static_cast<float>(idx.x * TILE_SIZE), static_cast<float>(idx.y * TILE_SIZE));
			FLOATPOINT tDest(static_cast<float>(m_route.front().x * TILE_SIZE), static_cast<float>((m_route.front().y * TILE_SIZE)));

			int angle = m_tInfo.fAngle;

			m_tInfo.fAngle = MATHMANAGER->CalcDegree(tDest, tSrc);

			float _Height = (float)abs(idx.y * TILE_SIZE - m_route.front().y * TILE_SIZE); // 현재 캐릭터의 좌표와 마우스와의 좌표 사이의 높이를 구해준다. 
			float _Bottom = (float)abs(idx.x * TILE_SIZE - m_route.front().x * TILE_SIZE); // 현재 캐릭터의 좌표와 마우스와의 좌표 사이의 밑변의 길이를 구해준다. 
			float _R = sqrt((_Height*_Height) + (_Bottom*_Bottom)); // 빗변을 구하는 공식. 
																	// 길이 = 속도(이동픽셀) * 시간 =&gt; 시간 = 길이 / 이동 픽셀 

			m_maxCnt = _R / m_tInfo.fSpeed;

			m_tMovePos.fX = _Bottom / m_maxCnt;
			m_tMovePos.fY = _Height / m_maxCnt;

			angle = m_tInfo.fAngle;


			if (angle == TOP) m_tMovePos.fY = -m_tMovePos.fY;
			else if (angle == LEFT) m_tMovePos.fX = -m_tMovePos.fX;
			else if (angle > TOP && angle < LEFT) {
				m_tMovePos.fX = -m_tMovePos.fX;
				m_tMovePos.fY = -m_tMovePos.fY;


			}
			else if (angle > LEFT && angle < BOTTOM) m_tMovePos.fX = -m_tMovePos.fX;


			else if (angle > 0 && angle < TOP) m_tMovePos.fY = -m_tMovePos.fY;

			m_dwTime = GetTickCount();
			m_cnt = 0;

			return;

		}


	}
}

void CUnit::Attack()
{
	if (UNIT::ATTACK == m_eCurrId && m_dwAttackTime + 50 < GetTickCount()) {

		if (m_nAttackCnt == m_nMaxAttackCnt) {
			m_eCurrId = UNIT::IDLE;
			m_nAttackAnim = 1;
			INTPOINT src;
			src.x = m_tSelectRect.left;
			src.y = m_tSelectRect.top;
			INTPOINT dest;
			dest.x = m_pControlTarget->GetSelectRect().left + TILE_SIZE * 2;
			dest.y = m_pControlTarget->GetSelectRect().top - TILE_SIZE;
			SetMove(PATHMANAGER->FindPath(src, dest));
			m_bIsRetunning = true;
			return;
		}

		m_dwAttackTime = GetTickCount();
		m_tAnimationInfo[m_eCurrId].nCnt += m_nAttackAnim;
		m_nAttackAnim = -m_nAttackAnim;
		m_nAttackCnt++;
	}




}

void CUnit::Build()
{
	if (m_bBuild && UNIT::BUILD == m_eCurrId && m_dwAttackTime + 50 < GetTickCount()) {

		if (m_dwBuildTime + 500 < GetTickCount()) {
			m_dwBuildTime = GetTickCount();
			++m_nBuildCnt;

		}
		if (m_nBuildCnt == 4) {
			m_eCurrId = UNIT::IDLE;
			m_nAttackAnim = 1;
			m_nBuildCnt = 0;
			m_bBuild = false;
			switch (m_eBuildId) {
			case BARRACK:
				CObj* pObj = CFactoryManager<CStructure>::CreateObj(GREEN, BARRACK, PORTRAIT::ADVISOR,
					UNIT::LARGE_WIRE::BARRACK, UNIT_SELECT9, FLOATPOINT(m_BuildPos.x, m_BuildPos.y), 1000);
				
				OBJMANAGER->AddObject(pObj, BARRACK);
				break;

			}

			return;

		}

		m_dwAttackTime = GetTickCount();
		m_tAnimationInfo[m_eCurrId].nCnt += m_nAttackAnim;
		m_nAttackAnim = -m_nAttackAnim;
		m_nAttackCnt++;
	}


}

void CUnit::UpdateRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tAnimationInfo[m_eCurrId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tAnimationInfo[m_eCurrId].nImageH);
}
