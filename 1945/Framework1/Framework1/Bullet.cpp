#include "stdafx.h"
#include "Bullet.h"

void Bullet::Init()
{
}

void Bullet::LateInit()
{
}

int Bullet::Update()
{
	return 0;
}

void Bullet::LateUpdate()
{
}

void Bullet::Render()
{
}

void Bullet::Realease()
{
}

bool Bullet::NoOut()
{
	if (m_info.m_y >= H_MAX + 30)
		return true;
	if (m_info.m_x >= W_MAX + 30)
		return true;
	if (m_info.m_x <= 0 - 30)
		return true;
	if (m_info.m_y <= 0 - 30)
		return true;
	return false;
}

void Bullet::SetMissileRect()
{
	m_rect.left = m_info.m_x;
	m_rect.top = m_info.m_y;
	m_rect.right = m_rect.left + m_info.m_w;
	m_rect.bottom = m_info.m_y + m_info.m_h;
}
