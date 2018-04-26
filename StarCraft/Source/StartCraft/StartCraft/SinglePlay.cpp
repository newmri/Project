#include "stdafx.h"
#include "SinglePlay.h"

void CSinglePlay::Init()
{
	m_eId = SCENE::SINGLE_PLAY;

	CScene::Init();

}

void CSinglePlay::LateInit()
{
	UpdateRect();
}

SCENE::SCENE_ID CSinglePlay::Update()
{
	CScene::LateInit();
	CScene::Update();

	return SCENE::NO_EVENT;
}

void CSinglePlay::LateUpdate()
{
}

void CSinglePlay::Render()
{
	CScene::Render();
}

void CSinglePlay::Release()
{
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName[i]);
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName);
}

CSinglePlay::CSinglePlay()
{

}

CSinglePlay::~CSinglePlay()
{
	Release();
}
