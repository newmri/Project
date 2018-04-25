#include "stdafx.h"
#include "Enemy.h"

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
	Release();
}

void CEnemy::Init()
{
	m_stat.nDamage = 0;

	m_info.fX = WINDOWS_WIDTH / 2;
	m_info.fY = WINDOWS_HEIGHT * 2;

	m_info.nW = WINDOWS_WIDTH;
	m_info.nH = WINDOWS_HEIGHT;
}

void CEnemy::LateInit()
{
}

int CEnemy::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;

	m_info.fY -= 0.5f;
	if (KEYMANAGER->KeyPressing(VK_UP)) m_info.fY = 9999.f;

	return NO_EVENT;
}

void CEnemy::LateUpdate()
{
}

void CEnemy::Render()
{
	CObj::UpdateRect();

	float fScrollY = SCROLLMANAGER->GetScrollY();


	BITMAPMANAGER->GetImage()["ENEMY1"]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_info.fX - m_info.nW / 2),
		static_cast<int>(m_info.fY - m_info.nH / 2 + fScrollY),
		m_info.nW,
		m_info.nH,
		0,
		0,
		m_info.nW,
		m_info.nH, RGB(0, 0, 0));
	//BitBlt(RENDERMANAGER->GetMemDC(), m_info.fX - m_info.nW / 2, m_info.fY - m_info.nH / 2, WINDOWS_WIDTH, WINDOWS_HEIGHT, BITMAPMANAGER->GetImage()["ENEMY1"]->GetDC(), 0, 0, SRCCOPY);

	//
}

void CEnemy::Release()
{
}