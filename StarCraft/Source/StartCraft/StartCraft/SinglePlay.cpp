#include "stdafx.h"
#include "SinglePlay.h"
#include "Button.h"
#include "Structure.h"
#include "Unit.h"

void CSinglePlay::Init()
{
	m_eId = SCENE::SINGLE_PLAY;

	m_tInfo.fX = 0;
	m_tInfo.fY = 0;

	m_bIsUI = true;

	
	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(MAIN_MAP_IMAGE);
	m_tMapImageInfo = new IMAGE_INFO[p->nImageNum];
	memcpy(m_tMapImageInfo, p, sizeof(IMAGE_INFO) * p->nImageNum);


	p = BITMAPMANAGER->GetImageInfo(BOTTOM_MENU_IMAGE);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

		memcpy(&pTemp->tInfo, &p[i], sizeof(IMAGE_INFO));
		pTemp->tPos.x = 0;
		pTemp->tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.8f);
		pTemp->tDrawSize.x = RENDERMANAGER->GetWindowSize().x;
		pTemp->tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.201f);
		pTemp->tColor = RGB(255, 255, 255);
		m_listStaticUImage.push_back(pTemp);
	}

	// MiniMap
	p = BITMAPMANAGER->GetImageInfo(MAIN_MAP_IMAGE);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

		memcpy(&pTemp->tInfo, &p[i], sizeof(IMAGE_INFO));

		pTemp->tPos.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.009f);
		pTemp->tPos.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.858f);
		pTemp->tDrawSize.x = static_cast<int>(RENDERMANAGER->GetWindowSize().x * 0.2f);
		pTemp->tDrawSize.y = static_cast<int>(RENDERMANAGER->GetWindowSize().y * 0.142f);
		pTemp->tColor = RGB(0, 0, 0);
		m_listStaticUImage.push_back(pTemp);

		RECT rc;
		rc.left = static_cast<LONG>(pTemp->tPos.x);
		rc.right = static_cast<LONG>(pTemp->tDrawSize.x);
		rc.top = static_cast<LONG>(pTemp->tPos.y);
		rc.bottom = static_cast<LONG>(pTemp->tPos.y + pTemp->tDrawSize.y);

		MOUSEMANAGER->SetMiniMapArea(rc);
	}

	// Resources Icon
	p = BITMAPMANAGER->GetImageInfo(RESOURCES_ICON_IMAGE);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

		memcpy(&pTemp->tInfo, &p[i], sizeof(IMAGE_INFO));

		pTemp->tPos.x = (RENDERMANAGER->GetWindowSize().x - 600) + (i * 200 );
		pTemp->tPos.y = 0;
		pTemp->tDrawSize.x = p[i].nImageW * 2;
		pTemp->tDrawSize.y = p[i].nImageH * 2;
		pTemp->tColor = RGB(0, 0, 0);
		m_listStaticUImage.push_back(pTemp);
	}

	CObj* pObj = CFactoryManager<CStructure>::CreateObj(GREEN, CONTROL, PORTRAIT::ADVISOR,
		UNIT::LARGE_WIRE::CONTROL, UNIT_SELECT9, 300, 200, 1500);
	OBJMANAGER->AddObject(pObj, CONTROL);

	pObj = CFactoryManager<CStructure>::CreateObj(GREEN, BARRACK, PORTRAIT::ADVISOR,
		UNIT::LARGE_WIRE::BARRACK, UNIT_SELECT9, 140, 300, 1500);
	OBJMANAGER->AddObject(pObj, BARRACK);

	for (int i = 300 - TILE_SIZE; i < 300 + TILE_SIZE * 6; i += TILE_SIZE) {
		pObj = CFactoryManager<CUnit>::CreateObj(GREEN, SCV, PORTRAIT::SCV,
			UNIT::LARGE_WIRE::SCV, UNIT::SMALL_WIRE::SCV, UNIT_SELECT3, i, 300, 60);
		OBJMANAGER->AddObject(pObj, SCV);
	}


}

void CSinglePlay::LateInit()
{
	m_tRect.left = 0;
	m_tRect.top = 0;


}

SCENE::SCENE_ID CSinglePlay::Update()
{
	if (KEYMANAGER->KeyDown(VK_ESCAPE)) return SCENE::MAIN_MENU;


	if (KEYMANAGER->KeyPressing(VK_LEFT)) SCROLLMANAGER->SetScrollX(SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_RIGHT)) SCROLLMANAGER->SetScrollX(-SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_UP)) SCROLLMANAGER->SetScrollY(SCROLL_SPEED);
	else if (KEYMANAGER->KeyPressing(VK_DOWN)) SCROLLMANAGER->SetScrollY(-SCROLL_SPEED);
	else if (KEYMANAGER->KeyDown(VK_TAB)) TILEMANAGER->SwapRenderMode();

	CScene::LateInit();

	MOUSEMANAGER->MouseScroll();
	MOUSEMANAGER->MoveScrollByMouse();
	SCROLLMANAGER->Update();
	MOUSEMANAGER->CheckSelectObj();
	MOUSEMANAGER->CheckMoveObj();

	return SCENE::NO_EVENT;
}

void CSinglePlay::LateUpdate()
{
	CScene::LateUpdate();
}

void CSinglePlay::Render()
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();


	BITMAPMANAGER->GetImage()[m_tMapImageInfo[0].szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_tRect.left + fScrollX),
		static_cast<int>(m_tRect.top + fScrollY),
		m_tMapImageInfo[0].nImageW,
		m_tMapImageInfo[0].nImageH,
		0,
		0,
		m_tMapImageInfo[0].nImageW,
		m_tMapImageInfo[0].nImageH, RGB(0, 0, 0));

	for (auto& image : m_listStaticUImage) {
		BITMAPMANAGER->GetImage()[image->tInfo.szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			image->tPos.x,
			image->tPos.y,
			image->tDrawSize.x,
			image->tDrawSize.y,
			0,
			0,
			image->tInfo.nImageW,
			image->tInfo.nImageH, image->tColor);
	}

	RENDERMANAGER->RenderMiniMapFrame();
	TILEMANAGER->Render();
	CScene::Render();
}

void CSinglePlay::Release()
{
	SafeDelete(m_tMapImageInfo);

	
	for_each(m_listStaticUImage.begin(), m_listStaticUImage.end(), [](auto& obj)
	{
		if (obj){
			delete obj;
			obj = nullptr;
		}
	});
	m_listStaticUImage.clear();
	

	SCROLLMANAGER->ReSet();
}

CSinglePlay::CSinglePlay()
{

}

CSinglePlay::~CSinglePlay()
{
	Release();
}
