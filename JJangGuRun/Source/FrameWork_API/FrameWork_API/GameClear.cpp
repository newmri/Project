#include "stdafx.h"
#include "GameClear.h"

void CGameClear::Init()
{
}

SCENE_ID CGameClear::Update()
{
	if (GetAsyncKeyState(VK_RETURN)) {
		return MAIN_MENU;
	}
}

void CGameClear::Render()
{
	BITMAPMANAGER->GetImage()["GAMECLEAR"]->BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0, 0, SRCCOPY);
}

void CGameClear::Release()
{
}

CGameClear::~CGameClear()
{
	Release();
}
