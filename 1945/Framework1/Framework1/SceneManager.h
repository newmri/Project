#pragma once

#include "My_Enum.h"

class CSceneManager
{

public:
	void Initialize();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render();
	void SetState(const SCENE_ID);
	void Release();

	void RenderDie();
	void RenderScore();

public:
	void IncreaseScore(int score);

public:
	const bool& ShowCollisionBox() { return m_bShowCollisionBox; }

public:
	void CreatePlayer();
	void ReSet();
	void ReSetAll();

	void CreateItem(float x, float y);

	void InsertObj(Obj* pObj, OBJ_ARR::objarr type);

public:
	OBJLIST* GetObjList() { return obj_list; }
	OBJLIST* GetEnemyNormallBulletList() { return &obj_list[OBJ_ARR::ENEMYNORMALBULLET]; }
	const SCENE_ID& GetStage() { return m_SceneID; }
	bool IsBossDead();

public:
	static CSceneManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CSceneManager;

		return m_instance;
	}


	~CSceneManager();
private:
	CSceneManager();
	CSceneManager(const CSceneManager&) = delete;
	void operator=(const CSceneManager&) = delete;

	static CSceneManager* m_instance;

private:
	CScene* m_pScene;
	SCENE_ID m_SceneID;

private:
	BYTE m_NPC_NUM;

private:
	OBJLIST obj_list[OBJ_ARR::END];

private:
	DWORD m_exitGameTime;
	bool m_bShowCollisionBox;
	bool m_bInvincibility;
	bool m_bIsPlayerDead;
	int m_dieW;
	int m_dieH;
	int m_score;
	bool m_gameStart;

};