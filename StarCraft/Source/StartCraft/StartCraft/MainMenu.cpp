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
	SOUNDMANAGER->PlayeSound(MAINMENUBGM);
	m_eId = SCENE::MAIN_MENU;

	CScene::Init();

	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(MAIN_MENU_IMAGE);
	m_tImageInfo = new IMAGE_INFO[p->nImageNum];
	memcpy(m_tImageInfo, p, sizeof(IMAGE_INFO) * p->nImageNum);


	float w = static_cast<float>(RENDERMANAGER->GetWindowSize().x);
	float h = static_cast<float>(RENDERMANAGER->GetWindowSize().y);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(w * 0.2f, h * 0.2f));
		dynamic_cast<CButton*>(p)->SetId(SINGLE_PLAY_BUTTON);
		AddUI(p, BUTTON);
	}

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(w * 0.3f, h * 0.6f));
		dynamic_cast<CButton*>(p)->SetId(MULTI_PLAY_BUTTON);
		p->SetColor(RGB(255, 255, 255));
		AddUI(p, BUTTON);
	}

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(w * 0.6f, h * 0.3f));
		dynamic_cast<CButton*>(p)->SetId(EDITOR_BUTTON);
		AddUI(p, BUTTON);
	}

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(w * 0.7f, h * 0.6f));
		dynamic_cast<CButton*>(p)->SetId(EXIT_BUTTON);
		AddUI(p, BUTTON);
	}


}

void CMainMenu::LateInit()
{
	CUI* pButton = GetButton(SINGLE_PLAY_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(pButton->GetRect().left, pButton->GetRect().top - 15));
		dynamic_cast<CButton*>(p)->SetId(SINGLE_PLAY_STR_BUTTON);
		AddUI(p, BUTTON);
	}

	pButton = GetButton(MULTI_PLAY_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(pButton->GetRect().left - 10, pButton->GetRect().top - 15));
		dynamic_cast<CButton*>(p)->SetId(MULTI_PLAY_STR_BUTTON);
		AddUI(p, BUTTON);
	}

	pButton = GetButton(EDITOR_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(pButton->GetRect().left, pButton->GetRect().top - 20));
		dynamic_cast<CButton*>(p)->SetId(EDITOR_STR_BUTTON);
		AddUI(p, BUTTON);
	}

	pButton = GetButton(EXIT_BUTTON);

	{
		CUI* p = CFactoryManager<CButton>::CreateUI(FLOATPOINT(pButton->GetRect().left, pButton->GetRect().top - 20));
		dynamic_cast<CButton*>(p)->SetId(EXIT_STR_BUTTON);
		AddUI(p, BUTTON);
	}
}


SCENE::SCENE_ID CMainMenu::Update()
{
	if (KEYMANAGER->KeyDown(VK_ESCAPE)) {
		SOUNDMANAGER->PlayerEffectSound(MAIN_MENU_CLICK);
		DestroyWindow(RENDERMANAGER->GethWnd());
	}
	if (KEYMANAGER->KeyDown('X')) {
		SOUNDMANAGER->PlayerEffectSound(MAIN_MENU_CLICK);
		DestroyWindow(RENDERMANAGER->GethWnd());
	}
	if (KEYMANAGER->KeyDown('S')) {
		SOUNDMANAGER->PlayerEffectSound(MAIN_MENU_CLICK);
		return SCENE::SINGLE_PLAY;
	}
	if (KEYMANAGER->KeyDown('C')) {
		SOUNDMANAGER->PlayerEffectSound(MAIN_MENU_CLICK);
		return SCENE::EDITOR;

	}
	CScene::LateInit();
	CScene::Update();
	
	// Click Button
	if (KEYMANAGER->KeyUp(VK_LBUTTON)) {
		auto it_begin = m_uiList[BUTTON].begin();
		auto it_OBJ_END = m_uiList[BUTTON].end();
		for (; it_begin != it_OBJ_END;) {
			if (((*it_begin)->IsMouseOver())) {
				if (SINGLE_PLAY_BUTTON == dynamic_cast<CButton*>((*it_begin))->GetId()) {
					SOUNDMANAGER->PlayerEffectSound(MAIN_MENU_CLICK);
					return SCENE::SINGLE_PLAY;
				}
				else if (EDITOR_BUTTON == dynamic_cast<CButton*>((*it_begin))->GetId()) {
					SOUNDMANAGER->PlayerEffectSound(MAIN_MENU_CLICK);
					return SCENE::EDITOR;
				}
				else if (EXIT_BUTTON == dynamic_cast<CButton*>((*it_begin))->GetId()) {
					SOUNDMANAGER->PlayerEffectSound(MAIN_MENU_CLICK);
					DestroyWindow(RENDERMANAGER->GethWnd());
				}
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
		BITMAPMANAGER->GetImage()[m_tImageInfo[MAIN_MENU_IMAGE].szName]->GetDC(), 0, 0,
		m_tImageInfo[MAIN_MENU_IMAGE].nImageW, m_tImageInfo[MAIN_MENU_IMAGE].nImageH, SRCCOPY);

	CScene::Render();
	
}

void CMainMenu::Release()
{
	SafeDelete(m_tImageInfo);
}
