#include "stdafx.h"
#include "Obj.h"
#include "Scene.h"
#include "Button.h"
#include "Tile.h"
#include "Mine.h"
#include "Structure.h"
#include "Unit.h"
#include "Scv.h"
#include "Ghost.h"

CMouseManager*	CMouseManager::m_pInstance = nullptr;

void CMouseManager::Init()
{
	m_eCurrId = ARROW;
	m_eBuildId = OBJ_END;

	m_bIsDragging = false;
	m_bIsClickedBuildIcon = false;
	m_bCanBuild = false;
	m_bSpecialAttack = false;
	m_nAnimationIdx = 0;
	m_nSelectedUnitNum = 0;

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(CURSOR);

	// Set Animation Name
	for (int i = 0; i < CURSOR_END; ++i) {

		m_tAnimationInfo[i].tName = new char*[pAnim[i].nAnimationNum];
		ZeroMemory(m_tAnimationInfo[i].tName, pAnim[i].nAnimationNum);

		for (int j = 0; j < pAnim[i].nAnimationNum; ++j) {

			m_tAnimationInfo[i].tName[j] = new char[STR_LEN];
			strcpy_s(m_tAnimationInfo[i].tName[j], strlen(m_tAnimationInfo[i].tName[j]), pAnim[i].tName[j]);

			m_tAnimationInfo[i].nAnimationNum = pAnim[i].nAnimationNum;

			m_tAnimationInfo[i].dwAnimationTime = GetTickCount();
			m_tAnimationInfo[i].nCnt = 0;

		}

	}

	
		IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(UNIT_SELECT_IMAGE);

		m_tSelectImage = new IMAGE_INFO[p->nImageNum];
		memcpy(m_tSelectImage, p, sizeof(IMAGE_INFO) * p->nImageNum);

		// Portrait
		for (int i = 0; i < PORTRAIT::PORTRAIT_END; ++i) {
			p = BITMAPMANAGER->GetPortraitImageInfo(static_cast<PORTRAIT::ID>(i));
			for (int j = 0; j < p[0].nImageNum; ++j) {
				STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

				memcpy(&pTemp->tInfo, &p[j], sizeof(IMAGE_INFO));

				pTemp->tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.648f);
				pTemp->tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.93f);
				pTemp->tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.089f);
				pTemp->tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.05f);
				pTemp->tColor = RGB(0, 0, 0);

				m_portraitList[i].push_back(pTemp);
			}
		}

		// Large Wire
		m_wireList[UNIT::LARGE] = new STATIC_UI_IMAGE_VECTOR_LIST[UNIT::LARGE_WIRE::LARGE_WIRE_END];
		for (int i = 0; i < UNIT::LARGE_WIRE::LARGE_WIRE_END; ++i) {
			p = BITMAPMANAGER->GetLargeWireImageInfo(static_cast<UNIT::LARGE_WIRE::LARGE_WIRE_ID>(i));
			for (int j = 0; j < p[0].nImageNum; ++j) {
				STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

				memcpy(&pTemp->tInfo, &p[j], sizeof(IMAGE_INFO));

				pTemp->tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.27f);
				pTemp->tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.92f);
				pTemp->tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.13f);
				pTemp->tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.06f);
				pTemp->tColor = RGB(0, 0, 0);

				m_wireList[UNIT::LARGE][i].push_back(pTemp);
			}
		}

		// Small Wire
		m_wireList[UNIT::SMALL] = new STATIC_UI_IMAGE_VECTOR_LIST[UNIT::SMALL_WIRE::SMALL_WIRE_END];
		for (int i = 0; i < UNIT::SMALL_WIRE::SMALL_WIRE_END; ++i) {
			p = BITMAPMANAGER->GetSmallWireImageInfo(static_cast<UNIT::SMALL_WIRE::SMALL_WIRE_ID>(i));
			for (int j = 0; j < p[0].nImageNum; ++j) {
				STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

				memcpy(&pTemp->tInfo, &p[j], sizeof(IMAGE_INFO));

				pTemp->tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.27f);
				pTemp->tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.92f);
				pTemp->tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.05f);
				pTemp->tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.04f);
				pTemp->tColor = RGB(0, 0, 0);

				m_wireList[UNIT::SMALL][i].push_back(pTemp);
			}
		}


		p = BITMAPMANAGER->GetImageInfo(BUILD_IMAGE);

		float fScrollX = SCROLLMANAGER->GetScrollX();
		float fScrollY = SCROLLMANAGER->GetScrollY();
		for (int i = 0; i < p[0].nImageNum; ++i) {
			memcpy(&m_tBuildImage[i].tInfo, &p[i], sizeof(IMAGE_INFO));

			m_tBuildImage[i].tPos.x = m_tRect.left + fScrollX;
			m_tBuildImage[i].tPos.y = (m_tRect.top + fScrollY) + TILE_SIZE;
			m_tBuildImage[i].tDrawSize.x = m_tBuildImage[i].tPos.x + (TILE_SIZE * 4);
			m_tBuildImage[i].tDrawSize.y = m_tBuildImage[i].tPos.y + (TILE_SIZE * 3);

			m_tBuildImage[i].tColor = RGB(0, 0, 0);
		
		} 

		
	
}

