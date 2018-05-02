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

const RECT CObj::GetRectWithScroll() const
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	RECT rc;

	rc.left = m_tRect.left + fScrollX;
	rc.top = m_tRect.top + fScrollY;
	rc.right = m_tRect.right + fScrollX;
	rc.bottom = m_tRect.bottom + fScrollY;


	return rc;
}

const RECT CObj::GetSelectRectWithScroll() const
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	RECT rc;

	rc.left = m_tSelectRect.left + fScrollX;
	rc.top = m_tSelectRect.top + fScrollY;
	rc.right = m_tSelectRect.right + fScrollX;
	rc.bottom = m_tSelectRect.bottom + fScrollY;


	return rc;
}

bool CObj::IsClicked(const POINT& pos) const
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	INTPOINT	mouseIdx = TILEMANAGER->GetIndex(pos);
	INTPOINT	unitIdx;
	POINT unitPos;

	for (unitPos.x = m_tSelectRect.left; unitPos.x < m_tSelectRect.right; unitPos.x += TILE_SIZE) {
		for (unitPos.y = m_tSelectRect.top; unitPos.y < m_tSelectRect.bottom; unitPos.y += TILE_SIZE) {
			unitIdx = TILEMANAGER->GetIndex(unitPos);
			if (mouseIdx.x == unitIdx.x && mouseIdx.y == unitIdx.y) return true;
		}
	}

	return false;
}




void CObj::SetMove(node_t* node)
{
	m_bMove = true;
	m_moveNode = node;
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


