#include "stdafx.h"
#include "Player.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

void CSceneManager::SetState(const SCENE_ID eSceneID)
{
	switch (eSceneID) {
	case SCENE_ID::MAIN_MENU:
		m_bIsGameStarted = false;
		m_pScene = new CMainMenu; m_eSceneID = SCENE_ID::MAIN_MENU; break;

	case SCENE_ID::STAGE1:
		m_bIsGameStarted = true;
		//SOUNDMANAGER->PlayeSound(STAGE1BGM);
		m_pScene = new CSinglePlay; m_eSceneID = SCENE_ID::STAGE1; break;

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

	if (eSceneId > SCENE_ID::NO_EVENT){
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
	if (m_pScene)  m_pScene->Render(); 

	OBJMANAGER->Render();

	/*if (nullptr != OBJMANAGER->GetPlayer()) {
		auto p = OBJMANAGER->GetPlayer();
		if (m_bInvincibility);
	}
*/
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
	OBJMANAGER->AddObject(p, OBJ_ID::PLAYER);
}

void CSceneManager::ReSet()
{
	OBJMANAGER->ReSet();
	CreatePlayer();
}

void CSceneManager::ReSetAll()
{
	OBJMANAGER->ReSet();
	Init();
}

