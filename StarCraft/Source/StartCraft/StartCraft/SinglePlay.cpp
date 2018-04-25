#include "stdafx.h"

#ifdef _DEBUG

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

CSinglePlay::CSinglePlay()
{
}


CSinglePlay::~CSinglePlay()
{
}

void CSinglePlay::Init()
{

	SCENEMANAGER->CreatePlayer();
}

SCENE_ID CSinglePlay::Update()
{
	return NO_EVENT;	
}

void CSinglePlay::Render()
{
	BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BITMAPMANAGER->GetImage()["STAGE1"]->GetDC(), 0, 0, SRCCOPY);

}

void CSinglePlay::Release()
{
}
