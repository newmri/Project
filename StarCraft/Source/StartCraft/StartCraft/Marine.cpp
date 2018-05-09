#include "stdafx.h"
#include "Marine.h"
#include "Tile.h"

void CMarine::Init()
{
	SOUNDMANAGER->PlayerEffectSound(MARINE_BORN);

	CUnit::Init();

	m_tStat.nAttackRange = TILE_SIZE * 4;

	m_fMoveAnimDivide = 2.98f;
	m_fAttackAnimDivide = 8.15f;
	m_tStat.nDamage = 10;
	m_nAttackTime = 150;

	m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / m_fMoveAnimDivide);
}

void CMarine::LateInit()
{
	CUnit::LateInit();


}

int CMarine::Update()
{
	CObj::LateInit();

	Move();
	Attack();
	
	return CUnit::Die();

}

void CMarine::LateUpdate()
{
}

void CMarine::Render()
{
	CUnit::Render();
}

void CMarine::Release()
{
}

bool CMarine::CheckCommand(POINT tMousePos)
{
	int nCnt = 0;

	for (auto& d : m_commandList) {

		if (tMousePos.x >= d->tImage.tPos.x && tMousePos.x <= d->tClickArea.x &&
			tMousePos.y >= d->tImage.tPos.y && tMousePos.y <= d->tClickArea.y) {
	
			if (!strcmp(d->tImage.tInfo.szName, "MarineCommand04")) {
				MOUSEMANAGER->ChangeCursor(TARGY);
			}
			nCnt++;

			return true;

		}

	}

	return false;
}

void CMarine::RenderUI()
{
	CUnit::RenderUI();
}

void CMarine::Move()
{
	CUnit::Move();
}

void CMarine::Attack()
{
	CUnit::Attack();
}

