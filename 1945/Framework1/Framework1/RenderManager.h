#pragma once

#include <Windows.h>

class CRenderManager
{

public:
	void Initialize(const HWND& hWnd);
	void Release();

public:
	void Render();

public:
	const HDC& GetMemDC() { return m_hMemDC; }
	const HWND& GethWnd() { return m_hWnd; }
	const RECT& GetRect() { return m_Rect; }

public:
	static CRenderManager* GetInstance()
	{
		if (m_instance == nullptr) m_instance = new CRenderManager;
		return m_instance;
	}

	~CRenderManager();
private:
	CRenderManager();
	CRenderManager(const CRenderManager&) = delete;
	void operator=(const CRenderManager&) = delete;

private:
	static CRenderManager* m_instance;

private:
	HDC m_hDC, m_hMemDC;
	HBITMAP m_hBit, m_hOldBit;
	HWND m_hWnd;
	RECT m_Rect;
};