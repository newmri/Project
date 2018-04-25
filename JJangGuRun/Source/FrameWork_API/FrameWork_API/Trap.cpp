#include "stdafx.h"
#include "Trap.h"

CTrap::CTrap()
{
}


CTrap::~CTrap()
{
	Release();
}

void CTrap::Init()
{
}

void CTrap::LateInit()
{
}

int CTrap::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;


	return NO_EVENT;
}

void CTrap::LateUpdate()
{
	UpdateLine();
}

void CTrap::Render()
{
	float fScrollY = SCROLLMANAGER->GetScrollY();

	if (m_eStoneType == ObstacleID::THORN_UP)
	{

		BITMAPMANAGER->GetImage()["BLOCK6"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_tLine[SegmentPos::LEFT].iFirstPtX),
			static_cast<int>(m_tLine[SegmentPos::LEFT].iFirstPtY - 50 + fScrollY),
			100,
			50,
			0,
			0,
			100,
			50, RGB(255, 255, 255));
	}
	else if (m_eStoneType == ObstacleID::THORN_DOWN)
	{
		BITMAPMANAGER->GetImage()["BLOCK7"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_tLine[SegmentPos::LEFT].iFirstPtX),
			static_cast<int>(m_tLine[SegmentPos::RIGHT].iLastPtY + fScrollY),
			100,
			50,
			0,
			0,
			100,
			50, RGB(255, 255, 255));
	}
}

void CTrap::Release()
{
}

void CTrap::SetPoint(POINT pPoint[])
{
	for (int i = 0; i < 3; i++)
	{
		m_pPoint[i].x = pPoint[i].x;
		m_pPoint[i].y = pPoint[i].y;
	}
}

void CTrap::UpdateLine()
{
	m_tLine[SegmentPos::LEFT].iFirstPtX = m_pPoint[0].x;
	m_tLine[SegmentPos::LEFT].iFirstPtY = m_pPoint[0].y;
	m_tLine[SegmentPos::LEFT].iLastPtX = m_pPoint[1].x;
	m_tLine[SegmentPos::LEFT].iLastPtY = m_pPoint[1].y;

	m_tLine[SegmentPos::RIGHT].iFirstPtX = m_pPoint[1].x;
	m_tLine[SegmentPos::RIGHT].iFirstPtY = m_pPoint[1].y;
	m_tLine[SegmentPos::RIGHT].iLastPtX = m_pPoint[2].x;
	m_tLine[SegmentPos::RIGHT].iLastPtY = m_pPoint[2].y;
}
