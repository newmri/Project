#include "stdafx.h"


CMainMenu::CMainMenu()
{
	
}


CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Init()
{
	m_tImageSize.x = BITMAPMANAGER->GetImage()["MAIN_MENU"]->GetWidth();
	m_tImageSize.y = BITMAPMANAGER->GetImage()["MAIN_MENU"]->GetHeight();

	float w = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
	float h = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));

}

void CMainMenu::LateInit()
{
}

SCENE::SCENE_ID CMainMenu::Update()
{
	if (KEYMANAGER->KeyDown(VK_ESCAPE)) DestroyWindow(RENDERMANAGER->GethWnd());
	if (KEYMANAGER->KeyDown('X')) DestroyWindow(RENDERMANAGER->GethWnd());

	
	return SCENE::NO_EVENT;
}

void CMainMenu::LateUpdate()
{
}

void CMainMenu::Render()
{
	StretchBlt(RENDERMANAGER->GetMemDC(), 0, 0, GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		BITMAPMANAGER->GetImage()["MAIN_MENU"]->GetDC(), 0, 0,
		m_tImageSize.x, m_tImageSize.y, SRCCOPY);
	
}

void CMainMenu::Release()
{
}