void CMouseManager::UpdateRect()
{

	m_tRect.left = m_tPos.x - CURSOR_SIZE / 2 - 30;
	m_tRect.right = m_tRect.left + 50;
	m_tRect.top = m_tPos.y - 30;
	m_tRect.bottom = m_tRect.top + 50;

}

void CMouseManager::Update()
{
	// Update Mouse Pos
	GetCursorPos(&m_tPos);
	ScreenToClient(RENDERMANAGER->GethWnd(), &m_tPos);

	if (HIGHSCROLL != m_eCurrId && LOWSCROLL != m_eCurrId) {
		if (m_tAnimationInfo[m_eCurrId].dwAnimationTime + 100 < GetTickCount()) {
			if (TARGG == m_eCurrId && m_tAnimationInfo[m_eCurrId].nCnt + 1 == m_tAnimationInfo[m_eCurrId].nAnimationNum) {
				m_tAnimationInfo[m_eCurrId].nCnt = 0;
				m_eCurrId = ARROW;
			}

			m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % m_tAnimationInfo[m_eCurrId].nAnimationNum;
			m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
		}
	}


	if (0 < m_nSelectedUnitNum && TARGG != m_eCurrId && ILLEGAL != m_eCurrId && TARGY != m_eCurrId) {
		if(m_tPos.x < m_tSelectRect.left ||
			m_tPos.x  > m_tSelectRect.right ||
			m_tPos.y < m_tSelectRect.top ||
			m_tPos.y > m_tSelectRect.bottom){
			m_tAnimationInfo[m_eCurrId].nCnt = 0;
			m_eCurrId = ARROW;
		}

	}


	if (ILLEGAL == m_eCurrId) {
		if (m_tPos.x < m_tIllegalRect.left ||
			m_tPos.x > m_tIllegalRect.right ||
			m_tPos.y < m_tIllegalRect.top ||
			m_tPos.y > m_tIllegalRect.bottom) {
			m_tAnimationInfo[m_eCurrId].nCnt = 0;
			m_eCurrId = ARROW;

		}
	}


}

