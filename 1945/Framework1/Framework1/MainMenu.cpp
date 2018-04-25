#include "stdafx.h"

CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Initialize()
{
	SOUNDMANAGER->PlayeSound(MAINMENUBGM);
}

SCENE_ID CMainMenu::Update()
{
	if (GetAsyncKeyState(VK_RETURN)) {
		SOUNDMANAGER->PlayeSound(STARTBGM);
		return STAGE1;
	}
	return NO_EVENT;
}

void CMainMenu::Render()
{
	BITMAPMANAGER->GetImage()["MAINMENU"]->BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, W_MAX, H_MAX, 0, 0, SRCCOPY);
}

void CMainMenu::Release()
{
}
