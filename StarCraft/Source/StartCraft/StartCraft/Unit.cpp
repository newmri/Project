#include "stdafx.h"
#include "Unit.h"
#include "Tile.h"
#include "Structure.h"

void CUnit::Init()
{
	m_eCurrId = UNIT::MOVE;

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);
	m_tAnimationInfo = new ANIMATION_INFO[pAnim->nStateNum];
	for (int i = 0; i < pAnim->nStateNum; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(m_tAnimationInfo[i]));

	m_tInfo.fSpeed = TILE_SIZE / 2.f;
	m_bMove = false;
	m_tInfo.fAngle = BOTTOM;
	m_nMaxAttackCnt = 10;

	m_bAttack = false;
	m_tReturnPos.x = -1;

	m_pTarget = nullptr;

	nAnimationCnt = -1;
	m_dwAttackTime = 0;
	m_nEffectIdx = 0;
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

	m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fMoveAnimDivide);


	// Command Icon
	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(MARINE_COMMAND_ICON);
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


	// Effect
	if(MARINE == m_tInfo.eObjId) p = BITMAPMANAGER->GetImageInfo(MARINE_EFFECT);
	else if (GHOST == m_tInfo.eObjId) p = BITMAPMANAGER->GetImageInfo(GHOST_EFFECT);

	for (int i = 0; i < p[0].nImageNum; ++i) {
		STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;
		memcpy(&pTemp->tInfo, &p[i], sizeof(IMAGE_INFO));
		pTemp->tColor = RGB(0, 0, 0);
		pTemp->tDrawSize.x = pTemp->tInfo.nImageW;
		pTemp->tDrawSize.y = pTemp->tInfo.nImageH;

		m_effectList.push_back(pTemp);
	}
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


	if (UNIT::ATTACK == m_eCurrId) {

		m_nEffectIdx = (m_nEffectIdx + 1) % m_effectList[0]->tInfo.nImageNum;
		BITMAPMANAGER->GetImage()[m_effectList[m_nEffectIdx]->tInfo.szName]->TransparentBlt(hDC,
			m_tAttackTargetPos.x + SCROLLMANAGER->GetScrollX(),
			m_tAttackTargetPos.y + SCROLLMANAGER->GetScrollY(),
			m_effectList[m_nEffectIdx]->tDrawSize.x,
			m_effectList[m_nEffectIdx]->tDrawSize.y,
			0,
			0,
			m_effectList[m_nEffectIdx]->tInfo.nImageW,
			m_effectList[m_nEffectIdx]->tInfo.nImageH, m_effectList[m_nEffectIdx]->tColor);
	}

}

void CUnit::Release()
{
}



void CUnit::RenderUI()
{
	HDC hDC = RENDERMANAGER->GetMemDC();
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

void CUnit::Move()
{
	if (!m_route.empty()) {
		m_eCurrId = UNIT::MOVE;
		m_commandList[0]->bRender = true;
		m_commandList[1]->bRender = false;


		if (-1 == nAnimationCnt) {
			m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fMoveAnimDivide);
			nAnimationCnt = m_tAnimationInfo[m_eCurrId].nCnt + 8;

		}


		INTPOINT pos;
		pos.x = m_tSelectRect.left;
		pos.y = m_tSelectRect.top;
		m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);

		m_nBoforeIdx = m_tSelectRectIdx.x + TILEMANAGER->GetTileNum().x * m_tSelectRectIdx.y;
		if (!dynamic_cast<CTile*>(TILEMANAGER->SelectTile(m_nBoforeIdx))->IsClickable())
			TILEMANAGER->SetTileMovable(m_nBoforeIdx);
		if (m_cnt < m_maxCnt) {

			if (m_dwTime + 10 < GetTickCount()) {
				m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % nAnimationCnt;
				if (m_tAnimationInfo[m_eCurrId].nCnt > 124) m_tAnimationInfo[m_eCurrId].nCnt = 124;
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
				m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fMoveAnimDivide);
				nAnimationCnt = -1;

				if (m_bAttack) {
					SetAttack();
					m_bAttack = false;
				}
				return;
			}
			pos.x = m_tSelectRect.left;
			pos.y = m_tSelectRect.top;

			INTPOINT idx = TILEMANAGER->GetIndex(pos);

			FLOATPOINT tSrc(static_cast<float>(idx.x * TILE_SIZE), static_cast<float>(idx.y * TILE_SIZE));
			FLOATPOINT tDest(static_cast<float>(m_route.front().x * TILE_SIZE), static_cast<float>((m_route.front().y * TILE_SIZE)));


			m_tInfo.fAngle = MATHMANAGER->CalcDegree(tDest, tSrc);
			int angle = m_tInfo.fAngle;

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

			m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fMoveAnimDivide);
			nAnimationCnt = m_tAnimationInfo[m_eCurrId].nCnt + 8;

			return;

		}


	}
}