void CMouseManager::Render()
{

	UpdateRect();



	// Rendser Circle
	if (m_nSelectedUnitNum > 0) {
		for (int i = 0; i < m_nSelectedUnitNum; ++i) {
			INTPOINT pos;
			pos.x = m_selectedObj[i]->GetInfo().tPos.fX;
			pos.y = m_selectedObj[i]->GetInfo().tPos.fY;

			switch (m_tUnitSelect[i].eSelectedUnitsize) {
			case UNIT_SELECT2:
				pos.x += TILE_SIZE / 2;
				pos.y += TILE_SIZE / 2;
				break;
			case UNIT_SELECT9:
				pos.x -= TILE_SIZE / 2;
				pos.y -= TILE_SIZE / 2;
				break;
			case UNIT_SELECT15:
				pos.x -= TILE_SIZE / 3;
				break;

			}


			BITMAPMANAGER->GetImage()[m_tSelectImage[m_tUnitSelect[i].eSelectedUnitsize].szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(pos.x + SCROLLMANAGER->GetScrollX()),
				static_cast<int>(pos.y + SCROLLMANAGER->GetScrollY()),
				m_tSelectImage[m_tUnitSelect[i].eSelectedUnitsize].nImageW,
				m_tSelectImage[m_tUnitSelect[i].eSelectedUnitsize].nImageH,
				0,
				0,
				m_tSelectImage[m_tUnitSelect[i].eSelectedUnitsize].nImageW,
				m_tSelectImage[m_tUnitSelect[i].eSelectedUnitsize].nImageH, RGB(255, 255, 255));
		}

		RenderUI();

	}

	if (m_bIsDragging) RenderDragRect();

	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

	if (OBJ_END != m_eBuildId) {
		RECT rc;
		rc.left = m_tPos.x - m_tBuildImage[m_eBuildId].tInfo.nImageW / 2;
		rc.right = rc.left + TILE_SIZE * 4;
		rc.top = m_tPos.y - m_tBuildImage[m_eBuildId].tInfo.nImageH / 2;
		rc.bottom = rc.top + TILE_SIZE * 3;


		HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));

		HBRUSH oldBrush = (HBRUSH)SelectObject(RENDERMANAGER->GetMemDC(), greenBrush);


		int tileNum = TILEMANAGER->GetTileNum().x;
		int cnt = 0;
		for (int y = rc.top; y < rc.bottom; y += TILE_SIZE) {
			for (int x = rc.left; x < rc.right; x += TILE_SIZE) {
				INTPOINT leftTopIdx = TILEMANAGER->GetIndex(INTPOINT(x, y));
				INTPOINT rightBottomIdx = TILEMANAGER->GetIndex(INTPOINT(x + TILE_SIZE, y + TILE_SIZE));


				int nLeftTop = leftTopIdx.x + tileNum * leftTopIdx.y;
				int nRightBottom = rightBottomIdx.x + tileNum * rightBottomIdx.y;

				CObj* LT = TILEMANAGER->SelectTile(nLeftTop);
				CObj* RB = TILEMANAGER->SelectTile(nRightBottom);

				if (dynamic_cast<CTile*>(LT)->IsMovable() && dynamic_cast<CTile*>(RB)->IsMovable())
					HBRUSH oldBrush = (HBRUSH)SelectObject(RENDERMANAGER->GetMemDC(), greenBrush);

				else {
					cnt++;
					HBRUSH oldBrush = (HBRUSH)SelectObject(RENDERMANAGER->GetMemDC(), redBrush);
				}
				Rectangle(RENDERMANAGER->GetMemDC(), x,
					y, x + TILE_SIZE, y + TILE_SIZE);
			}

		}
		SelectObject(RENDERMANAGER->GetMemDC(), oldBrush);
		DeleteObject(greenBrush);
		DeleteObject(redBrush);

		if (0 == cnt) m_bCanBuild = true;
		else m_bCanBuild = false;
		BITMAPMANAGER->GetImage()[m_tBuildImage[m_eBuildId].tInfo.szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			rc.left,
			rc.top,
			m_tBuildImage[m_eBuildId].tInfo.nImageW,
			m_tBuildImage[m_eBuildId].tInfo.nImageH,
			0,
			0,
			m_tBuildImage[m_eBuildId].tInfo.nImageW,
			m_tBuildImage[m_eBuildId].tInfo.nImageH, RGB(0, 0, 0));


	}

	// Render Cursor

	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_tPos.x - CURSOR_SIZE / 2,
		m_tPos.y - CURSOR_SIZE / 2,
		CURSOR_SIZE,
		CURSOR_SIZE,
		0,
		0,
		CURSOR_SIZE,
		CURSOR_SIZE, RGB(0, 0, 0));



}

