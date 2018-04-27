#include "stdafx.h"
#include "Button.h"

void CButton::Init()
{
	m_bIsUI = true;
	m_eCurrId = IDLE;

	m_tAnimationInfo = new ANIMATION_INFO[UI_STATE_END];
	for (int i = 0; i < UI_STATE_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(ANIMATION_INFO));

}

void CButton::LateInit()
{
	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetButtonAnimationInfo(m_eId);

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

	UpdateRect();
}

int CButton::Update()
{
	CUI::LateInit();
	CUI::Update();

	return 0;
}

void CButton::LateUpdate()
{
}

void CButton::Render()
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
}

void CButton::Release()
{

}

CButton::CButton()
{

}

CButton::~CButton()
{
	Release();
}
