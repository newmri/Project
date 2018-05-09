#include "stdafx.h"
#include "Ghost.h"

void CGhost::Init()
{
	CUnit::Init();
	m_tAnimationInfo[m_eCurrId].nCnt = 144;
	nAnimationCnt = -1;
	m_dwAttackTime = 0;
	m_nEffectIdx = 0;
	m_tStat.nAttackRange = TILE_SIZE * 5;

	m_fMoveAnimDivide = 2.49f;
	m_fAttackAnimDivide = 7.44f;
}

void CGhost::LateInit()
{

	CUnit::LateInit();

}

int CGhost::Update()
{
	CObj::LateInit();

	Move();
	Attack();

	return CUnit::Die();
}

void CGhost::LateUpdate()
{
}

void CGhost::Render()
{
	CUnit::Render();

}

void CGhost::Release()
{
}

bool CGhost::CheckCommand(POINT tMousePos)
{
	return false;
}

void CGhost::RenderUI()
{
	CUnit::RenderUI();
}

void CGhost::Move()
{
	CUnit::Move();

}

void CGhost::Attack()
{
	CUnit::Attack();

}
