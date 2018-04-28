#include "stdafx.h"
#include "Button.h"

CMainMenu::CMainMenu()
{
	
}


CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Init()
{
	m_eId = SCENE::MAIN_MENU;

	CScene::Init();

	float w = static_cast<float>(RENDERMANAGER->GetWindowSize().x);
	float h = static_cast<float>(RENDERMANAGER->GetWindowSize().y);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(w * 0.2f, h * 0.2f);
		dynamic_cast<CButton*>(p)->SetId(SINGLE_PLAY_BUTTON);
		AddUI(p, BUTTON);
	}

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(w * 0.3f, h * 0.6f);
		dynamic_cast<CButton*>(p)->SetId(MULTI_PLAY_BUTTON);
		p->SetColor(RGB(255, 255, 255));
		AddUI(p, BUTTON);
	}

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(w * 0.6f, h * 0.3f);
		dynamic_cast<CButton*>(p)->SetId(EDITOR_BUTTON);
		AddUI(p, BUTTON);
	}

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(w * 0.7f, h * 0.6f);
		dynamic_cast<CButton*>(p)->SetId(EXIT_BUTTON);
		AddUI(p, BUTTON);
	}


}

void CMainMenu::LateInit()
{
	CUI* pButton = GetButton(SINGLE_PLAY_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(pButton->GetRect().left, pButton->GetRect().top - 15);
		dynamic_cast<CButton*>(p)->SetId(SINGLE_PLAY_STR_BUTTON);
		AddUI(p, BUTTON);
	}

	pButton = GetButton(MULTI_PLAY_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(pButton->GetRect().left - 10, pButton->GetRect().top - 15);
		dynamic_cast<CButton*>(p)->SetId(MULTI_PLAY_STR_BUTTON);
		AddUI(p, BUTTON);
	}

	pButton = GetButton(EDITOR_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(pButton->GetRect().left, pButton->GetRect().top - 20);
		dynamic_cast<CButton*>(p)->SetId(EDITOR_STR_BUTTON);
		AddUI(p, BUTTON);
	}

	pButton = GetButton(EXIT_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(pButton->GetRect().left, pButton->GetRect().top - 20);
		dynamic_cast<CButton*>(p)->SetId(EXIT_STR_BUTTON);
		AddUI(p, BUTTON);
	}
}


SCENE::SCENE_ID CMainMenu::Update()
{
	if (KEYMANAGER->KeyDown(VK_ESCAPE)) DestroyWindow(RENDERMANAGER->GethWnd());
	if (KEYMANAGER->KeyDown('X')) DestroyWindow(RENDERMANAGER->GethWnd());
	if (KEYMANAGER->KeyDown('S')) return SCENE::SINGLE_PLAY;

	if (KEYMANAGER->KeyDown('C')) return SCENE::EDITOR;


	CScene::LateInit();
	CScene::Update();
	
	// Click Button
	if (KEYMANAGER->KeyUp(VK_LBUTTON)) {
		auto it_begin = m_uiList[BUTTON].begin();
		auto it_OBJ_END = m_uiList[BUTTON].end();
		for (; it_begin != it_OBJ_END;) {
			if (((*it_begin)->IsMouseOver())) {
				if (EDITOR_BUTTON == dynamic_cast<CButton*>((*it_begin))->GetId()) return SCENE::EDITOR;

				else if (EXIT_BUTTON == dynamic_cast<CButton*>((*it_begin))->GetId()) DestroyWindow(RENDERMANAGER->GethWnd());
			}
			it_begin++;
		}
	}

	return SCENE::NO_EVENT;
}

void CMainMenu::LateUpdate()
{
	CScene::LateUpdate();
}

void CMainMenu::Render()
{
	StretchBlt(RENDERMANAGER->GetMemDC(), 0, 0, RENDERMANAGER->GetWindowSize().x,
		RENDERMANAGER->GetWindowSize().y,
		BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->GetDC(), 0, 0,
		m_tAnimationInfo[m_eCurrId].nImageW, m_tAnimationInfo[m_eCurrId].nImageH, SRCCOPY);

	CScene::Render();
	
}

void CMainMenu::Release()
{
}