void CMouseManager::Release()
{
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName[i]);
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName);


	SafeDelete(m_tSelectImage);

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CMouseManager::RenderDragRect()
{
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(RENDERMANAGER->GetMemDC(), myBrush);
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(RENDERMANAGER->GetMemDC(), hNewPen);
	Rectangle(RENDERMANAGER->GetMemDC(), m_tDragPos[DRAG_START_POS].x,
		m_tDragPos[DRAG_START_POS].y, m_tDragPos[DRAG_END_POS].x, m_tDragPos[DRAG_END_POS].y);
	SelectObject(RENDERMANAGER->GetMemDC(), hNewPen);
	DeleteObject(hOldPen);
	SelectObject(RENDERMANAGER->GetMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void CMouseManager::RenderUI()
{

	HDC hDC = RENDERMANAGER->GetMemDC();
	STATIC_UI_IMAGE_INFO* p = nullptr;

	if (m_tUnitSelect[0].eSelectedPortraitId != PORTRAIT::PORTRAIT_END) {
		STATIC_UI_IMAGE_INFO* p = m_portraitList[m_tUnitSelect[0].eSelectedPortraitId][m_nAnimationIdx];

		if (m_dwAnimationTime + 50 < GetTickCount()) {
			m_dwAnimationTime = GetTickCount();
			m_nAnimationIdx = (m_nAnimationIdx + 1) % p->tInfo.nImageNum;
		}
		

		// Render Portrait
		BITMAPMANAGER->GetImage()[p->tInfo.szName]->TransparentBlt(hDC,
			p->tPos.x,
			p->tPos.y,
			p->tDrawSize.x,
			p->tDrawSize.y,
			0,
			0,
			p->tInfo.nImageW,
			p->tInfo.nImageH, p->tColor);
	}

	// Render Wire
	if (UNIT::LARGE == m_tUnitSelect[0].eSelectedWireSizeId) {
		int idx = 0;
		float fPercent = m_selectedObj[0]->GetHpPercent();
		if (0.7f > fPercent) idx = 1;
		if (0.6f > fPercent) idx = 2;
		if (0.5f > fPercent) idx = 3;
		if (0.4f > fPercent) idx = 4;
		if (0.3f > fPercent) idx = 5;



		p = m_wireList[m_tUnitSelect[0].eSelectedWireSizeId][m_tUnitSelect[0].eSelectedLargeWireId][idx];

		BITMAPMANAGER->GetImage()[p->tInfo.szName]->TransparentBlt(hDC,
			p->tPos.x,
			p->tPos.y,
			p->tDrawSize.x,
			p->tDrawSize.y,
			0,
			0,
			p->tInfo.nImageW,
			p->tInfo.nImageH, p->tColor);

		// Render HP
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 255, 0));
		wsprintf(m_tUnitSelect[0].szHp, L"%d/%d", m_selectedObj[0]->GetStat().nHP, m_selectedObj[0]->GetStat().nMaxHP);
		TextOut(hDC, static_cast<int>(p->tPos.x * 1.2f), static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.98f), m_tUnitSelect[0].szHp, _tcslen(m_tUnitSelect[0].szHp));

		// Render Name
		SetTextColor(hDC, RGB(189, 189, 189));
		TextOut(hDC, static_cast<int>(p->tPos.x * 1.6f), static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.91f), m_tUnitSelect[0].szName, _tcslen(m_tUnitSelect[0].szName));
		
	}

	else {


		for (int i = 0; i < m_nSelectedUnitNum; ++i) {
			float fPercent = m_selectedObj[i]->GetHpPercent();
			int idx = 0;

			if (0.7f > fPercent) idx = 1;
			if (0.6f > fPercent) idx = 2;
			if (0.5f > fPercent) idx = 3;
			if (0.4f > fPercent) idx = 4;
			if (0.3f > fPercent) idx = 5;

		p = m_wireList[m_tUnitSelect[i].eSelectedWireSizeId][m_tUnitSelect[i].eSelectedSmallWireId][idx];

			BITMAPMANAGER->GetImage()[p->tInfo.szName]->TransparentBlt(hDC,
				m_tUnitSelect[i].tDrawPos.x,
				m_tUnitSelect[i].tDrawPos.y,
				p->tDrawSize.x,
				p->tDrawSize.y,
				0,
				0,
				p->tInfo.nImageW,
				p->tInfo.nImageH, p->tColor);
		}

	}

	if (m_tUnitSelect[0].bIsStructure) dynamic_cast<CStructure*>(m_selectedObj[0])->RenderUI();
	if (dynamic_cast<CUnit*>(m_selectedObj[0])) dynamic_cast<CUnit*>(m_selectedObj[0])->RenderUI();

	

}

void CMouseManager::CheckSwapTile()
{

	CObj* pTile = GetTile();

	if (nullptr == pTile) return;

	dynamic_cast<CTile*>(pTile)->SwapTile();
}

