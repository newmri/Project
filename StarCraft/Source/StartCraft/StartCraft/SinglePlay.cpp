#include "stdafx.h"
#include "SinglePlay.h"
#include "Button.h"


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
	memcpy(&m_tBottomImage, p, sizeof(IMAGE_INFO));
	m_tBottomImage.tPos.x = 0;
	m_tBottomImage.tPos.y = RENDERMANAGER->GetWindowSize().y - p->nImageH;
	
	//m_listStaticUImage.push_back(pTemp);
	


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

	CScene::LateInit();

	SCROLLMANAGER->Update();

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

	// Render Bottom
	BITMAPMANAGER->GetImage()[m_tBottomImage.tInfo.szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_tBottomImage.tPos.x,
		m_tBottomImage.tPos.y,
		RENDERMANAGER->GetWindowSize().x,
		m_tBottomImage.tInfo.nImageH,
		0,
		0,
		m_tBottomImage.tInfo.nImageW,
		m_tBottomImage.tInfo.nImageH, RGB(255, 255, 255));


	/*for (auto& image : m_listStaticUImage) {
		BITMAPMANAGER->GetImage()[image->tInfo.szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			image->tPos.x,
			image->tPos.y,
			image->tInfo.nImageW,
			image->tInfo.nImageH,
			0,
			0,
			image->tInfo.nImageW,
			image->tInfo.nImageH, RGB(255, 255, 255));
	}
*/
	CScene::Render();
}

void CSinglePlay::Release()
{
	SafeDelete(m_tMapImageInfo);
	SCROLLMANAGER->ReSet();
}

CSinglePlay::CSinglePlay()
{

}

CSinglePlay::~CSinglePlay()
{
	Release();
}
