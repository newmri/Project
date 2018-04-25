#include "stdafx.h"
#include "Stage2.h"


CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Initialize()
{
	m_nImageHeight = static_cast<float>(BITMAPMANAGER->GetImage()["STAGE2"]->GetHeight());

	m_nY = m_nImageHeight - H_MAX;
	m_nProcessPercent = (m_nY / (m_nImageHeight - H_MAX)) * 100;

	m_createNormalEnemyTime = GetTickCount();
	m_nextStageTime = 0;
	m_bBossIsCreated = false;


	CreateNormalEnemy();

}

SCENE_ID CStage2::Update()
{
	m_nProcessPercent = (m_nY / (m_nImageHeight - H_MAX)) * 100;


	if (m_nY > 0) m_nY -= m_nImageHeight / STAGE_SPEED;

	if (m_nY + H_MAX <= 0) m_nY += m_nImageHeight;

	if (m_nProcessPercent <= 0) {
		if (!m_bBossIsCreated) {
			CreateBoss("BOSS2");
			m_bBossIsCreated = true;
		}

		else {
			if (SCENEMANAGER->IsBossDead()) {
				if (m_nextStageTime == 0) m_nextStageTime = GetTickCount();
				else if (m_nextStageTime + 10000 < GetTickCount()) {
					SCENEMANAGER->ReSetAll();

					return MAIN_MENU;
				}
			}
		}

		if (!SCENEMANAGER->IsBossDead() && m_createNormalEnemyTime + NORMAL_ENEMY_NEXT_SPAWN_TIME< GetTickCount()) {
			m_createNormalEnemyTime = GetTickCount();
			CreateNormalEnemy();
		}
	}

	if (m_createNormalEnemyTime + NORMAL_ENEMY_NEXT_SPAWN_TIME< GetTickCount()) {
		m_createNormalEnemyTime = GetTickCount();
		CreateNormalEnemy();
	}
	return NO_EVENT;
}

void CStage2::Render()
{
	if (m_nY < 0) {
		BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, W_MAX, static_cast<int>(-m_nY),
			BITMAPMANAGER->GetImage()["STAGE2"]->GetDC(), 0, static_cast<int>(m_nImageHeight + m_nY), SRCCOPY);

		BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, W_MAX,
			static_cast<int>(m_nY) + H_MAX, BITMAPMANAGER->GetImage()["STAGE2"]->GetDC(), 0, 0, SRCCOPY);

	}
	else BitBlt(RENDERMANAGER->GetMemDC(), 0, 0, W_MAX, H_MAX, BITMAPMANAGER->GetImage()["STAGE2"]->GetDC(), 0, static_cast<int>(m_nY), SRCCOPY);
}

void CStage2::Release()
{
}
