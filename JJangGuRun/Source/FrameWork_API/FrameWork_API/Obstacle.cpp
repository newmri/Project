#include "stdafx.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "Trap.h"


CObstacle::CObstacle()
{
}

CObstacle::CObstacle(const BLOCKINFO & rInfo)
{
	m_info.fX = rInfo.tBlock.fX;
	m_info.fY = rInfo.tBlock.fY;
	m_info.nW = rInfo.tBlock.nW;
	m_info.nH = rInfo.tBlock.nH;

	m_eStoneType = rInfo.tBlock.eID;
	m_AnimNum = 0;
}


CObstacle::~CObstacle()
{
	Release();
}

void CObstacle::Init()
{
}

void CObstacle::LateInit()
{
	CObj::UpdateRect();

	m_dwOld = -1;
	m_dwBullet = GetTickCount();
	m_dwPoop = GetTickCount();
	m_dwPoopBlock = GetTickCount();

	m_fOldposX = m_info.fX;
	m_fOldposY = m_info.fY;

	switch (m_eStoneType)
	{
	case ObstacleID::COMMON:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK1"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK1"]->GetHeight();
		break;
	case ObstacleID::MOVING:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK2"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK2"]->GetHeight();
		m_info.fSpeed = 1.f;
		break;
	case ObstacleID::RAIL_LEFT:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK3"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK3"]->GetHeight();
		break;
	case ObstacleID::RAIL_RIGHT:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK4"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK4"]->GetHeight();
		break;
	case ObstacleID::WALL:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK5"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK5"]->GetHeight();
		break;
	case ObstacleID::THORN_UP:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK1"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK1"]->GetHeight();
		CreateThorn(ObstacleID::THORN_UP);
		break;
	case ObstacleID::THORN_DOWN:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK1"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK1"]->GetHeight();
		CreateThorn(ObstacleID::THORN_DOWN);
		break;
	case ObstacleID::SHOOTING_UP:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK8"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK8"]->GetHeight();
		break;
	case ObstacleID::SHOOTING_DOWN:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK9"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK9"]->GetHeight();
		break;
	case ObstacleID::SHOOTING_LEFT:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK10"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK10"]->GetHeight();
		break;
	case ObstacleID::SHOOTING_RIGHT:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK11"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK11"]->GetHeight();
		break;
	case ObstacleID::POOP:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK12"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK12"]->GetHeight();
		break;
	case ObstacleID::END:
		m_info.nW = BITMAPMANAGER->GetImage()["BLOCK1"]->GetWidth();
		m_info.nH = BITMAPMANAGER->GetImage()["BLOCK1"]->GetHeight();
		break;
	default:
		break;
	}

}

int CObstacle::Update()
{
	CObj::LateInit();


	switch (m_eStoneType)
	{
	case ObstacleID::COMMON:
		if (m_bIsDead)
		{
			SetCount();
			if (m_dwOld + 2000 < GetTickCount())
			{
				return DEAD_OBSTACLE;
			}
		}
		break;
	case ObstacleID::MOVING:
		MovingStone();
		break;
	case ObstacleID::RAIL_LEFT:
		break;
	case ObstacleID::RAIL_RIGHT:
		break;
	case ObstacleID::WALL:
		break;
	case ObstacleID::THORN_UP:
		break;
	case ObstacleID::THORN_DOWN:
		break;
	case ObstacleID::SHOOTING_UP:
		CreateBullet(ObstacleID::SHOOTING_UP);
		break;
	case ObstacleID::SHOOTING_DOWN:
		CreateBullet(ObstacleID::SHOOTING_DOWN);
		break;
	case ObstacleID::SHOOTING_LEFT:
		CreateBullet(ObstacleID::SHOOTING_LEFT);
		break;
	case ObstacleID::SHOOTING_RIGHT:
		CreateBullet(ObstacleID::SHOOTING_RIGHT);
		break;
	case ObstacleID::POOP:
		CreatePoop(ObstacleID::POOP);
		break;
	case ObstacleID::END:
		break;
	default:
		break;
	}
	return NO_EVENT;
}

void CObstacle::LateUpdate()
{
	CObj::UpdateLine();
}

