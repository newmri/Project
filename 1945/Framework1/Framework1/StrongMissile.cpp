#include "stdafx.h"
#include "StrongMissile.h"


StrongMissile::StrongMissile()
{
}


StrongMissile::~StrongMissile()
{
}

void StrongMissile::Init()
{
	m_info.m_w = BITMAPMANAGER->GetImage()["MISSILE2"]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()["MISSILE2"]->GetHeight();
	m_info.m_speed = 5;

	m_info.m_degree = 90 * PI / 180;

	m_stat.m_Atk = 1;

	ex_target_dis = W_MAX * W_MAX + H_MAX * H_MAX;

}

void StrongMissile::LateInit()
{
}

int StrongMissile::Update()
{
	if (is_dead) return true;

	if (m_monsterlist->size() == 0) {

		m_info.m_x += cosf(m_info.m_degree) * m_info.m_speed;
		m_info.m_y -= sinf(m_info.m_degree) * m_info.m_speed;

	}
	else {
		for (auto& a : (*m_monsterlist)) {
			target_x = a->GetInfo().m_x - m_info.m_x;
			target_y = a->GetInfo().m_y - m_info.m_y;
			target_dis = target_x * target_x + target_y * target_y;
			if (target_dis < ex_target_dis)
			{
				ex_target_dis = target_dis;
				m_info.m_degree = acosf(target_x / sqrt(ex_target_dis));
				if (m_info.m_y < a->GetInfo().m_y)
					m_info.m_degree *= -1.f;
			}

		}
		m_info.m_x += cosf(m_info.m_degree) * m_info.m_speed;
		m_info.m_y -= sinf(m_info.m_degree) * m_info.m_speed;

	}
	if (Bullet::NoOut()) {
		return true;
	}

	return 0;
}

void StrongMissile::LateUpdate()
{
	SetMissileRect();
}

void StrongMissile::Render()
{
	BITMAPMANAGER->GetImage()["MISSILE2"]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_info.m_w,
		m_info.m_h,
		0,
		0,
		m_info.m_w,
		m_info.m_h, RGB(255, 255, 255));

}

void StrongMissile::Realease()
{
}
