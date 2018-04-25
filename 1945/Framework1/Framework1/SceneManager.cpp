#include "stdafx.h"
#include "SceneManager.h"
#include "Player.h"
#include "Item.h"

CSceneManager* CSceneManager::m_instance = nullptr;

CSceneManager::CSceneManager() : m_pScene(nullptr) {}
CSceneManager::~CSceneManager()
{
	Release();

	for (int i = 0; i < OBJ_ARR::END; i++)
	{
		for (auto& a : obj_list[i])
		{
			ObjDelete(a);
		}
		obj_list[i].clear();
	}

	ObjDelete(m_instance);
}

void  CSceneManager::SetState(const SCENE_ID a_SceneId)
{
	this->Release();

	switch (a_SceneId){
	case SCENE_ID::MAIN_MENU:
		m_gameStart = false;
		m_pScene = new CMainMenu; m_SceneID = SCENE_ID::MAIN_MENU; break;
	case SCENE_ID::STAGE1:
		m_gameStart = true;
		Sleep(4000);
		SOUNDMANAGER->PlayeSound(STAGE1BGM);
		m_pScene = new CStage1; m_SceneID = SCENE_ID::STAGE1; break;
	case SCENE_ID::STAGE2:
		SOUNDMANAGER->PlayeSound(STAGE2BGM);

		ReSet();
		m_pScene = new CStage2; m_SceneID = SCENE_ID::STAGE2; break;
	}
	m_pScene->Initialize();

}

void CSceneManager::Initialize()
{
	SetState(MAIN_MENU);
	m_score = 0;
	m_bShowCollisionBox = false;
	m_bInvincibility = false;
	m_bIsPlayerDead = false;
	m_exitGameTime = 0;
	LateInit();

}

void CSceneManager::LateInit()
{
	m_dieW = BITMAPMANAGER->GetImage()["DIE"]->GetWidth();
	m_dieH = BITMAPMANAGER->GetImage()["DIE"]->GetHeight();
}

void CSceneManager::Update()
{
	if (GetAsyncKeyState(VK_F1)) m_bShowCollisionBox = !m_bShowCollisionBox;
	if (GetAsyncKeyState(VK_F2)) m_bInvincibility = !m_bInvincibility;
	if (GetAsyncKeyState(VK_F3)) dynamic_cast<Player*>(obj_list[OBJ_ARR::PLAYER].front())->SetLevelMax();
	if (GetAsyncKeyState(VK_F4)) this->SetState(STAGE2);
	if (GetAsyncKeyState(VK_F5)) m_pScene->MoveToBoss();

	SCENE_ID sceneId = SCENE_ID::NO_EVENT;

	for (int i = 0; i < OBJ_ARR::END; i++) {
		auto it_begin = obj_list[i].begin();
		auto it_end = obj_list[i].end();
		for (; it_begin != it_end;) {
			if ((*it_begin)->Update())
			{
				if (i == OBJ_ARR::PLAYER) {
					m_bIsPlayerDead = true;
					m_exitGameTime = GetTickCount();

				}
				
				ObjDelete(*it_begin);
				it_begin = obj_list[i].erase(it_begin);
			}
			else
				it_begin++;
		}

	}

	sceneId = m_pScene->Update();

	if (sceneId > SCENE_ID::NO_EVENT){
		this->SetState(sceneId);
		return;
	}

}

void CSceneManager::LateUpdate()
{

	if (m_bIsPlayerDead && m_exitGameTime + 2000 < GetTickCount()) ReSetAll();
		
	
	for (int i = 0; i < OBJ_ARR::END; i++) {
		auto it_begin = obj_list[i].begin();
		auto it_end = obj_list[i].end();
		for (; it_begin != it_end;) {
			(*it_begin)->LateUpdate();
			it_begin++;
		}

	}

	COLLISIONMANAGER->RectCollision(obj_list[OBJ_ARR::ENEMY], obj_list[OBJ_ARR::NOMALBULLET]);
	COLLISIONMANAGER->RectCollision(obj_list[OBJ_ARR::ENEMY], obj_list[OBJ_ARR::MISSILE]);

	COLLISIONMANAGER->RectCollision(obj_list[OBJ_ARR::BOSS], obj_list[OBJ_ARR::NOMALBULLET]);
	COLLISIONMANAGER->RectCollision(obj_list[OBJ_ARR::BOSS], obj_list[OBJ_ARR::MISSILE]);

	COLLISIONMANAGER->ItemCollision(obj_list[OBJ_ARR::PLAYER], obj_list[OBJ_ARR::ITEM]);
	
	if (!m_bInvincibility) {
		COLLISIONMANAGER->RectCollision(obj_list[OBJ_ARR::PLAYER], obj_list[OBJ_ARR::ENEMYNORMALBULLET]);
		COLLISIONMANAGER->RectCollision(obj_list[OBJ_ARR::PLAYER], obj_list[OBJ_ARR::ENEMY]);
		COLLISIONMANAGER->RectCollision(obj_list[OBJ_ARR::PLAYER], obj_list[OBJ_ARR::BOSS]);


	}



}


void CSceneManager::Render()
{

	if (m_pScene)  m_pScene->Render(); 

	if (obj_list[OBJ_ARR::PLAYER].size() != 0) {
		auto& p = obj_list[OBJ_ARR::PLAYER].front();
		if (m_bInvincibility) dynamic_cast<Player*>(p)->RenderShiled();
	}

	for (int i = 0; i < OBJ_ARR::END; i++) {
		auto it_begin = obj_list[i].begin();
		auto it_end = obj_list[i].end();
		for (; it_begin != it_end;) {
			(*it_begin)->RenderCollsionBox();
			(*it_begin)->Render();
			it_begin++;
		}
	}

	RenderDie();
	RenderScore();

}

