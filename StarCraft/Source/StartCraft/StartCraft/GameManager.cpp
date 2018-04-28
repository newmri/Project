#include "stdafx.h"

CGameManager* CGameManager::m_pInstance = nullptr;

void CGameManager::Init()
{
	BITMAPMANAGER->Init();
	SOUNDMANAGER->Init();
	SCROLLMANAGER->Init();
	SCENEMANAGER->Init();
	MOUSEMANAGER->Init();
	TILEMANAGER->Init();
	TILEMANAGER->LateInit();


}

void CGameManager::Update()
{
	SCENEMANAGER->Update();
}

void CGameManager::LateUpdate()
{
	SCENEMANAGER->LateUpdate();
	KEYMANAGER->Update();
	MOUSEMANAGER->Update();
}

void CGameManager::Render()
{
	SCENEMANAGER->Render();
	MOUSEMANAGER->Render();
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
	MOUSEMANAGER->Release();

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
