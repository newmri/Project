#include "stdafx.h"
#include "Player.h"
#include "SinglePlay.h"
#include "MultiPlay.h"
#include "Editor.h"
#include "Exit.h"
#include "UI.h"
#include "Button.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

void CSceneManager::SetState(const SCENE::SCENE_ID eSceneID)
{
	if (eSceneID != m_eSceneID) {

		SafeDelete(m_pScene);

		switch (eSceneID) {
		case SCENE::SCENE_ID::MAIN_MENU:
			m_bIsGameStarted = false;
			m_pScene = new CMainMenu; m_eSceneID = SCENE::SCENE_ID::MAIN_MENU; break;

		case SCENE::SINGLE_PLAY:
			TILEMANAGER->LoadData();
			m_bIsGameStarted = true;
			m_pScene = new CSinglePlay; m_eSceneID = SCENE::SINGLE_PLAY; break;

		case SCENE::EDITOR:
			TILEMANAGER->LoadData();
			m_pScene = new CEditor; m_eSceneID = SCENE::EDITOR; break;

		default: break;
		}


		m_pScene->Init();
	}
}

void CSceneManager::Init()
{
	m_pScene = nullptr;
	m_bIsGameStarted = false;
	SetState(SCENE::MAIN_MENU);
	m_bShowCollisionBox = false;
	m_bInvincibility = false;

	LateInit();

}

void CSceneManager::LateInit()
{
	m_pScene->LateInit();
}

void CSceneManager::Update()
{
	if (KEYMANAGER->KeyDown(VK_F1)) m_bShowCollisionBox = !m_bShowCollisionBox;
	if (KEYMANAGER->KeyDown(VK_F2)) m_bInvincibility = !m_bInvincibility;

	SCENE::SCENE_ID eSceneId = SCENE::SCENE_ID::NO_EVENT;

	OBJMANAGER->Update();

	eSceneId = m_pScene->Update();

	if (eSceneId != SCENE::SCENE_ID::NO_EVENT) {
		this->SetState(eSceneId);
		return;
	}

}

void CSceneManager::LateUpdate()
{

	OBJMANAGER->LateUpdate();
	m_pScene->LateUpdate();


	if (!m_bInvincibility) {
		//COLLISIONMANAGER->RectCollision(obj_list[OBJTYPE::PLAYER], obj_list[OBJTYPE::ENEMY]);
	}

}


void CSceneManager::Render()
{
	if (m_pScene)  m_pScene->Render();
	OBJMANAGER->Render();

}

void CSceneManager::Release()
{
	OBJMANAGER->Release();

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}


CButton* CSceneManager::GetButton(BUTTON_ID eId)
{
	return m_pScene->GetButton(eId);
}


void CSceneManager::ReSet()
{
	OBJMANAGER->ReSet();
}

void CSceneManager::ReSetAll()
{
	OBJMANAGER->ReSet();
	Init();
}

