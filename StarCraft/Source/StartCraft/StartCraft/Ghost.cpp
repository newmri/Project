#include "stdafx.h"
#include "Ghost.h"

void CGhost::Init()
{
	SOUNDMANAGER->PlayerEffectSound(GHOST_BORN);

	CUnit::Init();

	m_tStat.nAttackRange = TILE_SIZE * 5;

	m_fMoveAnimDivide = 2.49f;
	m_fAttackAnimDivide = 7.44f;

	m_bNuclearOn = false;
	m_dwNuclearLaunchTime = 0;
	m_nNuclearIdx = 0;

	m_fNuclearDmg = 500.f;
	m_fNuclearArea = 120.f;

	m_tStat.nDamage = 20;
	m_nAttackTime = 150;
}

void CGhost::LateInit()
{
	CUnit::LateInit();

	// Effect
	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(GHOST_SKILL);

	for (int i = 0; i < p[0].nImageNum; ++i) {
		STATIC_UI_IMAGE_INFO* pTemp = new STATIC_UI_IMAGE_INFO;
		memcpy(&pTemp->tInfo, &p[i], sizeof(IMAGE_INFO));
		pTemp->tColor = RGB(0, 0, 0);
		pTemp->tDrawSize.x = pTemp->tInfo.nImageW;
		pTemp->tDrawSize.y = pTemp->tInfo.nImageH;

		m_SkillList.push_back(pTemp);
	}


}

int CGhost::Update()
{
	CObj::LateInit();
	Move();
	Attack();
	UpdateNuclear();
	

	return CUnit::Die();
}

void CGhost::LateUpdate()
{
}

void CGhost::Render()
{
	CUnit::Render();

	HDC hDC = RENDERMANAGER->GetMemDC();
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	if (m_bNuclearOn) {
		if (3 > m_nNuclearIdx) {
			BITMAPMANAGER->GetImage()[m_SkillList[m_nNuclearIdx]->tInfo.szName]->TransparentBlt(hDC,
				m_tNuclearPos.x + m_SkillList[m_nNuclearIdx]->tInfo.nImageW + fScrollX,
				m_tNuclearPos.y + SCROLLMANAGER->GetScrollY(),
				m_SkillList[m_nNuclearIdx]->tDrawSize.x,
				m_SkillList[m_nNuclearIdx]->tDrawSize.y,
				0,
				0,
				m_SkillList[m_nNuclearIdx]->tInfo.nImageW,
				m_SkillList[m_nNuclearIdx]->tInfo.nImageH, m_SkillList[m_nNuclearIdx]->tColor);

			// Laser
			BITMAPMANAGER->GetImage()[m_SkillList[2]->tInfo.szName]->TransparentBlt(hDC,
				(m_tNuclearTargetPos.x - m_SkillList[2]->tInfo.nImageW / 2) + fScrollX,
				(m_tNuclearTargetPos.y - m_SkillList[2]->tInfo.nImageH / 2) + fScrollY,
				m_SkillList[2]->tDrawSize.x,
				m_SkillList[2]->tDrawSize.y,
				0,
				0,
				m_SkillList[2]->tInfo.nImageW,
				m_SkillList[2]->tInfo.nImageH, m_SkillList[m_nNuclearIdx]->tColor);
		}

		else {
			BITMAPMANAGER->GetImage()[m_SkillList[m_nNuclearIdx]->tInfo.szName]->TransparentBlt(hDC,
				(m_tNuclearPos.x - m_SkillList[m_nNuclearIdx]->tInfo.nImageW / 3) + fScrollX,
				(m_tNuclearPos.y - m_SkillList[m_nNuclearIdx]->tInfo.nImageH / 2) + fScrollY,
				m_SkillList[m_nNuclearIdx]->tDrawSize.x,
				m_SkillList[m_nNuclearIdx]->tDrawSize.y,
				0,
				0,
				m_SkillList[m_nNuclearIdx]->tInfo.nImageW,
				m_SkillList[m_nNuclearIdx]->tInfo.nImageH, m_SkillList[m_nNuclearIdx]->tColor);

		}

	}

}

void CGhost::Release()
{
}

void CGhost::UpdateNuclear()
{
	if (m_bNuclearOn && m_dwNuclearLaunchTime + 100 < GetTickCount()) {
		m_dwNuclearLaunchTime = GetTickCount();
		if (0 == m_nNuclearIdx && m_tNuclearPos.y  > -m_SkillList[0]->tInfo.nImageH) m_tNuclearPos.y -= 5;
		else {
			if (m_tNuclearPos.x != (m_tNuclearTargetPos.x - m_SkillList[0]->tInfo.nImageW) - 10) {
				m_nNuclearIdx = 1;
				m_tNuclearPos.x = (m_tNuclearTargetPos.x - m_SkillList[0]->tInfo.nImageW) - 10;
				m_tNuclearPos.y = 0;
			}
			else {
				if (m_tNuclearPos.y < m_tNuclearTargetPos.y - m_SkillList[0]->tInfo.nImageH) m_tNuclearPos.y += 5;
				else {
					if (3 > m_nNuclearIdx) m_nNuclearIdx = 3;
				}

			}

		}

		if (3 <= m_nNuclearIdx) {
			SOUNDMANAGER->PlayerEffectSound(GHOST_NUCLEAR_EXP);

			if (m_nNuclearIdx < m_SkillList[0]->tInfo.nImageNum - 1) m_nNuclearIdx++;
			else {

				m_bNuclearOn = false;
				m_nNuclearIdx = 0;
				OBJLIST* p = OBJMANAGER->GetObj();
				for (int i = 0; i < CURSOR; ++i) {
					for (auto& d : p[i]) {
						RECT rc = d->GetSelectRectWithScroll();
						FLOATPOINT pos1(m_tNuclearPos.x, m_tNuclearPos.y);
						FLOATPOINT pos2(rc.left, rc.top);
						float dist = MATHMANAGER->CalcDistance(pos2, pos1);

						if (m_fNuclearArea >= dist) {
							int nHP = d->GetStat().nMaxHP;
							if (750 <= nHP) d->SetDamage(nHP / 2);

							else d->SetDamage(m_fNuclearDmg);
						}

					}

				}
			}
		}
	}
}

void CGhost::SetNuclear(POINT tMousePos)
{
	SOUNDMANAGER->PlayerEffectSound(GHOST_NUCLEAR_LASER);
	 m_bNuclearOn = true; 
	 m_tNuclearPos.x = m_tRect.left;
	 m_tNuclearPos.y = m_tRect.top; 

	 m_tNuclearTargetPos.x = tMousePos.x - SCROLLMANAGER->GetScrollX();
	 m_tNuclearTargetPos.y = tMousePos.y - SCROLLMANAGER->GetScrollY();


}

bool CGhost::CheckCommand(POINT tMousePos)
{
	if (!m_bNuclearOn) {
		int nCnt = 0;

		for (auto& d : m_commandList) {

			if (tMousePos.x >= d->tImage.tPos.x && tMousePos.x <= d->tClickArea.x &&
				tMousePos.y >= d->tImage.tPos.y && tMousePos.y <= d->tClickArea.y) {

				if (!strcmp(d->tImage.tInfo.szName, "GhostCommand14")) {
					MOUSEMANAGER->ChangeCursor(TARGY, true);
				}
				nCnt++;

				return false;

			}

		}
	}
	return false;
}

void CGhost::RenderUI()
{
	CUnit::RenderUI();
}

void CGhost::Move()
{
	if (m_bNuclearOn) m_route.clear();
	CUnit::Move();

}

void CGhost::Attack()
{
	CUnit::Attack();

}