void CUnit::Attack()
{
	if (KEYMANAGER->KeyDown('A')) MOUSEMANAGER->ChangeCursor(TARGY);



	if (UNIT::ATTACK == m_eCurrId) {
		if (-1 == nAnimationCnt) {
			nAnimationMinNum = m_tAnimationInfo[m_eCurrId].nCnt;
			nAnimationCnt = nAnimationMinNum + 3;
			m_nEffectIdx = 0;
		}
		if (m_dwAttackTime + 150 < GetTickCount()) {
			if (++m_tAnimationInfo[m_eCurrId].nCnt > nAnimationCnt) {
				m_tAnimationInfo[m_eCurrId].nCnt = nAnimationMinNum;
				if (0 < m_pTarget->GetStat().nHP) m_pTarget->SetDamage(30);
				else {
					m_pTarget = nullptr;
					m_eCurrId = UNIT::MOVE;
					m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fMoveAnimDivide);
					return;
				}

			}
			m_dwAttackTime = GetTickCount();
		}
	}

}

bool CUnit::Die()
{
	if (0 >= m_tStat.nHP) {
		m_eCurrId = UNIT::DIE;
		m_tStat.nHP = 0;
		if (m_tAnimationInfo[m_eCurrId].nCnt < m_tAnimationInfo[m_eCurrId].nAnimationNum - 1) {
			m_tAnimationInfo[m_eCurrId].nCnt++;
		}
		else {

			MOUSEMANAGER->ReSetSelectUnit();
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

					if (nullptr == pTile) return true;

					dynamic_cast<CTile*>(pTile)->SetTileMovable();
				}
			}
			return true;
		}
	}
	return 0;
}



void CUnit::SetTarget(CObj* pTarget, INTPOINT pos)
{
	m_pTarget = pTarget;
	FLOATPOINT src(m_tSelectRect.left, m_tSelectRect.top);
	INTPOINT idx = TILEMANAGER->GetIndex(pos);
	pos.x = idx.x * TILE_SIZE;
	pos.y = idx.y * TILE_SIZE;

	FLOATPOINT dest(pos.x, pos.y);

	if (m_tStat.nAttackRange >= MATHMANAGER->CalcDistance(src, dest)) {
		m_eCurrId = UNIT::ATTACK;
		m_tInfo.fAngle = MATHMANAGER->CalcDegree(dest, src);
		m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fAttackAnimDivide);
		nAnimationCnt = -1;
		m_tAttackTargetPos = dest;

		return;

	}
	else {
		INTPOINT src;
		src.x = m_tSelectRect.left;
		src.y = m_tSelectRect.top;

		INTPOINT dest[4];

		for (int i = 0; i < 4; ++i) dest[i] = pos;

		node_t* node[4];

		// L B R T
		dest[0].x -= m_tStat.nAttackRange;
		dest[1].y += m_tStat.nAttackRange;
		dest[2].x += m_tStat.nAttackRange;
		dest[3].y -= m_tStat.nAttackRange;


		for (int i = 0; i < 4; ++i) {
			node[i] = PATHMANAGER->FindPath(src, dest[i]);
		}


		for (int i = 0; i < 4; ++i) {
			if (0 > node[i]->value_factor) node[i]->value_factor = 999;
		}

		int min = node[0]->value_factor;

		for (int i = 0; i < 4; ++i) {
			if (min > node[i]->value_factor) min = node[i]->value_factor;
		}

		for (int j = 0; j < 4; ++j) {
			if (min == node[j]->value_factor) {
				node[j] = PATHMANAGER->FindPath(src, dest[j]);
				SetMove(node[j]);
				m_bAttack = true;

				break;


			}
		}



	}

	m_tAttackTargetPos = dest;


}

void CUnit::SetAttack()
{

	m_eCurrId = UNIT::ATTACK;
	
	FLOATPOINT src(m_tSelectRect.left, m_tSelectRect.top);
	FLOATPOINT dest(m_tAttackTargetPos.x, m_tAttackTargetPos.y);


	m_tInfo.fAngle = MATHMANAGER->CalcDegree(dest, src);
	m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fAttackAnimDivide);
	nAnimationCnt = -1;
}

void CUnit::UpdateRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tAnimationInfo[m_eCurrId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tAnimationInfo[m_eCurrId].nImageH);
}
