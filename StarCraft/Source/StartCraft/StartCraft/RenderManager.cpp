#include "stdafx.h"

CRenderManager* CRenderManager::m_pInstance = nullptr;

void CRenderManager::Init(const HWND& hWnd)
{
	BITMAPMANAGER->Init();

	RECT rc;
	GetClientRect(hWnd, &rc);
	m_tWindowSize.x = rc.right - rc.left;
	m_tWindowSize.y = rc.bottom - rc.top;

	m_hWnd = hWnd;
	m_hDC = GetDC(m_hWnd);
	m_hBit = CreateCompatibleBitmap(m_hDC, m_tWindowSize.x, m_tWindowSize.y);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	SetBkColor(m_hMemDC, RGB(0, 0, 0));



	
}

void CRenderManager::LateInit()
{
float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(MAIN_MAP_IMAGE);

	int x = MOUSEMANAGER->GetMiniMapArea().right - MOUSEMANAGER->GetMiniMapArea().left;
	int y = MOUSEMANAGER->GetMiniMapArea().bottom - MOUSEMANAGER->GetMiniMapArea().top;

	float fSizeX = m_tMiniMapFrameRect.right - m_tMiniMapFrameRect.left;
	float fMapSizeX = MOUSEMANAGER->GetMiniMapArea().right - MOUSEMANAGER->GetMiniMapArea().left;
	float fSizeY = m_tMiniMapFrameRect.bottom - m_tMiniMapFrameRect.top;
	float fMapSizeY = MOUSEMANAGER->GetMiniMapArea().bottom - MOUSEMANAGER->GetMiniMapArea().top;

	float fRatio = (1.f - (fSizeX / fMapSizeX));

	m_tMiniMapFrameRect.left = MOUSEMANAGER->GetMiniMapArea().left;
	m_tMiniMapFrameRect.left += (x * (fScrollX / static_cast<float>(SCROLLMANAGER->GetScrollEndPos().x))) * fRatio;

	m_tMiniMapFrameRect.right = static_cast<LONG>((static_cast<float>(m_tWindowSize.x) /
		static_cast<float>(p->nImageW)) * MOUSEMANAGER->GetMiniMapArea().right);
	m_tMiniMapFrameRect.right += m_tMiniMapFrameRect.left;

	fRatio = (1.f - (fSizeY / fMapSizeY)) * 0.97f;
	m_tMiniMapFrameRect.top = MOUSEMANAGER->GetMiniMapArea().top;
	m_tMiniMapFrameRect.top += (y * (fScrollY / static_cast<float>(SCROLLMANAGER->GetScrollEndPos().y))) * fRatio;

	m_tMiniMapFrameRect.bottom = m_tMiniMapFrameRect.top +
		static_cast<LONG>((static_cast<float>(m_tWindowSize.y) / static_cast<float>(p->nImageH)) *
		(MOUSEMANAGER->GetMiniMapArea().bottom - MOUSEMANAGER->GetMiniMapArea().top));

}

void CRenderManager::Release()
{
	SelectObject(m_hMemDC, m_hOldBit);
	DeleteObject(m_hBit);

	ReleaseDC(m_hWnd, m_hMemDC);

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CRenderManager::Render()
{
	m_hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBit);
	BitBlt(m_hDC, 0, 0, m_tWindowSize.x, m_tWindowSize.y, m_hMemDC, 0, 0, SRCCOPY);

}

void CRenderManager::UpdateMiniMapFrame()
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(MAIN_MAP_IMAGE);

	int x = MOUSEMANAGER->GetMiniMapArea().right - MOUSEMANAGER->GetMiniMapArea().left;
	int y = MOUSEMANAGER->GetMiniMapArea().bottom - MOUSEMANAGER->GetMiniMapArea().top;

	float fSizeX = m_tMiniMapFrameRect.right - m_tMiniMapFrameRect.left;
	float fMapSizeX = MOUSEMANAGER->GetMiniMapArea().right - MOUSEMANAGER->GetMiniMapArea().left;
	float fSizeY = m_tMiniMapFrameRect.bottom - m_tMiniMapFrameRect.top;
	float fMapSizeY = MOUSEMANAGER->GetMiniMapArea().bottom - MOUSEMANAGER->GetMiniMapArea().top;

	float fRatio = (1.f - (fSizeX / fMapSizeX)) * 1.1f;

	m_tMiniMapFrameRect.left = MOUSEMANAGER->GetMiniMapArea().left;
	m_tMiniMapFrameRect.left += (x * (fScrollX / static_cast<float>(SCROLLMANAGER->GetScrollEndPos().x))) * fRatio;

	m_tMiniMapFrameRect.right = static_cast<LONG>((static_cast<float>(m_tWindowSize.x) /
		static_cast<float>(p->nImageW)) * MOUSEMANAGER->GetMiniMapArea().right);
	m_tMiniMapFrameRect.right += m_tMiniMapFrameRect.left;

	fRatio = (1.f - (fSizeY / fMapSizeY)) * 0.97f;
	m_tMiniMapFrameRect.top = MOUSEMANAGER->GetMiniMapArea().top;
	m_tMiniMapFrameRect.top += (y * (fScrollY / static_cast<float>(SCROLLMANAGER->GetScrollEndPos().y))) * fRatio;

	m_tMiniMapFrameRect.bottom = m_tMiniMapFrameRect.top +
		static_cast<LONG>((static_cast<float>(m_tWindowSize.y) / static_cast<float>(p->nImageH)) *
		(MOUSEMANAGER->GetMiniMapArea().bottom - MOUSEMANAGER->GetMiniMapArea().top));

}

void CRenderManager::RenderMiniMapFrame()
{
	UpdateMiniMapFrame();

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hMemDC, myBrush);
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(m_hMemDC, hNewPen);
	Rectangle(m_hMemDC, m_tMiniMapFrameRect.left, m_tMiniMapFrameRect.top, m_tMiniMapFrameRect.right, m_tMiniMapFrameRect.bottom);
	SelectObject(m_hMemDC, hNewPen);
	DeleteObject(hOldPen);
	SelectObject(m_hMemDC, oldBrush);
	DeleteObject(myBrush);
}



