#include "stdafx.h"
#include "EnemyNormalBullet.h"

void CEnymyNormalBullet::Init()
{
	m_info.m_w = BITMAPMANAGER->GetImage()["NORMAL_ENEMY_BULLET_LV1"]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()["NORMAL_ENEMY_BULLET_LV1"]->GetHeight();

	m_info.m_speed = 10;

	m_stat.m_Atk = 1;

}

void CEnymyNormalBullet::LateInit()
{
}

int CEnymyNormalBullet::Update()
{
	Obj::LateInit();

	if (is_dead) return true;

	m_info.m_y += 10;
	if (NoOut()) {
		return true;
	}
	return 0;
}

void CEnymyNormalBullet::LateUpdate()
{
	SetRect();
}

void CEnymyNormalBullet::Render()
{
	BITMAPMANAGER->GetImage()[m_imageName]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_info.m_w,
		m_info.m_h,
		0,
		0,
		m_info.m_w,
		m_info.m_h, RGB(255, 255, 255));
}

void CEnymyNormalBullet::Realease()
{
}
