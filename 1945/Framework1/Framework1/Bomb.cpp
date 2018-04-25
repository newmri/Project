#include "stdafx.h"
#include "Bomb.h"


Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

void Bomb::Init()
{
	m_info.m_w = W_MAX;
	m_info.m_h = W_MAX;
	m_time = GetTickCount();
}

void Bomb::LateInit()
{
}

int Bomb::Update()
{
	if (m_time + 2000 < GetTickCount())
		return true;
	return 0;
}

void Bomb::LateUpdate()
{
}

void Bomb::Render()
{
	SetRect();
	Ellipse(RENDERMANAGER->GetMemDC(), m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

}

void Bomb::Realease()
{
}
