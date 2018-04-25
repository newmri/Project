#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::Init()
{
	m_time = GetTickCount();
	iIAM = rand() % 2;
	m_info.m_degree = Dir[rand() % 5];
	m_info.m_speed = 5;

	m_info.m_w = BITMAPMANAGER->GetImage()["ITEM"]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()["ITEM"]->GetHeight();
	m_animationCnt = 0;

}

void Item::LateInit()
{
	m_animationTime = GetTickCount();

}

int Item::Update()
{
	Obj::LateInit();

	if (is_dead) {
		SOUNDMANAGER->PlayerEffectSound(ITEM_DROP_EFSD);
		return true;
	}
	if (m_info.m_y >= H_MAX)
	{
		if (m_info.m_degree == 315)
			m_info.m_degree = 45;
		else if (m_info.m_degree == 225)
			m_info.m_degree = 125;

	}
	else if (m_info.m_y <= 0)
	{
		if (m_info.m_degree == 45)
			m_info.m_degree = 315;
		else if (m_info.m_degree == 135)
			m_info.m_degree = 225;
	}
	else if (m_info.m_x >= W_MAX)
	{
		if (m_info.m_degree == 315)
			m_info.m_degree = 225;
		else if (m_info.m_degree == 45)
			m_info.m_degree = 135;
	}
	else if (m_info.m_x <= 0)
	{
		if (m_info.m_degree == 225)
			m_info.m_degree = 315;
		else if (m_info.m_degree == 135)
			m_info.m_degree = 45;

	}


	m_info.m_x += cosf(m_info.m_degree * PI / 180.f) * m_info.m_speed;
	m_info.m_y -= sinf(m_info.m_degree * PI / 180.f) * m_info.m_speed;

	if (m_time + 10000 < GetTickCount())
		return true;
	return 0;
}

void Item::LateUpdate()
{
	if (m_animationTime + (1000 / ITEM_IMAGE_NUM) < GetTickCount()) {
		m_animationCnt = (m_animationCnt + 1) % ITEM_IMAGE_NUM;
		m_animationTime = GetTickCount();
	}
	SetItemRect();
}

void Item::Render()
{

	BITMAPMANAGER->GetImage()["ITEM"]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_info.m_w / ITEM_IMAGE_NUM,
		m_info.m_h,
		(m_info.m_w / ITEM_IMAGE_NUM) * m_animationCnt,
		0,
		m_info.m_w / ITEM_IMAGE_NUM,
		m_info.m_h, RGB(255, 255, 255));

}

void Item::Realease()
{
}

void Item::SetItemRect()
{
	m_rect.left = m_info.m_x;
	m_rect.top = m_info.m_y;
	m_rect.right = m_info.m_x + m_info.m_w / ITEM_IMAGE_NUM;
	m_rect.bottom = m_info.m_y + m_info.m_h;
}