void CMouseManager::SelectObj()
{
	CObj* pTile = GetTile();
	INTPOINT pos;
	pos.x = m_tPos.x;
	pos.y = m_tPos.y;

	if (nullptr == pTile) return;
	for (int i = BARRACK; i < OBJ_END; ++i) {
		OBJLIST list = OBJMANAGER->GetObj(static_cast<OBJ_ID>(i));
		for (auto& d : list) {
			if (d->IsClicked(pos)) {
				if (TARGY == m_eCurrId) {
					for (int i = 0; i < m_nSelectedUnitNum; ++i)
						dynamic_cast<CUnit*>(m_selectedObj[i])->SetTarget(d, pos);
					
					m_eCurrId = ARROW;
				}
				if (SCV == d->GetObjId()) SOUNDMANAGER->PlayerEffectSound(SCV_SELECT);
				else if (MARINE == d->GetObjId()) SOUNDMANAGER->PlayerEffectSound(MARINE_SELECT);
				else if (GHOST == d->GetObjId()) SOUNDMANAGER->PlayerEffectSound(GHOST_SELECT);

				else if(d->IsStructure()) SOUNDMANAGER->PlayerEffectSound(SELECT_BUILDING);

				m_selectedObj[0] = d;
				m_tSelectRect = d->GetSelectRect();
				m_tUnitSelect[0].eId = static_cast<OBJ_ID>(i);
				m_tUnitSelect[0].eSelectedUnitsize = d->GetSize();
				m_tUnitSelect[0].tSelectRenderRect = d->GetSelectRect();
				m_tUnitSelect[0].eSelectedPortraitId = d->GetPortraitId();
				m_tUnitSelect[0].eSelectedWireSizeId = UNIT::WIRE_ID::LARGE;
				m_tUnitSelect[0].eSelectedLargeWireId = d->GetLargeWireId();
				m_tUnitSelect[0].bIsStructure = d->IsStructure();

				wcscpy_s(m_tUnitSelect[0].szName, STR_LEN, OBJ_NAME[i]);
				wsprintf(m_tUnitSelect[0].szHp, L"%d/%d", d->GetStat().nHP, d->GetStat().nMaxHP);

				if (GREEN == d->GetOwnerId()) {
					m_tAnimationInfo[m_eCurrId].nCnt = 0;
					m_eCurrId = MAGG;
				}

				m_dwAnimationTime = GetTickCount();
				m_nAnimationIdx = 0;
				m_nSelectedUnitNum = 1;

				return;
			}
		}
	}

	pos.y -= TILE_SIZE;
	CObj* p = TILEMANAGER->TileObjSelect(pos);
	if (nullptr != p) {
		m_selectedObj[0] = p;
		m_tSelectRect = p->GetSelectRect();
		m_tSelectRect.top += TILE_SIZE;

		m_tSelectRect.bottom += TILE_SIZE;

		m_tUnitSelect[0].eSelectedUnitsize = p->GetSize();
		m_tUnitSelect[0].tSelectRenderRect = p->GetSelectRect();
		m_tUnitSelect[0].eSelectedPortraitId = PORTRAIT::PORTRAIT_END;
		m_tUnitSelect[0].eSelectedWireSizeId = UNIT::WIRE_ID::LARGE;
		m_tUnitSelect[0].eSelectedLargeWireId = p->GetLargeWireId();
		m_tUnitSelect[0].bIsStructure = p->IsStructure();

		if (UNIT::LARGE_WIRE::MINE == p->GetLargeWireId()) wcscpy_s(m_tUnitSelect[0].szName, STR_LEN, L"Mineral");
		
		wsprintf(m_tUnitSelect[0].szHp, L"%d/%d", p->GetStat().nHP, p->GetStat().nMaxHP);

		if (NEUTRAL == p->GetOwnerId()) {
			m_tAnimationInfo[m_eCurrId].nCnt = 0;
			m_eCurrId = MAGY;
		}
		m_dwAnimationTime = GetTickCount();
		m_nAnimationIdx = 0;
		m_nSelectedUnitNum = 1;

		return;
	}



	m_nSelectedUnitNum = 0;
}

