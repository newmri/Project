#include "stdafx.h"
#include "Skill.h"
#include"SkillBullet.h"

Skill::Skill()
{
}


Skill::~Skill()
{
}

void Skill::Init()
{
	m_time = GetTickCount();
}

void Skill::LateInit()
{
	m_info.m_w = BITMAPMANAGER->GetImage()["SKILL_AIR_PLANE"]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()["SKILL_AIR_PLANE"]->GetHeight();
}

int Skill::Update()
{
	Obj::LateInit();

	if (rl)
	{
		m_info.m_x -= 5;
		rl = false;
	}
	if (!rl)
	{
		m_info.m_x += 5;
		rl = true;
	}
	//ÀÏ¹Ý ÃÑ¾Ë
	if (my_level == 1)
	{
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x, m_info.m_y - 30, "NORMAL_BULLET_LV1"));
	}
	else if (my_level == 2)
	{
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV1"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV1"));

	}
	else if (my_level == 3)
	{
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x, m_info.m_y, "NORMAL_BULLET_LV2"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y, "NORMAL_BULLET_LV2"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y, "NORMAL_BULLET_LV2"));

	}
	else if (my_level == 4)
	{
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x - WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV3"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x + WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV3"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV3"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV3"));

	}
	else if (my_level == 5)
	{
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x, m_info.m_y - 30, "NORMAL_BULLET_LV4"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x - WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV4"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x + WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV4"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV4"));
		m_skillbulletlist->push_back(ObjMaker<SkillBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV4"));

	}
	if (m_time + 2000 < GetTickCount())
		return true;
	return 0;
}

void Skill::LateUpdate()
{
	SetRect();
}

void Skill::Render()
{
	Obj::LateInit();

	BITMAPMANAGER->GetImage()["SKILL_AIR_PLANE"]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_info.m_w,
		m_info.m_h,
		0,
		0,
		m_info.m_w,
		m_info.m_h, RGB(255, 255, 255));
}

void Skill::Realease()
{
}
