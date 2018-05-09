#include "stdafx.h"
#include "Structure.h"
#include "Tile.h"
#include "Unit.h"
#include "Scv.h"
#include "Marine.h"

void CStructure::Init()
{
	m_eCurrId = STRUCTURE_IDLE;
	m_tAnimationInfo = new ANIMATION_INFO[STRUCTURE_STATE_END];
	for (int i = 0; i < STRUCTURE_STATE_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(m_tAnimationInfo[i]));

	m_bIsStructure = true;
	fUnitBuildReMainPercent = 1.f;
	dwUnitBuildTime = 0;
}

void CStructure::LateInit()
{
	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);

	// Set Animation Name
	for (int i = 0; i < STRUCTURE_STATE_END; ++i) {

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

	INTPOINT pos(m_tRect.left, m_tRect.top);

	INTPOINT t = TILEMANAGER->GetIndex(pos);


	if (t.x & 1) {
		m_tSelectRect.left = m_tRect.left + fScrollX;
		m_tSelectRect.right = m_tSelectRect.left + fScrollX + TILE_SIZE * 4;

	}

	else {
		m_tSelectRect.left = m_tRect.left + fScrollX + TILE_SIZE;
		m_tSelectRect.right = m_tRect.right + fScrollX + TILE_SIZE;
	}

	m_tSelectRect.top = (m_tRect.top + fScrollY) + TILE_SIZE;
	m_tSelectRect.bottom = m_tSelectRect.top + TILE_SIZE * 3;

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


	// Unit Summon Queue
	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(UNIT_SUMMON_QUEUE);

	memcpy(&m_unitQueue.tInfo, p, sizeof(IMAGE_INFO));

	m_unitQueue.tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.41f);
	m_unitQueue.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.935f);
	m_unitQueue.tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.2f);
	m_unitQueue.tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.063f);
	m_unitQueue.tColor = RGB(0, 0, 0);

	
	// Progress 1
	p = BITMAPMANAGER->GetImageInfo(PROGRESS);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		memcpy(&m_unitProgress[i].tInfo, &p[i], sizeof(IMAGE_INFO));

		m_unitProgress[i].tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.46f);
		m_unitProgress[i].tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.944f);
		m_unitProgress[i].tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.15f);
		m_unitProgress[i].tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.01);
		if (1 == i) {
			m_unitProgress[i].tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.464f);
			m_unitProgress[i].tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.947f);
			m_unitProgress[i].tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.14f);

			m_unitProgress[i].tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.005);

		}
		m_unitProgress[i].tColor = RGB(0, 0, 0);
		
	}


	// Barrack Build Icon
	p = BITMAPMANAGER->GetImageInfo(BARRACK_BUILD_ICON);
	FLOATPOINT tPos(0.795f, 0.875f);

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

		// Odd 
		if (i & 1) {
			pTemp->nMineCost = 50;
			tPos.fX += 0.070f;
		}
		if (1 != i) pTemp->nGasCost = 25;

		if (7 == i) {
			pTemp->nMineCost = 25;
			pTemp->nGasCost = 75;

		}
		m_BuildList[BARRACK].push_back(pTemp);

		if (((i + 1) % 6) == 0) {
			tPos.fX = 0.795f;
			tPos.fY += 0.04f;
		}
	}

	// Control Build Icon
	p = BITMAPMANAGER->GetImageInfo(CONTROLS_BUILD_ICON);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		BUILD_INFO* pTemp = new BUILD_INFO;
		memcpy(&pTemp->tImage.tInfo, &p[i], sizeof(IMAGE_INFO));

		pTemp->tImage.tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.795f);
		pTemp->tImage.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.875f);
		pTemp->tImage.tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.05f);
		pTemp->tImage.tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.025);
		pTemp->tImage.tColor = RGB(0, 0, 0);

		pTemp->tClickArea.x = pTemp->tImage.tPos.x + pTemp->tImage.tDrawSize.x;
		pTemp->tClickArea.y = pTemp->tImage.tPos.y + pTemp->tImage.tDrawSize.y;

		// Odd 
		if (i & 1) pTemp->nMineCost = 50;
		m_BuildList[CONTROL].push_back(pTemp);
	}

}

int CStructure::Update()
{
	CObj::LateInit();
	BuildUnit();
	//if (m_eCurrId == STRUCTURE_BUILD && m_tInfo.eObjId == BARRACK) {
	//	m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % 3;
	//}
	return 0;
}

