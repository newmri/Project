#include "stdafx.h"
#include "Button.h"

void CButton::Init()
{
	m_eCurrId = IDLE;

	m_tAnimationInfo = new ANIMATION_INFO[UI_STATE_END];
	for (int i = 0; i < UI_STATE_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(ANIMATION_INFO));

	m_tRGB = (0, 0, 0);

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

	CUI::UpdateRect();
	if (SINGLE_PLAY_STR_BUTTON <= m_eId && EXIT_STR_BUTTON >= m_eId) m_tRect.bottom += 150;
	if (SINGLE_PLAY_STR_BUTTON == m_eId || EXIT_STR_BUTTON == m_eId) m_tRect.right += 150;

	

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
	CUI::Render();
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