void CSceneManager::Release() { ObjDelete(m_pScene); }

void CSceneManager::RenderDie()
{
	if (m_bIsPlayerDead) {
		BITMAPMANAGER->GetImage()["DIE"]->TransparentBlt(RENDERMANAGER->GetMemDC(), (W_MAX / 2) - m_dieW / 2, (H_MAX / 2) - m_dieH / 2,
			m_dieW,
			m_dieH,
			0,
			0,
			m_dieW,
			m_dieH, RGB(0, 0, 0));
	}
	//BITMAPMANAGER->GetImage()["DIE"]->BitBlt(RENDERMANAGER->GetMemDC(), (W_MAX / 2) - m_dieW / 2, (H_MAX / 2) - m_dieH / 2, W_MAX, H_MAX, 0, 0, SRCCOPY);
}

void CSceneManager::RenderScore()
{
	if (m_gameStart) {
		HBRUSH MyBrush, OldBrush;
		MyBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
		OldBrush = (HBRUSH)SelectObject(RENDERMANAGER->GetMemDC(), MyBrush);

		Rectangle(RENDERMANAGER->GetMemDC(), 400, 0, 600, 30);


		SelectObject(RENDERMANAGER->GetMemDC(), OldBrush);

		SetBkColor(RENDERMANAGER->GetMemDC(), RGB(255, 255, 255));
		TCHAR szBuf[32] = L"";
		// swprintf_s: 두번째 인수와 세번째 인수가 결합되어 완성된 문자열을 첫번째 인수에 기록한다.
		swprintf_s(szBuf, L"Score: %d", m_score);
		TextOut(RENDERMANAGER->GetMemDC(), 450, 10, szBuf, lstrlen(szBuf));
	}
}

void CSceneManager::IncreaseScore(int score)
{
	m_score += dynamic_cast<Player*>(obj_list[OBJ_ARR::PLAYER].front())->GetLevel() * score;
}

void CSceneManager::CreatePlayer()
{
	Obj* newObj = ObjMaker<Player>::Create();
	//일반
	dynamic_cast<Player*>(newObj)->SetWEAPONEList(&obj_list[OBJ_ARR::WEAPONE]);
	dynamic_cast<Player*>(newObj)->SetNOMALList(&obj_list[OBJ_ARR::NOMALBULLET]);
	/////////미사일
	dynamic_cast<Player*>(newObj)->SetMISSILEist(&obj_list[OBJ_ARR::MISSILE]);
	dynamic_cast<Player*>(newObj)->SetMONSTERist(&obj_list[OBJ_ARR::ENEMY]);

	////////////////////스킬
	dynamic_cast<Player*>(newObj)->SetSKILLList(&obj_list[OBJ_ARR::SKILL]);
	dynamic_cast<Player*>(newObj)->SetSKILLBULLETList(&obj_list[OBJ_ARR::SKILLBULLET]);

	////////////////////////폭탄
	dynamic_cast<Player*>(newObj)->SetBOMBList(&obj_list[OBJ_ARR::BOMB]);
	/////////////////////아이템
	dynamic_cast<Player*>(newObj)->SetItemList(&obj_list[OBJ_ARR::ITEM]);


	obj_list[OBJ_ARR::PLAYER].push_back(newObj);


}

void CSceneManager::ReSet()
{
	for (int i = 0; i < OBJ_ARR::END; i++) {
		auto it_begin = obj_list[i].begin();
		auto it_end = obj_list[i].end();
		for (; it_begin != it_end;) {
			ObjDelete(*it_begin);
			it_begin = obj_list[i].erase(it_begin);
			
		}

	}

	CreatePlayer();
}

void CSceneManager::ReSetAll()
{
	for (int i = 0; i < OBJ_ARR::END; i++) {
		auto it_begin = obj_list[i].begin();
		auto it_end = obj_list[i].end();
		for (; it_begin != it_end;) {
			ObjDelete(*it_begin);
			it_begin = obj_list[i].erase(it_begin);

		}

	}

	Initialize();
}

void CSceneManager::CreateItem(float x, float y)
{
	Obj* p = ObjMaker<Item>::Create(x, y);
	obj_list[OBJ_ARR::ITEM].push_back(p);
}

void CSceneManager::InsertObj(Obj* pObj, OBJ_ARR::objarr type)
{
	obj_list[type].push_back(pObj);
}

bool CSceneManager::IsBossDead()
{
	bool ret = obj_list[OBJ_ARR::BOSS].size() == 0 ? true : false;
	
	if (ret) {
		auto it_begin = obj_list[OBJ_ARR::ENEMY].begin();
		auto it_end = obj_list[OBJ_ARR::ENEMY].end();
		for (; it_begin != it_end;) {
			(*it_begin)->SetDead();
			it_begin++;
		}

		it_begin = obj_list[OBJ_ARR::ENEMYNORMALBULLET].begin();
		it_end = obj_list[OBJ_ARR::ENEMYNORMALBULLET].end();
		for (; it_begin != it_end;) {
			(*it_begin)->SetDead();
			it_begin++;
		}

	}

	return ret;
}