void CStructure::LateUpdate()
{
}

void CStructure::Render()
{
	if (0 == m_tAnimationInfo[m_eCurrId].nImageW) return;

	if (STRUCTURE_PRODUCE_UNIT == m_eCurrId) {
		if (CONTROL == m_tInfo.eObjId) {
			BITMAPMANAGER->GetImage()[m_tAnimationInfo[STRUCTURE_IDLE].tName[m_tAnimationInfo[STRUCTURE_IDLE].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
				static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
				m_tAnimationInfo[STRUCTURE_IDLE].nImageW,
				m_tAnimationInfo[STRUCTURE_IDLE].nImageH,
				0,
				0,
				m_tAnimationInfo[STRUCTURE_IDLE].nImageW,
				m_tAnimationInfo[STRUCTURE_IDLE].nImageH, RGB(0, 0, 0));


			BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX() - 1),
				static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY() - 28),
				m_tAnimationInfo[m_eCurrId].nImageW,
				m_tAnimationInfo[m_eCurrId].nImageH,
				0,
				0,
				m_tAnimationInfo[m_eCurrId].nImageW,
				m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));
		}
		else {
			m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % m_tAnimationInfo[m_eCurrId].nAnimationNum;
			BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
				static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
				m_tAnimationInfo[m_eCurrId].nImageW,
				m_tAnimationInfo[m_eCurrId].nImageH,
				0,
				0,
				m_tAnimationInfo[m_eCurrId].nImageW,
				m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));

		}

	}

	else
		BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
			static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
			m_tAnimationInfo[m_eCurrId].nImageW,
			m_tAnimationInfo[m_eCurrId].nImageH,
			0,
			0,
			m_tAnimationInfo[m_eCurrId].nImageW,
			m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));

}

void CStructure::Release()
{
}

void CStructure::RenderUI()
{
	HDC hDC = RENDERMANAGER->GetMemDC();


	BITMAPMANAGER->GetImage()[m_unitQueue.tInfo.szName]->TransparentBlt(hDC,
	m_unitQueue.tPos.x,
	m_unitQueue.tPos.y,
	m_unitQueue.tDrawSize.x,
	m_unitQueue.tDrawSize.y,
	0,
	0,
	m_unitQueue.tInfo.nImageW,
	m_unitQueue.tInfo.nImageH, m_unitQueue.tColor);

	for (int i = 0; i < 2; ++i) {
		if(0 == i)
		BITMAPMANAGER->GetImage()[m_unitProgress[i].tInfo.szName]->TransparentBlt(hDC,
			m_unitProgress[i].tPos.x,
			m_unitProgress[i].tPos.y,
			m_unitProgress[i].tDrawSize.x,
			m_unitProgress[i].tDrawSize.y,
			0,
			0,
			m_unitProgress[i].tInfo.nImageW,
			m_unitProgress[i].tInfo.nImageH, m_unitProgress[i].tColor);

		else {

			StretchBlt(hDC, m_unitProgress[i].tPos.x, m_unitProgress[i].tPos.y, m_unitProgress[i].tDrawSize.x,
				m_unitProgress[i].tDrawSize.y,
				BITMAPMANAGER->GetImage()[m_unitProgress[i].tInfo.szName]->GetDC(), (m_unitProgress[i].tInfo.nImageW * fUnitBuildReMainPercent), 0,
				m_unitProgress[i].tInfo.nImageW, m_unitProgress[i].tInfo.nImageH, SRCCOPY);

		}
		
	}


	for (auto& d : m_BuildList[m_tInfo.eObjId]) {
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

	for (auto& d : m_BuildQueueList) {
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

void CStructure::UpdateRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tAnimationInfo[m_eCurrId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tAnimationInfo[m_eCurrId].nImageH);
}

bool CStructure::CheckBuildUnit(POINT tMousePos)
{
	int nCnt = 0;

	for (auto& d : m_BuildList[m_tInfo.eObjId]) {

		if (tMousePos.x > d->tImage.tPos.x && tMousePos.x < d->tClickArea.x &&
			tMousePos.y > d->tImage.tPos.y && tMousePos.y < d->tClickArea.y) {
			nCnt++;
			float fX = 0.416f;
			if (SCENEMANAGER->GetReSourcesValue(MINE) >= d->nMineCost) {
				if (!(nCnt & 1) && m_BuildQueueList.size() < 5) {
					int nSize = m_BuildQueueList.size();
					SCENEMANAGER->UpdateResourcesValue(MINE, -d->nMineCost);
					BUILD_INFO* p = new BUILD_INFO;
					memcpy(p, d, sizeof(BUILD_INFO));


					p->tImage.tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.04f);
					p->tImage.tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.025);

					if (0 == nSize) {
						p->tImage.tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * fX);
						p->tImage.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.935f);
					}
					else if (1 == nSize) {
						p->tImage.tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * fX);
						p->tImage.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.97f);
					}
					else {
						fX += 0.05f * (nSize - 1);
						p->tImage.tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * fX);
						p->tImage.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.97f);
					}
					m_BuildQueueList.push_back(p);

					return true;
				}
		
			}
		}
	}

	return false;
}

