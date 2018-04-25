#include "stdafx.h"
#include "Player.h"
//#ifdef _DEBUG
//
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif
//#endif

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Init()
{
	m_nProcessPercent = 0;
	SCENEMANAGER->CreatePlayer();
	SCENEMANAGER->CreateEnemy();

}

SCENE_ID CStage1::Update()
{
	
	if (OBJMANAGER->IsPlayerDead() || OBJMANAGER->GetPlayer()->GetInfo().fY > WINDOWS_HEIGHT) {
		return GAME_OVER;
	}

	if (OBJMANAGER->GetPlayer()->GetInfo().fX >= 530 && OBJMANAGER->GetPlayer()->GetInfo().fY <= -7846) {
		return GAME_CLEAR;
	}
	return NO_EVENT;	
}

void CStage1::Render()
{
	BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, BITMAPMANAGER->GetImage()["STAGE1"]->GetDC(), 0, 0, SRCCOPY);

}

void CStage1::Release()
{
}