void CObstacle::Render()
{
	CObj::UpdateRect();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	switch (m_eStoneType)
	{
	case ObstacleID::COMMON:
		BITMAPMANAGER->GetImage()["BLOCK1"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(255, 255, 255));
		break;
	case ObstacleID::MOVING:
		BITMAPMANAGER->GetImage()["BLOCK2"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(255, 255, 255));
		break;
	case ObstacleID::RAIL_LEFT:
		BITMAPMANAGER->GetImage()["BLOCK3"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(255, 255, 255));
		break;
	case ObstacleID::RAIL_RIGHT:
		BITMAPMANAGER->GetImage()["BLOCK4"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(255, 255, 255));
		break;
	case ObstacleID::WALL:
		if (m_info.fX < WINDOWS_WIDTH / 2)
		{
			BITMAPMANAGER->GetImage()["BLOCK5"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
				m_info.nW,
				m_info.nH,
				0,
				0,
				m_info.nW,
				m_info.nH, RGB(84, 110, 140));
		}
		else
		{
			BITMAPMANAGER->GetImage()["BLOCK14"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
				m_info.nW,
				m_info.nH,
				0,
				0,
				m_info.nW,
				m_info.nH, RGB(84, 110, 140));
		}
		break;
	case ObstacleID::THORN_UP:
		BITMAPMANAGER->GetImage()["BLOCK1"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(255, 255, 255));
		break;
	case ObstacleID::THORN_DOWN:
		BITMAPMANAGER->GetImage()["BLOCK1"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(255, 255, 255));
		break;
	case ObstacleID::SHOOTING_UP:
		BITMAPMANAGER->GetImage()["BLOCK8"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(0, 0, 0));
		break;
	case ObstacleID::SHOOTING_DOWN:
		BITMAPMANAGER->GetImage()["BLOCK9"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(0, 0, 0));
		break;
	case ObstacleID::SHOOTING_LEFT:
		BITMAPMANAGER->GetImage()["BLOCK10"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(0, 0, 0));
		break;
	case ObstacleID::SHOOTING_RIGHT:
		BITMAPMANAGER->GetImage()["BLOCK11"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(0, 0, 0));
		break;
	case ObstacleID::POOP:
		if (m_AnimNum == 1)
		{
			BITMAPMANAGER->GetImage()["BLOCK12"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
				m_info.nW,
				m_info.nH,
				0,
				0,
				m_info.nW,
				m_info.nH, RGB(255, 255, 255));
		}
		else
		{
			BITMAPMANAGER->GetImage()["BLOCK13"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
				m_info.nW,
				m_info.nH,
				0,
				0,
				m_info.nW,
				m_info.nH, RGB(255, 255, 255));
		}
		break;
	case ObstacleID::END:
		BITMAPMANAGER->GetImage()["BLOCK1"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_info.fX - m_info.nW / 2),
			static_cast<int>((m_info.fY - m_info.nH / 2) + fScrollY),
			m_info.nW,
			m_info.nH,
			0,
			0,
			m_info.nW,
			m_info.nH, RGB(255, 255, 255));
		break;
	default:
		break;
	}
}

void CObstacle::Release()
{
}

void CObstacle::MovingStone()
{
	m_info.fX += m_info.fSpeed;

	if (m_fOldposX + 100 <= m_info.fX || m_info.fX <= m_fOldposX - 100)
		m_info.fSpeed *= -1.f;
}

void CObstacle::CreateBullet(ObstacleID::OBSTACLE eID)
{
	if (m_dwBullet + 2000 < GetTickCount())
	{
		CObj* pObj = nullptr;
		switch (eID)
		{
		case ObstacleID::SHOOTING_UP:
			pObj = CFactoryManager<CBullet>::CreateObj(m_info.fX, m_info.fY - m_info.nH, eID);
			break;
		case ObstacleID::SHOOTING_DOWN:
			pObj = CFactoryManager<CBullet>::CreateObj(m_info.fX, m_info.fY + m_info.nH, eID);
			break;
		case ObstacleID::SHOOTING_LEFT:
			pObj = CFactoryManager<CBullet>::CreateObj(m_info.fX - m_info.nW, m_info.fY, eID);
			break;
		case ObstacleID::SHOOTING_RIGHT:
			pObj = CFactoryManager<CBullet>::CreateObj(m_info.fX + m_info.nW, m_info.fY, eID);
			break;
		}
		OBJMANAGER->AddObject(pObj, OBJTYPE::BULLET);
		m_dwBullet = GetTickCount();
	}
}

void CObstacle::CreatePoop(ObstacleID::OBSTACLE eID)
{
	if (m_dwPoop + 2000 < GetTickCount())
	{
		CObj* pObj = nullptr;
		pObj = CFactoryManager<CBullet>::CreateObj(m_info.fX, m_info.fY + m_info.nH, eID);
		OBJMANAGER->AddObject(pObj, OBJTYPE::BULLET);

		m_AnimNum = 2;
		m_dwPoop = GetTickCount();
		m_dwPoopBlock = GetTickCount();
	}

	if (m_dwPoopBlock + 1000 < GetTickCount())
	{
		m_AnimNum = 1;
	}
}

void CObstacle::CreateThorn(ObstacleID::OBSTACLE eID)
{
	CObj::UpdateRect();
	POINT pThorn[3];
	CObj* pObj = nullptr;

	switch (eID)
	{
	case ObstacleID::THORN_UP:
		pObj = CFactoryManager<CTrap>::CreateObj(eID);

		pThorn[0].x = m_rect.left + 50;
		pThorn[0].y = m_rect.top;

		pThorn[1].x = (m_rect.left + m_rect.right) / 2;
		pThorn[1].y = m_rect.top - 50;

		pThorn[2].x = m_rect.right - 50;
		pThorn[2].y = m_rect.top;

		dynamic_cast<CTrap*>(pObj)->SetPoint(pThorn);
		break;
	case ObstacleID::THORN_DOWN:
		pObj = CFactoryManager<CTrap>::CreateObj(eID);

		pThorn[0].x = m_rect.left + 50;
		pThorn[0].y = m_rect.bottom;

		pThorn[1].x = (m_rect.left + m_rect.right) / 2;
		pThorn[1].y = m_rect.bottom + 50;

		pThorn[2].x = m_rect.right - 50;
		pThorn[2].y = m_rect.bottom;

		dynamic_cast<CTrap*>(pObj)->SetPoint(pThorn);
		break;
	}

	OBJMANAGER->AddObject(pObj, OBJTYPE::TRAP);
}


void CObstacle::SetCount()
{
	if (m_dwOld != -1)
		return;
	else
		m_dwOld = GetTickCount();
}