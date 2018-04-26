#include "stdafx.h"
#include "MultiPlay.h"

void CMultiPlay::Init()
{
	m_eId = SCENE::MULTI_PLAY;

	CScene::Init();

}

void CMultiPlay::LateInit()
{
	UpdateRect();
}

SCENE::SCENE_ID CMultiPlay::Update()
{
	CScene::LateInit();
	CScene::Update();

	return SCENE::NO_EVENT;
}

void CMultiPlay::LateUpdate()
{
}

void CMultiPlay::Render()
{
	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_tRect.left,
		m_tRect.top,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(255, 255, 255));
}

void CMultiPlay::Release()
{
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName[i]);
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName);
}

CMultiPlay::CMultiPlay()
{

}

CMultiPlay::~CMultiPlay()
{
	Release();
}
