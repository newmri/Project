#include "stdafx.h"
#include "Obj.h"

void CObj::LateInit()
{
	if (!m_bIsInit) this->LateInit();

	m_bIsInit = true;
}


void CObj::RenderCollsionBox()
{
	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

bool CObj::IsClicked(const POINT& pos) const
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	if (pos.x + fScrollX + TILE_SIZE >= m_tSelectRect.left && pos.x + fScrollX + TILE_SIZE <= m_tSelectRect.right &&
		pos.y + fScrollY >= m_tSelectRect.top && pos.y + fScrollY <= m_tSelectRect.bottom) return true;

	return false;
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


