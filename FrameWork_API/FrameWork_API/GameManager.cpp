#include "stdafx.h"

CGameManager* CGameManager::m_pInstance = nullptr;

void CGameManager::Init()
{
	SOUNDMANAGER->Init();
	BITMAPMANAGER->Init();
	SCENEMANAGER->Init();
}

void CGameManager::Update()
{
	SCENEMANAGER->Update();
}

void CGameManager::LateUpdate()
{
	SCENEMANAGER->LateUpdate();
	KEYMANAGER->Update();
}

void CGameManager::Render()
{
	SCENEMANAGER->Render();
	RENDERMANAGER->Render();
}

void CGameManager::Release()
{
	BITMAPMANAGER->Release();
	RENDERMANAGER->Release();
	SCENEMANAGER->Release();
	SOUNDMANAGER->Release();
	COLLISIONMANAGER->Release();
	KEYMANAGER->Release();

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}
