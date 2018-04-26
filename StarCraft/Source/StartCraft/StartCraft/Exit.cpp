#include "stdafx.h"
#include "Exit.h"

void CExit::Init()
{
	m_eId = SCENE::EXIT;

	CScene::Init();

}

void CExit::LateInit()
{
	UpdateRect();
}

SCENE::SCENE_ID CExit::Update()
{
	CScene::LateInit();
	CScene::Update();

	return SCENE::NO_EVENT;
}

void CExit::LateUpdate()
{
	if (KEYMANAGER->KeyUp(VK_LBUTTON) && MOUSE_OVER == m_eCurrId) DestroyWindow(RENDERMANAGER->GethWnd());
	
}

void CExit::Render()
{
	CScene::Render();
}

void CExit::Release()
{
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName[i]);
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName);
}

CExit::CExit()
{

}

CExit::~CExit()
{
	Release();
}
