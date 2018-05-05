#include "stdafx.h"
#include "Scene.h"
#include "Button.h"

void CScene::Init()
{
	m_bIsUI = true;
	m_eCurrId = IDLE;

}

void CScene::LateInit()
{
	if (!m_bIsInit) {
		LateUIInit();
	}
	this->LateInit();

	m_bIsInit = true;
}

SCENE::SCENE_ID CScene::Update()
{

	UIUpdate();

	return SCENE::NO_EVENT;
}

void CScene::LateUpdate()
{
	LateUIUpdate();
	for (int i = 0; i < UI_END; ++i) MOUSEMANAGER->CheckMouseOver(m_uiList[i]);

}

void CScene::Render()
{
	UIRender();

}

void CScene::LateUIInit()
{
	for (int i = 0; i < UI_END; i++) {
		auto it_begin = m_uiList[i].begin();
		auto it_OBJ_END = m_uiList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->LateInit();
			it_begin++;
		}

	}
}

void CScene::UIUpdate()
{
	for (int i = 0; i < UI_END; i++) {
		auto it_begin = m_uiList[i].begin();
		auto it_OBJ_END = m_uiList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->Update();
			it_begin++;
		}

	}
}

void CScene::LateUIUpdate()
{
	for (int i = 0; i < UI_END; i++) {
		auto it_begin = m_uiList[i].begin();
		auto it_OBJ_END = m_uiList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->LateUpdate();
			it_begin++;
		}

	}
}

void CScene::UIRender()
{
	for (int i = 0; i < UI_END; i++) {
		auto it_begin = m_uiList[i].begin();
		auto it_OBJ_END = m_uiList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->RenderCollsionBox();
			(*it_begin)->Render();
			it_begin++;
		}

	}
}

void CScene::RenderCollsionBox()
{
	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

CButton* CScene::GetButton(BUTTON_ID eId)
{
	auto it_begin = m_uiList[BUTTON].begin();
	auto it_OBJ_END = m_uiList[BUTTON].end();
	for (; it_begin != it_OBJ_END;) {
		CButton* p = dynamic_cast<CButton*>((*it_begin));
		if (eId == p->GetId()) return p;
		it_begin++;
	}

	return nullptr;
}

void CScene::SetMouseOver()
{
	if (IDLE == m_eCurrId) {
		ChangeAnimation(MOUSE_OVER);

		auto it_begin = m_uiList[BUTTON].begin();
		auto it_OBJ_END = m_uiList[BUTTON].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->ChangeAnimation(MOUSE_OVER);
			it_begin++;
		}

	}
}

void CScene::SetIdle()
{
	if (MOUSE_OVER == m_eCurrId) {
		ChangeAnimation(IDLE);

		auto it_begin = m_uiList[BUTTON].begin();
		auto it_OBJ_END = m_uiList[BUTTON].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->ChangeAnimation(IDLE);
			it_begin++;
		}
	}
}

void CScene::AddUI(CUI* pObj, UI_ID eID)
{
	m_uiList[eID].push_back(pObj);
}

void CScene::ChangeAnimation(UI_STATE_ID eId)
{
	m_eCurrId = eId;
	m_tAnimationInfo[m_eCurrId].nCnt = 0;
	m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
}

void CScene::UpdateRect()
{
	m_tRect.left = m_tInfo.tPos.fX;
	m_tRect.right = m_tInfo.tPos.fX + m_tAnimationInfo[m_eCurrId].nImageW;
	m_tRect.top = m_tInfo.tPos.fY;
	m_tRect.bottom = m_tInfo.tPos.fY + m_tAnimationInfo[m_eCurrId].nImageH;
}


CScene::CScene()
{
	m_bIsInit = false;
}

CScene::~CScene()
{
	for (int i = 0; i < UI_END; ++i) {
		for_each(m_uiList[i].begin(), m_uiList[i].end(),
			[](auto& obj)
		{
			if (obj)
			{
				delete obj;
				obj = nullptr;
			}
		});
		m_uiList[i].clear();
	}
}
