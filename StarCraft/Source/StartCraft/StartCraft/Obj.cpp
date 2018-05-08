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

bool CObj::IsClicked(const INTPOINT& pos) const
{
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	INTPOINT	mouseIdx = TILEMANAGER->GetIndex(pos);
	INTPOINT	unitIdx;
	INTPOINT unitPos;

	for (unitPos.x = m_tSelectRect.left + fScrollX; unitPos.x < m_tSelectRect.right + fScrollX; unitPos.x += TILE_SIZE) {
		for (unitPos.y = m_tSelectRect.top + fScrollY; unitPos.y < m_tSelectRect.bottom + fScrollY; unitPos.y += TILE_SIZE) {
			unitIdx = TILEMANAGER->GetIndex(unitPos);
			if (mouseIdx.x == unitIdx.x && mouseIdx.y == unitIdx.y) return true;
		}
	}

	return false;
}


void CObj::SetMove(node_t* node)
{
	m_bMove = true;

	m_route.clear();

	while (node->prev_node != NULL) {
		m_route.push_front(node->pos);
		node = node->prev_node;
	}

	if (m_route.empty()) return;

	INTPOINT pos;
	pos.x = m_tSelectRect.left;
	pos.y = m_tSelectRect.top;

	INTPOINT idx = TILEMANAGER->GetIndex(pos);

	FLOATPOINT tSrc(static_cast<float>(idx.x * TILE_SIZE), static_cast<float>(idx.y * TILE_SIZE));
	FLOATPOINT tDest(static_cast<float>(m_route.front().x * TILE_SIZE), static_cast<float>((m_route.front().y * TILE_SIZE)));

	int angle = static_cast<int>(m_tInfo.fAngle);

	m_tInfo.fAngle = MATHMANAGER->CalcDegree(tDest, tSrc);


	float _Height = (float)abs(idx.y * TILE_SIZE - m_route.front().y * TILE_SIZE); // 현재 캐릭터의 좌표와 마우스와의 좌표 사이의 높이를 구해준다. 
	float _Bottom = (float)abs(idx.x * TILE_SIZE - m_route.front().x * TILE_SIZE); // 현재 캐릭터의 좌표와 마우스와의 좌표 사이의 밑변의 길이를 구해준다. 
	float _R = sqrt((_Height*_Height) + (_Bottom*_Bottom)); // 빗변을 구하는 공식. 
															// 길이 = 속도(이동픽셀) * 시간 =&gt; 시간 = 길이 / 이동 픽셀 

	m_maxCnt = _R / m_tInfo.fSpeed;


	// 시간을 X또는 Y축과 나누면 그 축으로 시간만큼 얼마나 이동해야 정해진 시간안에 목표에 도달하는지를 구할 수 있다. 
	m_tMovePos.fX = _Bottom / m_maxCnt;
	m_tMovePos.fY = _Height / m_maxCnt;

	angle = m_tInfo.fAngle;

	if (angle == TOP) m_tMovePos.fY = -m_tMovePos.fY;
	else if (angle == LEFT) m_tMovePos.fX = -m_tMovePos.fX;
	else if (angle > TOP && angle < LEFT) {
		m_tMovePos.fX = -m_tMovePos.fX;
		m_tMovePos.fY = -m_tMovePos.fY;


	}
	else if (angle > LEFT && angle < BOTTOM) m_tMovePos.fX = -m_tMovePos.fX;

	else if (angle > 0 && angle < TOP) m_tMovePos.fY = -m_tMovePos.fY;


	m_dwTime = GetTickCount();
	m_cnt = 0;
	m_nBoforeIdx = 0;
}

CObj::CObj()
{
	m_bIsDead = false;
	m_bIsInit = false;
	m_bIsUI = false;
	m_bIsStructure = false;
}

CObj::~CObj()
{
}


