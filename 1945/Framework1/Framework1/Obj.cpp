#include "stdafx.h"
#include "Obj.h"


Obj::Obj()
{
}

void Obj::LateInit()
{
	if (!m_bIsInit)
		this->LateInit();

	m_bIsInit = true;
}


Obj::~Obj()
{
}

bool Obj::NoOut()
{
	if (m_info.m_y >= H_MAX)
		return true;
	if (m_info.m_x >= W_MAX)
		return true;
	if (m_info.m_x <= 0)
		return true;
	if (m_info.m_y <= 0)
		return true;
	return false;
}

void Obj::RenderCollsionBox()
{
	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	}
}

void Obj::SetRect()
{
	m_rect.left = m_info.m_x + m_info.m_w / 4;
	m_rect.top = m_info.m_y;
	m_rect.right = m_rect.left + m_info.m_w / 2;
	m_rect.bottom = m_info.m_y + m_info.m_h;

}

void Obj::SetStat(float fHp, float fAtk)
{
	m_stat.m_Atk = fAtk; m_stat.m_cHp = fHp;
}

