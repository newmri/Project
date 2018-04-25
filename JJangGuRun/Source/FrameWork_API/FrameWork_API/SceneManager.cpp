#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "GameOver.h"
#include "GameClear.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

void CSceneManager::SetState(const SCENE_ID eSceneID)
{
	switch (eSceneID) {
	case SCENE_ID::MAIN_MENU:
		SOUNDMANAGER->PlayeSound(MAINMENUBGM);
		m_bIsGameStarted = false;
		m_pScene = new CMainMenu; m_eSceneID = SCENE_ID::MAIN_MENU; break;

	case SCENE_ID::STAGE1:
		SOUNDMANAGER->PlayerEffectSound(START_EFSD);
		SOUNDMANAGER->PlayeSound(STAGE1BGM);

		m_bIsGameStarted = true;
		OBJMANAGER->LoadData();
		m_pScene = new CStage1; m_eSceneID = SCENE_ID::STAGE1; break;

	case SCENE_ID::GAME_OVER:
		ReSetAll();
		m_pScene = new CGameOver; m_eSceneID = SCENE_ID::GAME_OVER; break;

	case SCENE_ID::GAME_CLEAR:
		ReSetAll();
		m_pScene = new CGameClear; m_eSceneID = SCENE_ID::GAME_CLEAR; break;
	default: break;
	}
	m_pScene->Init();
}

void CSceneManager::Init()
{
	SetState(MAIN_MENU);
	m_bShowCollisionBox = false;
	m_bInvincibility = false;
	m_bIsPlayerDead = false;
	LateInit();

}

void CSceneManager::LateInit()
{

}

void CSceneManager::Update()
{
	if (KEYMANAGER->KeyDown(VK_F1)) m_bShowCollisionBox = !m_bShowCollisionBox;
	if (KEYMANAGER->KeyDown(VK_F2)) m_bInvincibility = !m_bInvincibility;

	SCENE_ID eSceneId = SCENE_ID::NO_EVENT;

	OBJMANAGER->Update();

	eSceneId = m_pScene->Update();

	if (eSceneId > SCENE_ID::NO_EVENT) {
		this->SetState(eSceneId);
		return;
	}
}

void CSceneManager::LateUpdate()
{

	OBJMANAGER->LateUpdate();

	if (!m_bInvincibility) {
		//COLLISIONMANAGER->RectCollision(obj_list[OBJTYPE::PLAYER], obj_list[OBJTYPE::ENEMY]);
	}

}


void CSceneManager::Render()
{
	if (SCENE_ID::GAME_OVER != m_eSceneID) {
		if (m_pScene)  m_pScene->Render();

		OBJMANAGER->Render();
	}
	if (nullptr != OBJMANAGER->GetPlayer()) {
		auto p = OBJMANAGER->GetPlayer();
		if (m_bInvincibility);
	}

	RenderDie();
}

void CSceneManager::Release()
{
	OBJMANAGER->Release();

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CSceneManager::RenderDie()
{
	if (m_bIsPlayerDead) {
		/*BITMAPMANAGER->GetImage()["DIE"]->TransparentBlt(RENDERMANAGER->GetMemDC(), (W_MAX / 2) - m_dieW / 2, (H_MAX / 2) - m_dieH / 2,
			m_dieW,
			m_dieH,
			0,
			0,
			m_dieW,
			m_dieH, RGB(0, 0, 0));*/
	}
	
}

void CSceneManager::CreatePlayer()
{
	CObj* p = CFactoryManager<CPlayer>::CreateObj();
	OBJMANAGER->AddObject(p, OBJTYPE::PLAYER);
}

void CSceneManager::CreateEnemy()
{
	CObj* p = CFactoryManager<CEnemy>::CreateObj();
	OBJMANAGER->AddObject(p, OBJTYPE::ENEMY);
}

void CSceneManager::ReSet()
{
	OBJMANAGER->ReSet();
	SCROLLMANAGER->ReSet();
	//CreatePlayer();
}

void CSceneManager::ReSetAll()
{
	OBJMANAGER->ReSet();
	SCROLLMANAGER->ReSet();
	OBJMANAGER->Init();
}

