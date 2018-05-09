#include "stdafx.h"
#include "SinglePlay.h"
#include "Button.h"
#include "Structure.h"
#include "Unit.h"
#include "Marine.h"
#include "Ghost.h"


void CSinglePlay::Init()
{
	SOUNDMANAGER->BGSoundOff();
	SOUNDMANAGER->PlayeSound(TERRAN_BGM);

	m_eId = SCENE::SINGLE_PLAY;

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

	RESOURCES* rc = SCENEMANAGER->GetResources();
	// Resources Icon
	p = BITMAPMANAGER->GetImageInfo(RESOURCES_ICON_IMAGE);
	for (int i = 0; i < p[0].nImageNum; ++i) {
		STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;

		memcpy(&pTemp->tInfo, &p[i], sizeof(IMAGE_INFO));

		pTemp->tPos.x = (RENDERMANAGER->GetWindowSize().x - 600) + (i * 200 );
		pTemp->tPos.y = 10;
		pTemp->tDrawSize.x = p[i].nImageW * 2;
		pTemp->tDrawSize.y = p[i].nImageH * 2;
		pTemp->tColor = RGB(0, 0, 0);
		m_listStaticUImage.push_back(pTemp);

		rc[i].tPos.x = pTemp->tPos.x + pTemp->tDrawSize.x + 10;
		rc[i].tPos.y = pTemp->tPos.y + 3;
	}

	CObj* pObj = CFactoryManager<CStructure>::CreateObj(GREEN, CONTROL, PORTRAIT::ADVISOR,
		UNIT::LARGE_WIRE::CONTROL, UNIT_SELECT9, FLOATPOINT(300, 180), 1500);
	OBJMANAGER->AddObject(pObj, CONTROL);


	//pObj = CFactoryManager<CMarine>::CreateObj(GREEN, MARINE, PORTRAIT::MARINE,
	//	UNIT::LARGE_WIRE::MARINE, UNIT::SMALL_WIRE::MARINE, UNIT_SELECT2, FLOATPOINT((5 * TILE_SIZE) - 19, (5 * TILE_SIZE) - 17), 60);
	//OBJMANAGER->AddObject(pObj, MARINE);

	//pObj = CFactoryManager<CGhost>::CreateObj(GREEN, GHOST, PORTRAIT::GHOST,
	//	UNIT::LARGE_WIRE::GHOST, UNIT::SMALL_WIRE::GHOST, UNIT_SELECT2, FLOATPOINT((6 * TILE_SIZE) - 19, (5 * TILE_SIZE) - 17), 60);
	//OBJMANAGER->AddObject(pObj, GHOST);

}

void CSinglePlay::LateInit()
{
	m_tRect.left = 0;
	m_tRect.top = 0;


}

SCENE::SCENE_ID CSinglePlay::Update()
{
	if (KEYMANAGER->KeyDown(VK_ESCAPE)) {
		OBJMANAGER->ReSet();
		MOUSEMANAGER->Init();
		SCENEMANAGER->Init();
		return SCENE::MAIN_MENU;
	}

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
	HDC hDC = RENDERMANAGER->GetMemDC();

	BITMAPMANAGER->GetImage()[m_tMapImageInfo[0].szName]->TransparentBlt(hDC,
		static_cast<int>(m_tRect.left + fScrollX),
		static_cast<int>(m_tRect.top + fScrollY),
		m_tMapImageInfo[0].nImageW,
		m_tMapImageInfo[0].nImageH,
		0,
		0,
		m_tMapImageInfo[0].nImageW,
		m_tMapImageInfo[0].nImageH, RGB(0, 0, 0));

	for (auto& image : m_listStaticUImage) {
		BITMAPMANAGER->GetImage()[image->tInfo.szName]->TransparentBlt(hDC,
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
	SCENEMANAGER->RenderResourcesValue();
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