void CStructure::BuildUnit()
{
	if (0 < m_BuildQueueList.size() && dwUnitBuildTime + 100 < GetTickCount()) {
		dwUnitBuildTime = GetTickCount();
		if(STRUCTURE_IDLE == m_eCurrId) m_eCurrId = STRUCTURE_PRODUCE_UNIT;
		else m_eCurrId = STRUCTURE_IDLE;


		if(0.0f < fUnitBuildReMainPercent) fUnitBuildReMainPercent -= 0.1f;
		else {
			if (0 < m_BuildQueueList.size()) {

				float fScrollX = SCROLLMANAGER->GetScrollX();
				float fScrollY = SCROLLMANAGER->GetScrollY();

				INTPOINT pos;
				pos.y = m_tSelectRect.bottom;

				INTPOINT area;
				area.x = m_tSelectRect.right;
				area.y = pos.y + TILE_SIZE * 4;

				for (; pos.y < area.y; pos.y += TILE_SIZE) {
					for (pos.x = m_tSelectRect.left; pos.x < area.x; pos.x += TILE_SIZE) {
						INTPOINT idx = TILEMANAGER->GetIndex(pos);
						int nIdx = idx.x + TILEMANAGER->GetTileNum().x * idx.y;
						CObj* pTile = TILEMANAGER->SelectTile(nIdx);
					
						if (dynamic_cast<CTile*>(pTile)->IsMovable()) {
							if (!strcmp(m_BuildQueueList.front()->tImage.tInfo.szName, "ControlUnitIcon01")) {
								CObj* pObj = CFactoryManager<CScv>::CreateObj(GREEN, SCV, PORTRAIT::SCV,
									UNIT::LARGE_WIRE::SCV, UNIT::SMALL_WIRE::SCV, UNIT_SELECT2, FLOATPOINT((idx.x * TILE_SIZE) - 19, (idx.y * TILE_SIZE) - 17), 60);
								OBJMANAGER->AddObject(pObj, SCV);
							}
							else if (!strcmp(m_BuildQueueList.front()->tImage.tInfo.szName, "BarrackUnitIcon01")) {
								CObj* pObj = CFactoryManager<CMarine>::CreateObj(GREEN, MARINE, PORTRAIT::MARINE,
									UNIT::LARGE_WIRE::MARINE, UNIT::SMALL_WIRE::MARINE, UNIT_SELECT2, FLOATPOINT((idx.x * TILE_SIZE) - 19, (idx.y * TILE_SIZE) - 17), 60);
								OBJMANAGER->AddObject(pObj, MARINE);
							}
							else if (!strcmp(m_BuildQueueList.front()->tImage.tInfo.szName, "BarrackUnitIcon07")) {
								CObj* pObj = CFactoryManager<CMarine>::CreateObj(GREEN, GHOST, PORTRAIT::GHOST,
									UNIT::LARGE_WIRE::GHOST, UNIT::SMALL_WIRE::GHOST, UNIT_SELECT2, FLOATPOINT((idx.x * TILE_SIZE) - 19, (idx.y * TILE_SIZE) - 17), 60);
								OBJMANAGER->AddObject(pObj, GHOST);
							}
							m_BuildQueueList.pop_front();
							int nSize = m_BuildQueueList.size();

							BUILD_LIST::iterator itor = m_BuildQueueList.begin();

							for (int i = 0; i < nSize; ++i) {
								if (0 == i) (*itor)->tImage.tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.935f);
								else (*itor)->tImage.tPos.x -= static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.05f);

								++itor;
							}
							fUnitBuildReMainPercent = 1.f;

							return;
						}

					}

				}
			}
		}

	}

	if(0 == m_BuildQueueList.size()) m_eCurrId = STRUCTURE_IDLE;
}
