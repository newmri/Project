#include "stdafx.h"
#include "Scene.h"

void CScene::Init()
{
	m_bIsUI = true;
	m_eCurrId = IDLE;

	m_tAnimationInfo = new ANIMATION_INFO[UI_STATE_END];
	for (int i = 0; i < UI_STATE_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(ANIMATION_INFO));

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetSceneAnimationInfo(m_eId);

	// Set Animation Name
	for (int i = 0; i < UI_STATE_END; ++i) {

		m_tAnimationInfo[i].tName = new char*[pAnim[i].nAnimationNum];
		ZeroMemory(m_tAnimationInfo[i].tName, pAnim[i].nAnimationNum);

		for (int j = 0; j < pAnim[i].nAnimationNum; ++j) {

			m_tAnimationInfo[i].tName[j] = new char[STR_LEN];
			strcpy_s(m_tAnimationInfo[i].tName[j], strlen(m_tAnimationInfo[i].tName[j]), pAnim[i].tName[j]);

			m_tAnimationInfo[i].nAnimationNum = pAnim[i].nAnimationNum;
			m_tAnimationInfo[i].nImageW = pAnim[i].nImageW;
			m_tAnimationInfo[i].nImageH = pAnim[i].nImageH;
			m_tAnimationInfo[i].dwAnimationTime = GetTickCount();
			m_tAnimationInfo[i].nCnt = 0;

		}

	}
}

void CScene::LateInit()
{
	if (!m_bIsInit) {
		this->LateInit();
		LateUIInit();
	}
	m_bIsInit = true;
}

SCENE::SCENE_ID CScene::Update()
{
	if (m_tAnimationInfo[m_eCurrId].dwAnimationTime + 1000 / m_tAnimationInfo[m_eCurrId].nAnimationNum < GetTickCount()) {

		m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % m_tAnimationInfo[m_eCurrId].nAnimationNum;
		m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
	}

	UIUpdate();

	return SCENE::NO_EVENT;
}

void CScene::LateUpdate()
{
	LateUIUpdate();
}

void CScene::Render()
{
	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_tRect.left,
		m_tRect.top,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));

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

	m_tRect.left = m_tInfo.fX;
	m_tRect.right = m_tInfo.fX + m_tAnimationInfo[m_eCurrId].nImageW;
	m_tRect.top = m_tInfo.fY;
	m_tRect.bottom = m_tInfo.fY + m_tAnimationInfo[m_eCurrId].nImageH;
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
