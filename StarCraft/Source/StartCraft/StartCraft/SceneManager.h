#pragma once

#include "Enum.h"
#include "Type.h"

class CSceneManager
{
public:
	void Init();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render();
	void SetState(const SCENE::SCENE_ID eSceneID);
	void Release();

	void RenderDie();

public:
	void AddScene(CScene* pObj, SCENE::SCENE_ID eID);

public:
	void KillPlayer() { m_bIsPlayerDead = true; }

public:
	const bool& ShowCollisionBox() { return m_bShowCollisionBox; }

public:
	void CreatePlayer();
	void ReSet();
	void ReSetAll();

public:
	const SCENE::SCENE_ID& GetStage() { return m_eSceneID; }

public:
	static CSceneManager* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CSceneManager;

		return m_pInstance;
	}


private:
	CSceneManager() = default;
	~CSceneManager() = default;
	CSceneManager(const CSceneManager&) = delete;
	void operator=(const CSceneManager&) = delete;

private:
	static CSceneManager* m_pInstance;

private:
	SCENELIST m_objList[SCENE::SCENE_ID::SCENE_END];

private:
	CScene*		m_pScene;
	SCENE::SCENE_ID	m_eSceneID;

private:
	bool		m_bShowCollisionBox;
	bool		m_bInvincibility;
	bool		m_bIsPlayerDead;
	bool		m_bIsGameStarted;

};