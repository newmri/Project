#include "stdafx.h"

CRenderManager* CRenderManager::m_instance = nullptr;

void CRenderManager::Initialize(const HWND& hWnd)
{
	m_hWnd = hWnd;
	m_hDC = GetDC(m_hWnd);
	m_hBit = CreateCompatibleBitmap(m_hDC, W_MAX, H_MAX);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	SetBkColor(m_hMemDC, RGB(0, 0, 0));

	GetClientRect(m_hWnd, &m_Rect);
}

void CRenderManager::Release()
{
	ObjDelete(m_instance);
}

void CRenderManager::Render()
{
	m_hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBit);
	BitBlt(m_hDC, 0, 0, W_MAX, H_MAX, m_hMemDC, 0, 0, SRCCOPY);
}

CRenderManager::~CRenderManager()
{
	Release();
}

CRenderManager::CRenderManager()
{

}
