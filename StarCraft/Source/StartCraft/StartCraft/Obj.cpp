#include "stdafx.h"
#include "Obj.h"

void CObj::LateInit()
{
	if (!m_bIsInit) this->LateInit();

	m_bIsInit = true;
}

void CObj::UpdateRect()
{
	/*int w = static_cast<int>(m_tInfo.fX - m_tAnimationInfo[m_eCurrId].nImageW / 2);
	m_tRect.left = w;
	m_tRect.right = m_tRect.left + w;
	m_tRect.top = m_tInfo.fY + 5;
	m_tRect.bottom = m_tInfo.fY + m_tAnimationInfo[m_eCurrAnim].nImageH;*/

}

void CObj::RenderCollsionBox()
{
	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}


CObj::CObj()
{
	m_bIsDead = false;
	m_bIsInit = false;
	m_bIsUI = false;
}

CObj::~CObj()
{
}


