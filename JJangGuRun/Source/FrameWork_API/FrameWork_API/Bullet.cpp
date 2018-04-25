#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Init()
{
	srand((unsigned)time(nullptr));

	m_PoopType = rand() % 2 + 1;

	m_info.nW = 30.f;
	m_info.nH = 30.f;

	m_info.fSpeed = 5.f;

	m_dwAnimTIme = GetTickCount();
}

void CBullet::LateInit()
{
	m_AnimNum = 1;
	if (m_eStoneType == ObstacleID::POOP)
	{
		m_info.nW = 70.f;
		m_info.nH = 70.f;

		m_info.fSpeed = 5.f;
	}
}

int CBullet::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;

	switch (m_eStoneType)
	{
	case ObstacleID::SHOOTING_UP:
		m_info.fY -= m_info.fSpeed;
		break;
	case ObstacleID::SHOOTING_DOWN:
		m_info.fY += m_info.fSpeed;
		break;
	case ObstacleID::SHOOTING_LEFT:
		m_info.fX -= m_info.fSpeed;
		break;
	case ObstacleID::SHOOTING_RIGHT:
		m_info.fX += m_info.fSpeed;
		break;
	case ObstacleID::POOP:
		m_info.fY += m_info.fSpeed;
		break;
	default:
		break;
	}


	return NO_EVENT;
}

void CBullet::LateUpdate()
{
	CObj::UpdateRect();

	if (m_info.fX < 0 || m_info.fX > WINDOWS_WIDTH)
		m_bIsDead = true;
}

void CBullet::Render()
{
	float fScrollY = SCROLLMANAGER->GetInstance()->GetScrollY();

	if (m_eStoneType == ObstacleID::POOP)
	{
		if (m_PoopType == 1)
		{
			BITMAPMANAGER->GetImage()["BULLET6"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
				70,
				70,
				0,
				0,
				70,
				70, RGB(255, 255, 255));
		}
		else
		{
			BITMAPMANAGER->GetImage()["BULLET7"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
				70,
				70,
				0,
				0,
				70,
				70, RGB(255, 255, 255));
		}
	}
	else
	{
		if (m_dwAnimTIme + 1000 << GetTickCount())
		{
			++m_AnimNum;
			if (m_AnimNum > 5)
				m_AnimNum = 1;

			m_dwAnimTIme = GetTickCount();
		}

		switch (m_AnimNum)
		{
		case 1:
			BITMAPMANAGER->GetImage()["BULLET1"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
				30,
				30,
				0,
				0,
				30,
				30, RGB(255, 255, 255));
			break;
		case 2:
			BITMAPMANAGER->GetImage()["BULLET2"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
				30,
				30,
				0,
				0,
				30,
				30, RGB(255, 255, 255));
			break;
		case 3:
			BITMAPMANAGER->GetImage()["BULLET3"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
				30,
				30,
				0,
				0,
				30,
				30, RGB(255, 255, 255));
			break;
		case 4:
			BITMAPMANAGER->GetImage()["BULLET4"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
				30,
				30,
				0,
				0,
				30,
				30, RGB(255, 255, 255));
			break;
		case 5:
			BITMAPMANAGER->GetImage()["BULLET5"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
				static_cast<int>(m_info.fX - m_info.nW / 2),
				static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
				30,
				30,
				0,
				0,
				30,
				30, RGB(255, 255, 255));
			break;
		}
	}
}

void CBullet::Release()
{
}
