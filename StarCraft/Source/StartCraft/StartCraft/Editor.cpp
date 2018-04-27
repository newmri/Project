#include "stdafx.h"
#include "Editor.h"
#include "Button.h"

void CEditor::Init()
{
	m_eId = SCENE::EDITOR;

	CScene::Init();

}

void CEditor::LateInit()
{
	UpdateRect();

	CUI* p = CFactoryManager<CButton>::CreateUI(m_tRect.left, m_tRect.top - 20);
	dynamic_cast<CButton*>(p)->SetId(EDITOR_BUTTON);
	AddUI(p, BUTTON);
}

SCENE::SCENE_ID CEditor::Update()
{
	CScene::LateInit();
	CScene::Update();

	return SCENE::NO_EVENT;
}

void CEditor::LateUpdate()
{
}

void CEditor::Render()
{
	CScene::Render();
}

void CEditor::Release()
{
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName[i]);
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName);
}

CEditor::CEditor()
{

}

CEditor::~CEditor()
{
	Release();
}