void CMouseManager::DragSelectObj()
{
	CObj* pTile = GetTile();

	if (nullptr == pTile) return;
	INTPOINT pos;
	for (int i = BARRACK; i < OBJ_END; ++i) {
		OBJLIST list = OBJMANAGER->GetObj(static_cast<OBJ_ID>(i));
		auto itor_begin = list.begin();
		auto itor_end = list.end();

		while(itor_begin!= itor_end){
			for (pos.y = m_tDragPos[DRAG_START_POS].y; pos.y < m_tDragPos[DRAG_END_POS].y; pos.y += TILE_SIZE) {
				for (pos.x = m_tDragPos[DRAG_START_POS].x; pos.x < m_tDragPos[DRAG_END_POS].x; pos.x += TILE_SIZE) {
					if ((*itor_begin)->IsClicked(pos)) {
						if (PORTRAIT::ADVISOR == (*itor_begin)->GetPortraitId()) goto END;

						m_selectedObj[m_nSelectedUnitNum] = *itor_begin;
						m_tSelectRect = (*itor_begin)->GetSelectRect();
						m_tUnitSelect[m_nSelectedUnitNum].eSelectedPortraitId = (*itor_begin)->GetPortraitId();
						m_tUnitSelect[m_nSelectedUnitNum].eSelectedUnitsize = (*itor_begin)->GetSize();
						m_tUnitSelect[m_nSelectedUnitNum].tSelectRenderRect = (*itor_begin)->GetSelectRect();
						m_tUnitSelect[0].bIsStructure = (*itor_begin)->IsStructure();


						m_tUnitSelect[m_nSelectedUnitNum].tDrawPos.x =
							static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.28f) +
							static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.05f) * (m_nSelectedUnitNum % (MAX_UNIT_SELECT_NUM / 2));
				
						m_tUnitSelect[m_nSelectedUnitNum].tDrawPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.91f);
						if(MAX_UNIT_SELECT_NUM / 2 <= m_nSelectedUnitNum) m_tUnitSelect[m_nSelectedUnitNum].tDrawPos.y += static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.045f);


						m_tUnitSelect[m_nSelectedUnitNum].eSelectedWireSizeId = UNIT::WIRE_ID::SMALL;
						m_tUnitSelect[m_nSelectedUnitNum].eSelectedSmallWireId = (*itor_begin)->GetSmallWireId();


						if (GREEN == (*itor_begin)->GetOwnerId()) {
							m_eCurrId = MAGG;
							m_tAnimationInfo[m_eCurrId].nCnt = 0;
						}

						m_dwAnimationTime = GetTickCount();
						m_nAnimationIdx = 0;
						if (m_nSelectedUnitNum < MAX_UNIT_SELECT_NUM) ++m_nSelectedUnitNum;
	
						goto END;
					}
				}
			}
			END:
			++itor_begin;
		}

	}
	if (SCV == m_selectedObj[0]->GetObjId()) SOUNDMANAGER->PlayerEffectSound(SCV_SELECT);
	else if (MARINE == m_selectedObj[0]->GetObjId()) SOUNDMANAGER->PlayerEffectSound(MARINE_SELECT);
	else if (GHOST == m_selectedObj[0]->GetObjId()) SOUNDMANAGER->PlayerEffectSound(GHOST_SELECT);

}

