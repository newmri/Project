#include "stdafx.h"
#include "SinglePlayUI.h"

void CSinglePlayUI::Init()
{
	m_eCurrId = IDLE;

	m_tAnimationInfo = new ANIMATION_INFO[UI_END];
	for (int i = 0; i < UI_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(ANIMATION_INFO));

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(SINGLE_PLAY);

	// Set Animation Name
	for (int i = 0; i < UI_END; ++i) {

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

void CSinglePlayUI::LateInit()
{
}

int CSinglePlayUI::Update()
{
	if (m_tAnimationInfo[m_eCurrId].dwAnimationTime + 2000 / m_tAnimationInfo[m_eCurrId].nAnimationNum < GetTickCount()) {

		m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % m_tAnimationInfo[m_eCurrId].nAnimationNum;
		m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
	}

	return 0;
}

void CSinglePlayUI::LateUpdate()
{
}

void CSinglePlayUI::Render()
{
	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_tInfo.fX - m_tAnimationInfo[m_eCurrId].nImageW / 2,
		m_tInfo.fY - m_tAnimationInfo[m_eCurrId].nImageH / 2,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));
}

void CSinglePlayUI::Realease()
{
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName[i]);
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName);
}

CSinglePlayUI::CSinglePlayUI()
{

}

CSinglePlayUI::~CSinglePlayUI()
{
	Realease();
}
