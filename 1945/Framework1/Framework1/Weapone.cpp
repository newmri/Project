#include "stdafx.h"
#include "Weapone.h"
#include"Missile.h"
#include"NomalBullet.h"
#include"Skill.h"

Weapone::Weapone()
{
}


Weapone::~Weapone()
{
}

void Weapone::Init()
{
	m_info.m_w = C_W;
	m_info.m_h = C_H;
}

void Weapone::LateInit()
{
}

int Weapone::Update()
{
	//ÀÏ¹Ý ÃÑ¾Ë
	if (my_level == 1)
	{
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x, m_info.m_y - 30, "NORMAL_BULLET_LV1"));
	}
	else if (my_level == 2)
	{
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV1"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV1"));

	}
	else if (my_level == 3)
	{
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x, m_info.m_y, "NORMAL_BULLET_LV2"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y, "NORMAL_BULLET_LV2"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y, "NORMAL_BULLET_LV2"));

	}
	else if (my_level == 4)
	{
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x - WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV3"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x + WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV3"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV3"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV3"));

	}
	else if (my_level == 5)
	{
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x, m_info.m_y - 30, "NORMAL_BULLET_LV4"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x - WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV4"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x + WEAPONE_W / 2, m_info.m_y, "NORMAL_BULLET_LV4"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x - WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV4"));
		m_bulletlist->push_back(ObjMaker<NomalBullet>::Create(m_info.m_x + WEAPONE_W, m_info.m_y - 15, "NORMAL_BULLET_LV4"));

	}

	return true;
}

void Weapone::LateUpdate()
{
}

void Weapone::Render()
{
}


void Weapone::Realease()
{
}


