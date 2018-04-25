#include "stdafx.h"
#include "SinglePlay.h"
#include "SinglePlayUI.h"

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

	CObj* p = CFactoryManager<CSinglePlayUI>::CreateObj(m_tImageSize.x * 0.4, m_tImageSize.y * 0.4);
	OBJMANAGER->AddObject(p, SINGLE_PLAY);
	SOUNDMANAGER->PlayeSound(MAINMENUBGM);
}

SCENE_ID CMainMenu::Update()
{
	if (KEYMANAGER->KeyDown(VK_RETURN)) {
		return STAGE1;
	}
	return NO_EVENT;
}

void CMainMenu::Render()
{
	StretchBlt(RENDERMANAGER->GetMemDC(), 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BITMAPMANAGER->GetImage()["MAIN_MENU"]->GetDC(), 0, 0,
		m_tImageSize.x, m_tImageSize.y, SRCCOPY);
	
}

void CMainMenu::Release()
{
}
