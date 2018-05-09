#include "stdafx.h"
#include "Editor.h"
#include "Button.h"
#include "Mine.h"

//#ifdef _DEBUG
//
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif
//#endif
void CEditor::Init()
{
	m_eId = SCENE::EDITOR;


	m_bIsUI = true;
	m_eCurrId = static_cast<UI_STATE_ID>(MAIN_MAP);

	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(MAIN_MAP_IMAGE);
	m_tImageInfo = new IMAGE_INFO[p->nImageNum];
	memcpy(m_tImageInfo, p, sizeof(IMAGE_INFO) * p->nImageNum);


}

void CEditor::LateInit()
{
	m_tRect.left = 0;
	m_tRect.top = 0;

}

SCENE::SCENE_ID CEditor::Update()
{
	if (KEYMANAGER->KeyDown(VK_ESCAPE)) {
		TILEMANAGER->SaveData();
		return SCENE::MAIN_MENU;
	}

	CScene::LateInit();

	if (KEYMANAGER->KeyPressing(VK_LEFT)) SCROLLMANAGER->SetScrollX(SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_RIGHT)) SCROLLMANAGER->SetScrollX(-SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_UP)) SCROLLMANAGER->SetScrollY(SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_DOWN)) SCROLLMANAGER->SetScrollY(-SCROLL_SPEED);

	MOUSEMANAGER->MouseScroll();

	SCROLLMANAGER->Update();

	return SCENE::NO_EVENT;
}

void CEditor::LateUpdate()
{
	CScene::LateUpdate();
	if (KEYMANAGER->KeyUp(VK_LBUTTON)) MOUSEMANAGER->CheckSwapTile();
	if (KEYMANAGER->KeyDown('Z')) TILEMANAGER->Undo();
	if (KEYMANAGER->KeyDown(VK_TAB)) TILEMANAGER->SwapRenderMode();


	if (KEYMANAGER->KeyDown('S')) TILEMANAGER->SaveData();
	if (KEYMANAGER->KeyDown('L')) TILEMANAGER->LoadData();

	if (KEYMANAGER->KeyDown(VK_F2)) {
		POINT mousePos = MOUSEMANAGER->GetPos();
		FLOATPOINT pos;
		pos.fX = mousePos.x;
		pos.fY = mousePos.y - TILE_SIZE;

		CObj* obj = CFactoryManager<CMine>::CreateObj(pos);
		TILEMANAGER->AddTileObj(MINE, obj);
	}

	if (KEYMANAGER->KeyDown(VK_F3)) TILEMANAGER->DeleteTileObj(MINE);

}

void CEditor::Render()
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();


	BITMAPMANAGER->GetImage()[m_tImageInfo[0].szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_tRect.left + fScrollX),
		static_cast<int>(m_tRect.top + fScrollY),
		m_tImageInfo[0].nImageW,
		m_tImageInfo[0].nImageH,
		0,
		0,
		m_tImageInfo[0].nImageW,
		m_tImageInfo[0].nImageH, RGB(0, 0, 0));


	TILEMANAGER->Render();
	CScene::Render();
	TILEMANAGER->RenderTile();
}

void CEditor::Release()
{
	SafeDelete(m_tImageInfo);
}

CEditor::CEditor()
{

}

CEditor::~CEditor()
{
	Release();
}