void CMouseManager::CheckSelectObj()
{
	
	// Update Mouse Pos
	GetCursorPos(&m_tPos);
	ScreenToClient(RENDERMANAGER->GethWnd(), &m_tPos);

	if (m_bIsDragging) {
		if (KEYMANAGER->KeyUp(VK_LBUTTON)) {
			m_bIsDragging = false;
			m_tAnimationInfo[m_eCurrId].nCnt = 0;
			m_eCurrId = ARROW;
			MOUSEMANAGER->DragSelectObj();
			return;
		}
	}
	else {
		if (KEYMANAGER->KeyDown(VK_LBUTTON)) {
			if (TARGY == m_eCurrId && m_bSpecialAttack && dynamic_cast<CGhost*>(m_selectedObj[0])) {
				dynamic_cast<CGhost*>(m_selectedObj[0])->SetNuclear(m_tPos);
			}
			// Build Icon Click
			if (0 < m_nSelectedUnitNum) {

				m_bIsClickedBuildIcon = false;
				if(m_tUnitSelect[0].bIsStructure)
					m_bIsClickedBuildIcon = dynamic_cast<CStructure*>(m_selectedObj[0])->CheckBuildUnit(m_tPos);
				else if (dynamic_cast<CUnit*>(m_selectedObj[0])) {
					m_bIsClickedBuildIcon = dynamic_cast<CUnit*>(m_selectedObj[0])->CheckCommand(m_tPos);
				}
				if (m_bCanBuild) {
					m_tIntPos.x = m_tPos.x - SCROLLMANAGER->GetScrollX();
					m_tIntPos.y = m_tPos.y - SCROLLMANAGER->GetScrollY();

					INTPOINT dest[3];

					for (int i = 0; i < 3; ++i) dest[i] = m_tIntPos;

					INTPOINT src;
					src.x = m_selectedObj[0]->GetSelectRect().left;
					src.y = m_selectedObj[0]->GetSelectRect().top;
					node_t* node[3];

					// L B R
					dest[0].x -= TILE_SIZE * 3;
					dest[1].y += TILE_SIZE * 2;
					dest[2].x += TILE_SIZE * 3;

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
							m_selectedObj[0]->SetMove(node[j]);

							float fAngle;
							if (0 == j) fAngle = RIGHT;
							else if (1 == j) fAngle = TOP;
							else if (2 == j) fAngle = LEFT;
							INTPOINT spawnPos;
							spawnPos.x = m_tIntPos.x - TILE_SIZE * 2;
							spawnPos.y = m_tIntPos.y - TILE_SIZE * 2;

							dynamic_cast<CScv*>(m_selectedObj[0])->BuildStructure(m_eBuildId, spawnPos, fAngle);
							m_eBuildId = OBJ_END;
							break;


						}
					}

					m_bCanBuild = false;
					m_eBuildId = OBJ_END;

					return;

				}
		
			}
		
			if (!m_bIsClickedBuildIcon) MOUSEMANAGER->SelectObj();


		}
	}
	if (KEYMANAGER->KeyPressing(VK_LBUTTON)) {
		if (!m_bIsDragging && m_tPos.y < m_tMiniMapRect.top * 0.96f && 0 == m_nSelectedUnitNum) {
			m_tDragPos[DRAG_START_POS] = m_tPos;
			m_bIsDragging = true;
			m_tAnimationInfo[m_eCurrId].nCnt = 0;
			m_eCurrId = DRAG;
		}

		if (m_bIsDragging) m_tDragPos[DRAG_END_POS] = m_tPos;
		
	}


}

void CMouseManager::CheckMoveObj()
{


	if (0 < m_nSelectedUnitNum && KEYMANAGER->KeyUp(VK_RBUTTON)) {
		GetCursorPos(&m_tPos);
		ScreenToClient(RENDERMANAGER->GethWnd(), &m_tPos);

		m_tIntPos.x = m_tPos.x - SCROLLMANAGER->GetScrollX();
		m_tIntPos.y = m_tPos.y - SCROLLMANAGER->GetScrollY();
		CObj* pTile = GetTile();
		m_tAnimationInfo[m_eCurrId].nCnt = 0;
		if (dynamic_cast<CTile*>(pTile)->IsMovable()) {
			m_eCurrId = TARGG;
			for (int i = 0; i < m_nSelectedUnitNum; ++i) {
				INTPOINT src;
				src.x = m_selectedObj[i]->GetSelectRect().left;
				src.y = m_selectedObj[i]->GetSelectRect().top;
				node_t* p = PATHMANAGER->FindPath(src, m_tIntPos);
				m_selectedObj[i]->SetMove(p);

			}
			return;
		}
		if (dynamic_cast<CTile*>(pTile)->IsClickable()) {
			m_eCurrId = TARGG;
			INTPOINT dest[3];

			for (int i = 0; i < m_nSelectedUnitNum; ++i) {
				if (SCV == m_selectedObj[i]->GetObjId()) {
					for (int i = 0; i < 3; ++i) dest[i] = m_tIntPos;

					INTPOINT src;
					src.x = m_selectedObj[i]->GetSelectRect().left;
					src.y = m_selectedObj[i]->GetSelectRect().top;
					node_t* node[3];

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
							m_selectedObj[i]->SetMove(node[j]);
							float fAngle;
							if (0 == j) fAngle = RIGHT;
							else if (1 == j) fAngle = TOP;
							else if (2 == j) fAngle = LEFT;

							dynamic_cast<CUnit*>(m_selectedObj[i])->SetAttack(m_tIntPos, fAngle);
							break;


						}
					}

				}
				return;
			}
		}
		m_eCurrId = ILLEGAL;
		SOUNDMANAGER->PlayerEffectSound(ILLEGAL_CLICK);
		m_tIllegalRect = dynamic_cast<CTile*>(pTile)->GetRectWithScroll();
		
	}
}

