#include "stdafx.h"
#include "Boss.h"
#include "EnemyNormalBullet.h"

CBoss::CBoss()
{
}


CBoss::~CBoss()
{
}

void CBoss::Init()
{
	
	m_bulletSpawnTime = GetTickCount();

	m_normalBulletSpawnTime = (rand() % (NORMAL_ENEMY_BULLET_MAX_SPAWN_TIME - NORMAL_ENEMY_BULLET_MIN_SPAWN_TIME)) + NORMAL_ENEMY_BULLET_MIN_SPAWN_TIME;
	m_stat.m_cHp = 100;
}

void CBoss::LateInit()
{
	m_info.m_w = BITMAPMANAGER->GetImage()[m_imageName]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()[m_imageName]->GetHeight();
}

int CBoss::Update()
{
	Obj::LateInit();

	if (is_dead) {
		SOUNDMANAGER->PlayerEffectSound(DIE_EFSD);
		if (!strcmp(m_imageName, "BOSS1")) SCENEMANAGER->IncreaseScore(BOSS_SCORE);
		else SCENEMANAGER->IncreaseScore(BOSS_SCORE * 2);
		for(int i = 0; i < 20; ++i)
		if (rand() % 100 <= ITEM_SPAWN_PERCENT) SCENEMANAGER->CreateItem(rand() % W_MAX, rand() % H_MAX);

		return true;
	}
	if (m_bulletSpawnTime + m_normalBulletSpawnTime < GetTickCount()) {
		Obj* p = ObjMaker<CEnymyNormalBullet>::Create(m_info.m_x + m_info.m_w / 3, m_info.m_y + m_info.m_h / 2, "NORMAL_ENEMY_BULLET_LV1");
		Obj* p2 = ObjMaker<CEnymyNormalBullet>::Create(m_info.m_x + m_info.m_w / 1.5f, m_info.m_y + m_info.m_h / 2, "NORMAL_ENEMY_BULLET_LV1");
		if (!strcmp(m_imageName, "BOSS2")) {
			Obj* p = ObjMaker<CEnymyNormalBullet>::Create(rand() % W_MAX, m_info.m_y + m_info.m_h / 2, "NORMAL_ENEMY_BULLET_LV1");
			Obj* p2 = ObjMaker<CEnymyNormalBullet>::Create(rand() % W_MAX, m_info.m_y + m_info.m_h / 2, "NORMAL_ENEMY_BULLET_LV1");
			m_normalBulletLlist->push_back(p);
			m_normalBulletLlist->push_back(p2);
		}
		m_normalBulletLlist->push_back(p);
		m_normalBulletLlist->push_back(p2);

		m_bulletSpawnTime = GetTickCount();
	}


	if (m_info.m_y > H_MAX) return true;

	return 0;
}

void CBoss::LateUpdate()
{
	SetRect();
}

void CBoss::Render()
{
	BITMAPMANAGER->GetImage()[m_imageName]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_info.m_w,
		m_info.m_h,
		0,
		0,
		m_info.m_w,
		m_info.m_h, RGB(255, 255, 255));
}

void CBoss::Realease()
{
}
