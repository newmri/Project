#include "stdafx.h"
#include "Exit.h"
#include "Button.h"

void CExit::Init()
{
	m_eId = SCENE::EXIT;

	CScene::Init();

}

void CExit::LateInit()
{
	UpdateRect();

	CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(static_cast<float>(m_tRect.left + 80), static_cast<float>(m_tRect.top - 20)));
	dynamic_cast<CButton*>(p)->SetId(EXIT_STR_BUTTON);
	AddUI(p, BUTTON);
}

SCENE::SCENE_ID CExit::Update()
{
	CScene::LateInit();
	CScene::Update();

	return SCENE::NO_EVENT;
}

void CExit::LateUpdate()
{
	
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
