#include "stdafx.h"

void CUI::Init()
{
	
}

void CUI::LateInit()
{
	if (!m_bIsInit) this->LateInit();

	m_bIsInit = true;
}

int CUI::Update()
{
	if (m_tAnimationInfo[m_eCurrId].dwAnimationTime + 1000 / m_tAnimationInfo[m_eCurrId].nAnimationNum < GetTickCount()) {

		m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % m_tAnimationInfo[m_eCurrId].nAnimationNum;
		m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
	}

	return 0;
}

void CUI::LateUpdate()
{
}

void CUI::Render()
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


void CUI::RenderCollsionBox()
{
	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CUI::SetMouseOver()
{
	if (IDLE == m_eCurrId) ChangeAnimation(MOUSE_OVER);
		
}

void CUI::SetIdle()
{
	if (MOUSE_OVER == m_eCurrId) ChangeAnimation(IDLE);
}


void CUI::ChangeAnimation(UI_STATE_ID eId)
{
	m_eCurrId = eId;
	m_tAnimationInfo[m_eCurrId].nCnt = 0;
	m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
}

void CUI::UpdateRect()
{

	m_tRect.left = m_tInfo.fX;
	m_tRect.right = m_tInfo.fX + m_tAnimationInfo[m_eCurrId].nImageW;
	m_tRect.top = m_tInfo.fY;
	m_tRect.bottom = m_tInfo.fY + m_tAnimationInfo[m_eCurrId].nImageH;
}

CUI::CUI()
{
	m_bIsInit = false;
}

CUI::~CUI()
{
}
