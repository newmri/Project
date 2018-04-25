#pragma once

#include <Windows.h>

class CRenderManager
{
public:
	void Init(const HWND& hWnd);
	void Release();

public:
	void Render();

public:
	const HDC& GetMemDC() { return m_hMemDC; }
	const HWND& GethWnd() { return m_hWnd; }
	const RECT& GetRect() { return m_rect; }

public:
	static CRenderManager* GetInstance()
	{
		if (m_pInstance == nullptr) m_pInstance = new CRenderManager;
		return m_pInstance;
	}

private:
	CRenderManager() = default;
	~CRenderManager() = default;
	CRenderManager(const CRenderManager&) = delete;
	void operator=(const CRenderManager&) = delete;

private:
	static CRenderManager* m_pInstance;

private:
	HDC			m_hDC, m_hMemDC;
	HBITMAP		m_hBit, m_hOldBit;
	HWND		m_hWnd;
	RECT		m_rect;
};