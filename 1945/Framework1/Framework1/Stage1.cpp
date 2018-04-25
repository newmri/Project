#include "stdafx.h"
#include "Stage1.h"
//
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

void CStage1::Initialize()
{
	m_nImageHeight = static_cast<float>(BITMAPMANAGER->GetImage()["STAGE1"]->GetHeight());

	m_nY = m_nImageHeight - H_MAX;
	m_nProcessPercent = (m_nY / (m_nImageHeight - H_MAX)) * 100;
	SCENEMANAGER->CreatePlayer();

	m_createNormalEnemyTime = GetTickCount();

	CreateNormalEnemy();
	
	m_bBossIsCreated = false;
	m_nextStageTime = 0;


}

SCENE_ID CStage1::Update()
{
	m_nProcessPercent = (m_nY / (m_nImageHeight - H_MAX)) * 100;


	if (m_nY > 0) m_nY -= m_nImageHeight / STAGE_SPEED;
	if (m_nY + H_MAX <= 0) m_nY += m_nImageHeight;

	if(m_nProcessPercent <= 0){
		if (!m_bBossIsCreated) {
			CreateBoss("BOSS1");
			m_bBossIsCreated = true;
		}
		else {
			if (SCENEMANAGER->IsBossDead()) {
				if (m_nextStageTime == 0) m_nextStageTime = GetTickCount();
				else if (m_nextStageTime + 10000 < GetTickCount()) return STAGE2;

			}
		}

		if (!SCENEMANAGER->IsBossDead() && m_createNormalEnemyTime + NORMAL_ENEMY_NEXT_SPAWN_TIME < GetTickCount()) {
			m_createNormalEnemyTime = GetTickCount();
			CreateNormalEnemy();
		}
	}

	if (!m_bBossIsCreated && m_createNormalEnemyTime + NORMAL_ENEMY_NEXT_SPAWN_TIME < GetTickCount()) {
		m_createNormalEnemyTime = GetTickCount();
		CreateNormalEnemy();
	}
	return NO_EVENT;
}

void CStage1::Render()
{
	if (m_nY < 0) {
		BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, W_MAX, static_cast<int>(-m_nY), 
			BITMAPMANAGER->GetImage()["STAGE1"]->GetDC(), 0, static_cast<int>(m_nImageHeight + m_nY), SRCCOPY);

		BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, W_MAX, 
			static_cast<int>(m_nY) + H_MAX, BITMAPMANAGER->GetImage()["STAGE1"]->GetDC(), 0, 0, SRCCOPY);

	}
	else BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, W_MAX, H_MAX, BITMAPMANAGER->GetImage()["STAGE1"]->GetDC(), 0, static_cast<int>(m_nY), SRCCOPY);

}

void CStage1::Release()
{
}
