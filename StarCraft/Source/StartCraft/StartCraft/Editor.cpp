#include "stdafx.h"
#include "Editor.h"

void CEditor::Init()
{
	m_eId = SCENE::EDITOR;

	CScene::Init();

}

void CEditor::LateInit()
{
	UpdateRect();
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
