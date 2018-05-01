#include "stdafx.h"
#include "Obj.h"
#include "Scene.h"
#include "Button.h"
#include "Tile.h"

CMouseManager*	CMouseManager::m_pInstance = nullptr;

void CMouseManager::Init()
{
	m_eCurrId = ARROW;
	m_bIsSelectedObj = false;
	m_bIsDragging = false;
	m_nAnimationIdx = 0;
	m_eSelectedPortraitId = PORTRAIT::PORTRAIT_END;

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
		p = BITMAPMANAGER->GetPortraitImageInfo(PORTRAIT::ADVISOR);
		for (int i = 0; i < p[0].nImageNum; ++i) {
			STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

			memcpy(&pTemp->tInfo, &p[i], sizeof(IMAGE_INFO));

			pTemp->tPos.x = 994;
			pTemp->tPos.y = 770;
			pTemp->tDrawSize.x = pTemp->tInfo.nImageW * 2.3;
			pTemp->tDrawSize.y = pTemp->tInfo.nImageH + 5;
			pTemp->tColor = RGB(0, 0, 0);

			m_uiList.push_back(pTemp);
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

	if(HIGHSCROLL != m_eCurrId && LOWSCROLL != m_eCurrId)
	if (m_tAnimationInfo[m_eCurrId].dwAnimationTime + 500 < GetTickCount()) {

		m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % m_tAnimationInfo[m_eCurrId].nAnimationNum;
		m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
	}

	if (m_bIsSelectedObj) {
		if(m_tPos.x + TILE_SIZE < m_tSelectRect.left ||
			m_tPos.x + TILE_SIZE > m_tSelectRect.right ||
			m_tPos.y < m_tSelectRect.top ||
			m_tPos.y > m_tSelectRect.bottom){

			m_eCurrId = ARROW;
		}

	}

	CheckDragSelectObj();
}

void CMouseManager::Render()
{
	UpdateRect();

	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_tPos.x - CURSOR_SIZE / 2,
		m_tPos.y - CURSOR_SIZE / 2,
		CURSOR_SIZE,
		CURSOR_SIZE,
		0,
		0,
		CURSOR_SIZE,
		CURSOR_SIZE, RGB(0, 0, 0));

	if (m_bIsSelectedObj) {
		BITMAPMANAGER->GetImage()[m_tSelectImage[m_eSelectedUnitsize].szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_tSelectRenderRect.left + SCROLLMANAGER->GetScrollX()),
			static_cast<int>(m_tSelectRenderRect.top + SCROLLMANAGER->GetScrollY()),
			m_tSelectImage[m_eSelectedUnitsize].nImageW,
			m_tSelectImage[m_eSelectedUnitsize].nImageH,
			0,
			0,
			m_tSelectImage[m_eSelectedUnitsize].nImageW,
			m_tSelectImage[m_eSelectedUnitsize].nImageH, RGB(255, 255, 255));

		RenderUI();

	}

	if (m_bIsDragging) RenderDragRect();
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

	if (m_dwAnimationTime + 1000 / m_uiList[m_nAnimationIdx]->tInfo.nImageNum < GetTickCount()) {
		m_dwAnimationTime = GetTickCount();
		m_nAnimationIdx = (m_nAnimationIdx + 1) % m_uiList[m_nAnimationIdx]->tInfo.nImageNum;
	}
	BITMAPMANAGER->GetImage()[m_uiList[m_nAnimationIdx]->tInfo.szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_uiList[m_nAnimationIdx]->tPos.x,
		m_uiList[m_nAnimationIdx]->tPos.y,
		m_uiList[m_nAnimationIdx]->tDrawSize.x,
		m_uiList[m_nAnimationIdx]->tDrawSize.y,
		0,
		0,
		m_uiList[m_nAnimationIdx]->tInfo.nImageW,
		m_uiList[m_nAnimationIdx]->tInfo.nImageH, m_uiList[m_nAnimationIdx]->tColor);
}

void CMouseManager::CheckSwapTile()
{

	CObj* pTile = GetTile();

	if (nullptr == pTile) return;

	dynamic_cast<CTile*>(pTile)->SwapTile();
}

void CMouseManager::CheckSelectObj()
{
	CObj* pTile = GetTile();

	if (nullptr == pTile) return;

	for (int i = BARRACK; i < OBJ_END; ++i) {
		OBJLIST list = OBJMANAGER->GetObj(static_cast<OBJ_ID>(i));
		for (auto& d : list) {
			if (d->IsClicked(m_tPos)) {
				m_bIsSelectedObj = true;
				m_tSelectRect = d->GetSelectRect();
				m_eSelectedUnitsize = d->GetSize();
				m_tSelectRenderRect = d->GetRect();
				m_eSelectedPortraitId = d->GetPortraitId();

				m_tSelectRenderRect.left -= 10;
				m_tSelectRenderRect.right -= 10;
				m_tSelectRenderRect.top -= 10;
				m_tSelectRenderRect.bottom -= 10;

				if (GREEN == d->GetOwnerId()) {
					m_eCurrId = MAGG;
					m_tAnimationInfo[m_eCurrId].nCnt = 0;
				}

				m_dwAnimationTime = GetTickCount();

				return;
			}
		}
	}
	m_bIsSelectedObj = false;

}

void CMouseManager::CheckDragSelectObj()
{
	
	if (m_bIsDragging) {
		if (KEYMANAGER->KeyUp(VK_LBUTTON)) {
			m_bIsDragging = false;
			m_tAnimationInfo[m_eCurrId].nCnt = 0;
			m_eCurrId = ARROW;

			MOUSEMANAGER->CheckSelectObj();
			return;
		}
	}


	if (KEYMANAGER->KeyPressing(VK_LBUTTON)) {
		cout << m_tPos.x << ", " << m_tPos.y << endl;
		if (!m_bIsDragging) {
			m_tDragPos[DRAG_START_POS] = m_tPos;
			m_bIsDragging = true;
			m_tAnimationInfo[m_eCurrId].nCnt = 0;
			m_eCurrId = DRAG;
		}

		if (m_bIsDragging) m_tDragPos[DRAG_END_POS] = m_tPos;
		
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

void CMouseManager::MoveScrollByMouse()
{
	if (m_tPos.x >= m_tMiniMapRect.left && (m_tPos.x  - m_tMiniMapRect.left) <= m_tMiniMapRect.right &&
		m_tPos.y >= m_tMiniMapRect.top && m_tPos.y <= m_tMiniMapRect.bottom &&
		KEYMANAGER->KeyPressing(VK_LBUTTON)) {
		m_tPos.x = m_tPos.x - m_tMiniMapRect.left;
		m_tPos.y = m_tPos.y - m_tMiniMapRect.top;

		float fPercentX = static_cast<float>(m_tPos.x) / static_cast<float>(m_tMiniMapRect.right);
		float fPercentY = static_cast<float>(m_tPos.y + 5) / static_cast<float>(m_tMiniMapRect.bottom - m_tMiniMapRect.top);

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
