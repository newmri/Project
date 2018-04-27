#include "stdafx.h"
#include "SinglePlay.h"
#include "Button.h"

void CSinglePlay::Init()
{
	m_eId = SCENE::SINGLE_PLAY;

	CScene::Init();

}

void CSinglePlay::LateInit()
{
	UpdateRect();

	CUI* p = CFactoryManager<CButton>::CreateUI(m_tRect.right - 150, m_tRect.bottom);
	dynamic_cast<CButton*>(p)->SetId(SINGLE_PLAY_BUTTON);

	AddUI(p, BUTTON);
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
