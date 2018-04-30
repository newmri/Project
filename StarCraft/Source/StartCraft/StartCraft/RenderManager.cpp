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

	m_tMiniMapFrameRect.left = m_tWindowSize.x / 110;
	m_tMiniMapFrameRect.right = m_tWindowSize.x * 0.09f - m_tMiniMapFrameRect.left;
	m_tMiniMapFrameRect.top = (m_tWindowSize.y - BITMAPMANAGER->GetImageInfo(BOTTOM_MENU_IMAGE)->nImageH) + 69;
	m_tMiniMapFrameRect.bottom = m_tMiniMapFrameRect.top + m_tWindowSize.y * 0.03f;

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

	m_tMiniMapFrameRect.left = (m_tWindowSize.x / 110) - (fScrollX * 0.075);
	m_tMiniMapFrameRect.right = (m_tWindowSize.x * 0.075f) + m_tMiniMapFrameRect.left;
	m_tMiniMapFrameRect.top = (m_tWindowSize.y - BITMAPMANAGER->GetImageInfo(BOTTOM_MENU_IMAGE)->nImageH) + 69;
	m_tMiniMapFrameRect.top = m_tMiniMapFrameRect.top - (fScrollY * 0.041);
	m_tMiniMapFrameRect.bottom = m_tMiniMapFrameRect.top + m_tWindowSize.y * 0.03f;
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



