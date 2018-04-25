#include "stdafx.h"
#include "Stage1.h"

CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Init()
{
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
	BITMAPMANAGER->GetImage()["MAINMENU"]->BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0, 0, SRCCOPY);
}

void CMainMenu::Release()
{
}
