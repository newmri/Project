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
	if (m_tAnimationInfo[m_eCurrId].dwAnimationTime + 1000 / m_tAnimationInfo[m_eCurrId].nAnimationNum < GetTickCount()) {

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

	}
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
				m_tSelectRenderRect.left -= 10;
				m_tSelectRenderRect.right -= 10;
				m_tSelectRenderRect.top += 10;
				m_tSelectRenderRect.bottom += 10;

				if (GREEN == d->GetOwnerId()) {
					m_eCurrId = MAGG;
					m_tAnimationInfo[m_eCurrId].nCnt = 0;
				}
				return;
			}
		}
	}
	m_bIsSelectedObj = false;

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


void CMouseManager::MoveScrollByMouse()
{
	if (m_tPos.x >= m_tMiniMapRect.left && m_tPos.x <= m_tMiniMapRect.right &&
		m_tPos.y >= m_tMiniMapRect.top && m_tPos.x <= m_tMiniMapRect.bottom &&
		KEYMANAGER->KeyPressing(VK_LBUTTON)) {
		if(m_tPos.x <= m_tMiniMapRect.right / 2) m_tPos.x = m_tPos.x - m_tMiniMapRect.left;

		m_tPos.y = m_tPos.y - m_tMiniMapRect.top;

		SCROLLMANAGER->SetScrollXY( static_cast<LONG>(m_tPos.x * (SCROLLMANAGER->GetScrollEndPos().x / m_tMiniMapRect.right)),
			static_cast<LONG>(m_tPos.y * (SCROLLMANAGER->GetScrollEndPos().y / (m_tMiniMapRect.bottom - m_tMiniMapRect.top))));
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
