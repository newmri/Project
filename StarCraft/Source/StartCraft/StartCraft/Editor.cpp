#include "stdafx.h"
#include "Editor.h"
#include "Button.h"

void CEditor::Init()
{
	m_eId = SCENE::EDITOR;
	m_tInfo.fX = 0;
	m_tInfo.fY = 0;

	m_bIsUI = true;
	m_eCurrId = static_cast<UI_STATE_ID>(MAIN_MAP);

	m_tAnimationInfo = new ANIMATION_INFO[MAP_KIND_END];
	for (int i = 0; i < MAP_KIND_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(ANIMATION_INFO));

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetMapInfo(BEGINNER_MAP);

	// Set Animation Name
	for (int i = 0; i < MAP_KIND_END; ++i) {

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
		if (1 == pAnim[i].nAnimationNum) break;
	}

}

void CEditor::LateInit()
{
	m_tRect.left = 0;
	m_tRect.top = 0;

}

SCENE::SCENE_ID CEditor::Update()
{
	CScene::LateInit();
	
	if (KEYMANAGER->KeyDown(VK_ESCAPE)) return SCENE::MAIN_MENU;
	if (KEYMANAGER->KeyPressing(VK_LEFT)) SCROLLMANAGER->SetScrollX(SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_RIGHT)) SCROLLMANAGER->SetScrollX(-SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_UP)) SCROLLMANAGER->SetScrollY(SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_DOWN)) SCROLLMANAGER->SetScrollY(-SCROLL_SPEED);


	SCROLLMANAGER->Update();

	return SCENE::NO_EVENT;
}

void CEditor::LateUpdate()
{
	CScene::LateUpdate();

}

void CEditor::Render()
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_tRect.left + fScrollX),
		static_cast<int>(m_tRect.top + fScrollY),
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(0,0,0));

	TILEMANAGER->Render();

	//CScene::Render();
}

void CEditor::Release()
{
	
}

CEditor::CEditor()
{

}

CEditor::~CEditor()
{
	Release();
}
