#include "stdafx.h"

CRenderManager* CRenderManager::m_pInstance = nullptr;

void CRenderManager::Init(const HWND& hWnd)
{
	m_tWindowSize.x = GetSystemMetrics(SM_CXSCREEN);
	m_tWindowSize.y = GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = hWnd;
	m_hDC = GetDC(m_hWnd);
	m_hBit = CreateCompatibleBitmap(m_hDC, m_tWindowSize.x, m_tWindowSize.y);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	SetBkColor(m_hMemDC, RGB(0, 0, 0));

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