CObj* CMouseManager::GetTile()
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	int x = (m_tPos.x - static_cast<int>(fScrollX)) / TILE_SIZE;
	int y = (m_tPos.y - static_cast<int>(fScrollY)) / TILE_SIZE;
	int k = TILEMANAGER->GetTileNum().x;
	int nIdx = x + TILEMANAGER->GetTileNum().x * y;

	CObj* pTile = TILEMANAGER->SelectTile(nIdx);
	return pTile;
		
}

void CMouseManager::MouseScroll()
{
	// Up
	if (0 >= m_tPos.y) {
		m_eCurrId = HIGHSCROLL;
		if (0 == m_tPos.x) {
			m_tAnimationInfo[m_eCurrId].nCnt = LU;
			SCROLLMANAGER->SetScrollX(SCROLL_SPEED);
		}
		else if (RENDERMANAGER->GetWindowSize().x - 1 <= m_tPos.x) {
			m_tAnimationInfo[m_eCurrId].nCnt = RU;
			SCROLLMANAGER->SetScrollX(-SCROLL_SPEED);
		}
		else m_tAnimationInfo[m_eCurrId].nCnt = UP;
			
		SCROLLMANAGER->SetScrollY(SCROLL_SPEED);
	}

	// Down
	else if (RENDERMANAGER->GetWindowSize().y - 1 <= m_tPos.y) {
		m_eCurrId = HIGHSCROLL;
		if (0 == m_tPos.x) {
			m_tAnimationInfo[m_eCurrId].nCnt = LD;
			SCROLLMANAGER->SetScrollX(SCROLL_SPEED);
		}
		else if (m_tPos.x >= RENDERMANAGER->GetWindowSize().x - 1) {
			m_tAnimationInfo[m_eCurrId].nCnt = RD;
			SCROLLMANAGER->SetScrollX(-SCROLL_SPEED);
		}
		else m_tAnimationInfo[m_eCurrId].nCnt = DOWN;

		SCROLLMANAGER->SetScrollY(-SCROLL_SPEED);
	}

	// Left
	else if (0 == m_tPos.x) {
		m_eCurrId = HIGHSCROLL;
		m_tAnimationInfo[m_eCurrId].nCnt = L;
		SCROLLMANAGER->SetScrollX(SCROLL_SPEED);
	}

	// Right
	else if (m_tPos.x >= RENDERMANAGER->GetWindowSize().x - 1) {
		m_eCurrId = HIGHSCROLL;
		m_tAnimationInfo[m_eCurrId].nCnt = R;
		SCROLLMANAGER->SetScrollX(-SCROLL_SPEED);
	}

	else {
		if(HIGHSCROLL == m_eCurrId) m_eCurrId = ARROW;
	}
	
	
	
}


void CMouseManager::SetMiniMapArea(RECT rc)
{
	m_tMiniMapRect = rc;
	RENDERMANAGER->LateInit();
}

void CMouseManager::SetBuild(OBJ_ID eId)
{
	m_eBuildId = eId;

}

void CMouseManager::MoveScrollByMouse()
{
	if (m_tPos.x >= m_tMiniMapRect.left && (m_tPos.x  - m_tMiniMapRect.left) <= m_tMiniMapRect.right &&
		m_tPos.y >= m_tMiniMapRect.top && m_tPos.y <= m_tMiniMapRect.bottom &&
		KEYMANAGER->KeyPressing(VK_LBUTTON)) {
		m_tPos.x = m_tPos.x - m_tMiniMapRect.left;
		m_tPos.y = m_tPos.y - m_tMiniMapRect.top;

		float fPercentX = static_cast<float>(m_tPos.x) / static_cast<float>(m_tMiniMapRect.right);
		float fPercentY = static_cast<float>(m_tPos.y) / static_cast<float>(m_tMiniMapRect.bottom - m_tMiniMapRect.top);

		SCROLLMANAGER->SetScrollXY(fPercentX, fPercentY);
	}
}

void CMouseManager::CheckMouseOver(UILIST& target)
{
	RECT rc{};

	for (auto& pTarget : target) {
		if (IntersectRect(&rc, &m_tRect, &(pTarget->GetRect()))) {
			pTarget->SetMouseOver();
		}

		else {
			pTarget->SetIdle();

		}
	}
}
