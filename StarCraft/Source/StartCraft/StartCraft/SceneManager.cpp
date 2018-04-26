#include "stdafx.h"
#include "Player.h"
#include "SinglePlay.h"
#include "SinglePlay.h"
#include "MultiPlay.h"
#include "Editor.h"
#include "Exit.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

void CSceneManager::SetState(const SCENE::SCENE_ID eSceneID)
{
	switch (eSceneID) {
	case SCENE::SCENE_ID::MAIN_MENU:
		m_bIsGameStarted = false;
		m_pScene = new CMainMenu; m_eSceneID = SCENE::SCENE_ID::MAIN_MENU; break;

	//case SCENE_ID::STAGE1:
	//	m_bIsGameStarted = true;
	//	//SOUNDMANAGER->PlayeSound(STAGE1BGM);
	//	m_pScene = new CSinglePlay; m_eSceneID = SCENE_ID::STAGE1; break;

	default: break;
	}
	m_pScene->Init();
}

void CSceneManager::Init()
{
	SetState(SCENE::MAIN_MENU);
	m_bShowCollisionBox = false;
	m_bInvincibility = false;
	m_bIsPlayerDead = false;
	LateInit();


}

void CSceneManager::LateInit()
{
	float w = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
	float h = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));

	{
		CScene* p = CFactoryManager<CSinglePlay>::CreateScene(w * 0.2f, h * 0.2f);
		SCENEMANAGER->AddScene(p, SCENE::SINGLE_PLAY);
	}

	{
		CScene* p = CFactoryManager<CEditor>::CreateScene(w * 0.6f, h * 0.3f);
		SCENEMANAGER->AddScene(p, SCENE::EDITOR);

	}

	{
		CScene* p = CFactoryManager<CMultiPlay>::CreateScene(w * 0.3f, h * 0.6f);
		SCENEMANAGER->AddScene(p, SCENE::MULTI_PLAY);

	}

	{
		CScene* p = CFactoryManager<CExit>::CreateScene(w * 0.7f, h * 0.6f);
		SCENEMANAGER->AddScene(p, SCENE::EXIT);

	}

	for (int i = SCENE::SINGLE_PLAY; i < SCENE::SCENE_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->LateInit();
			it_begin++;
		}

	}
}

void CSceneManager::Update()
{
	if (KEYMANAGER->KeyDown(VK_F1)) m_bShowCollisionBox = !m_bShowCollisionBox;
	if (KEYMANAGER->KeyDown(VK_F2)) m_bInvincibility = !m_bInvincibility;

	SCENE::SCENE_ID eSceneId = SCENE::SCENE_ID::NO_EVENT;

	OBJMANAGER->Update();

	for (int i = SCENE::SINGLE_PLAY; i < SCENE::SCENE_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->Update();
			it_begin++;
		}

	}

	eSceneId = m_pScene->Update();

	if (eSceneId > SCENE::SCENE_ID::NO_EVENT){
		this->SetState(eSceneId);
		return;
	}

}

void CSceneManager::LateUpdate()
{

	OBJMANAGER->LateUpdate();

	for (int i = SCENE::SINGLE_PLAY; i < SCENE::SCENE_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->LateUpdate();
			it_begin++;
		}

	}

	MOUSEMANAGER->CheckMouseOver(m_objList[SCENE::SINGLE_PLAY]);
	MOUSEMANAGER->CheckMouseOver(m_objList[SCENE::MULTI_PLAY]);

	MOUSEMANAGER->CheckMouseOver(m_objList[SCENE::EDITOR]);
	MOUSEMANAGER->CheckMouseOver(m_objList[SCENE::EXIT]);

	if (!m_bInvincibility) {
		//COLLISIONMANAGER->RectCollision(obj_list[OBJTYPE::PLAYER], obj_list[OBJTYPE::ENEMY]);
	}

}


void CSceneManager::Render()
{
	if (m_pScene)  m_pScene->Render(); 

	for (int i = 1; i < SCENE::SCENE_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->RenderCollsionBox();
			(*it_begin)->Render();
			it_begin++;
		}
	}

	OBJMANAGER->Render();


	RenderDie();
}

void CSceneManager::Release()
{
	OBJMANAGER->Release();

	for (int i = 0; i < SCENE::SCENE_END; ++i) {
		for_each(m_objList[i].begin(), m_objList[i].end(),
			[](auto& obj)
		{
			if (obj)
			{
				delete obj;
				obj = nullptr;
			}
		});
		m_objList[i].clear();
	}


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

void CSceneManager::AddScene(CScene* pObj, SCENE::SCENE_ID eID)
{
	m_objList[eID].push_back(pObj);
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

