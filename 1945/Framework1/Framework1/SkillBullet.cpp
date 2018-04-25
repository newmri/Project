#include "stdafx.h"
#include "SkillBullet.h"


SkillBullet::SkillBullet()
{

}


SkillBullet::~SkillBullet()
{
}

void SkillBullet::Init()
{

	m_info.m_speed = 10;

	m_stat.m_Atk = 1;

}

void SkillBullet::LateInit()
{
	m_info.m_w = BITMAPMANAGER->GetImage()[m_imageName]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()[m_imageName]->GetHeight();
}

int SkillBullet::Update()
{
	Obj::LateInit();

	m_info.m_y -= 10;
	if (NoOut()) {
		return true;
	}
	return 0;
}

void SkillBullet::LateUpdate()
{
	SetRect();
}

void SkillBullet::Render()
{
	BITMAPMANAGER->GetImage()[m_imageName]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_info.m_w,
		m_info.m_h,
		0,
		0,
		m_info.m_w,
		m_info.m_h, RGB(255, 255, 255));

}

void SkillBullet::Realease()
{
}
