#include "stdafx.h"
#include "NormalEnemy.h"
#include "EnemyNormalBullet.h"

CNormalEnemy::CNormalEnemy()
{
}


CNormalEnemy::~CNormalEnemy()
{
}

void CNormalEnemy::Init()
{
	m_info.m_w = BITMAPMANAGER->GetImage()["ENEMY1"]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()["ENEMY1"]->GetHeight();

	m_bulletSpawnTime = GetTickCount();

	m_normalBulletSpawnTime = (rand() % (NORMAL_ENEMY_BULLET_MAX_SPAWN_TIME - NORMAL_ENEMY_BULLET_MIN_SPAWN_TIME)) + NORMAL_ENEMY_BULLET_MIN_SPAWN_TIME;

}

void CNormalEnemy::LateInit()
{
	m_firstX = m_info.m_x;
	m_firstY = m_info.m_y;
	m_info.m_degree = 0;

}

int CNormalEnemy::Update()
{
	Obj::LateInit();

	if (is_dead) {

		SOUNDMANAGER->PlayerEffectSound(DIE_EFSD);
		SCENEMANAGER->IncreaseScore(ENEMY_SCORE);

		if (rand() % 100 <= ITEM_SPAWN_PERCENT) SCENEMANAGER->CreateItem(m_info.m_x, m_info.m_y);
		return true;
	}
	if (m_bulletSpawnTime + m_normalBulletSpawnTime < GetTickCount()) {
		Obj* p = ObjMaker<CEnymyNormalBullet>::Create(m_info.m_x, m_info.m_y, "NORMAL_ENEMY_BULLET_LV1");
		m_normalBulletLlist->push_back(p);
		m_bulletSpawnTime = GetTickCount();
	}
	m_info.m_y += m_info.m_speed;

	if (m_info.m_y > H_MAX) return true;

	return 0;
}

void CNormalEnemy::LateUpdate()
{
	SetRect();
}

void CNormalEnemy::Render()
{
	//HBITMAP  bitmap = BITMAPMANAGER->CreateMask(RENDERMANAGER->GetMemDC(), m_info.m_w, m_info.m_h);

	//BITMAPMANAGER->RotateSizingImage(RENDERMANAGER->GetMemDC(), (HBITMAP)*BITMAPMANAGER->GetImage()["ENEMY1"],
	//	RENDERMANAGER->GetRect(),
	//	m_info.m_degree,
	//	m_info.m_w / 2,
	//	m_info.m_h / 2,
	//	m_info.m_x,
	//	m_info.m_y,
	//	1.0,
	//	bitmap);

	
	BITMAPMANAGER->GetImage()["ENEMY1"]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_info.m_w,
		m_info.m_h,
		0,
		0,
		m_info.m_w,
		m_info.m_h, RGB(255, 255, 255));
		
		
}

void CNormalEnemy::Realease()
{
}
