#include "stdafx.h"
#include "GameOver.h"
#include <Vfw.h>

#pragma comment(lib,"Vfw32.lib")

void CGameOver::Init()
{
	m_hVideo = MCIWndCreate(RENDERMANAGER->GethWnd(), NULL, MCIWNDF_NOTIFYPOS | MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"Resources/Movie/GameOver.wmv");
	SOUNDMANAGER->BGSoundOff();
	SetWindowPos(m_hVideo, NULL, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, SWP_NOZORDER);
	if (m_hVideo) MCIWndPlay(m_hVideo);
}

SCENE_ID CGameOver::Update()
{
	if (GetAsyncKeyState(VK_RETURN)) {
		Release();
		return MAIN_MENU;
	}
	
	return NO_EVENT;
}

void CGameOver::Render()
{
}

void CGameOver::Release()
{
	MCIWndClose(m_hVideo);
}

CGameOver::~CGameOver()
{
	
}
