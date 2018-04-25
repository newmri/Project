#include "stdafx.h"
#include "Obj.h"

void CObj::LateInit()
{
	if (!m_bIsInit) this->LateInit();

	m_bIsInit = true;
}

void CObj::RenderCollsionBox()
{
	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CObj::SetRect()
{
	int w = (m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim]);
	m_tRect.left = m_tInfo.fX + 10;
	m_tRect.right = m_tRect.left + w - 20;
	m_tRect.top = m_tInfo.fY + 5;
	m_tRect.bottom = m_tInfo.fY + m_tAnimationInfo[m_eCurrAnim].nImageH;

}

void CObj::DoAnimation()
{
	if (m_tAnimationInfo[m_eCurrAnim].dwAnimationTime + (1000 / PLAYER_ANIMATION_NUM[m_eCurrAnim]) < GetTickCount()) {
		if (ANIM_LEFT_IDLE == m_eCurrAnim || ANIM_LEFT == m_eCurrAnim || ANIM_LEFT_JUMP == m_eCurrAnim) {
			--m_tAnimationInfo[m_eCurrAnim].nCnt;
			if (0 > m_tAnimationInfo[m_eCurrAnim].nCnt) m_tAnimationInfo[m_eCurrAnim].nCnt = PLAYER_ANIMATION_NUM[m_eCurrAnim] - 1;
		}
		else {
			++m_tAnimationInfo[m_eCurrAnim].nCnt;
			if (m_tAnimationInfo[m_eCurrAnim].nCnt >= PLAYER_ANIMATION_NUM[m_eCurrAnim]) m_tAnimationInfo[m_eCurrAnim].nCnt = 0;
		}

		m_tAnimationInfo[m_eCurrAnim].dwAnimationTime = GetTickCount();
	}
}

void CObj::EnableAnimation(ANIMATION eAnim)
{
	ReSetAnimation();
	m_eCurrAnim = eAnim;
}

void CObj::ReSetAnimation()
{
	for (int i = 0; i < ANIM_END; ++i) {
		if (i == ANIM_UP || i == ANIM_DOWN) continue;
		if (ANIM_LEFT_IDLE == i || i == ANIM_LEFT || i == ANIM_LEFT_JUMP) m_tAnimationInfo[i].nCnt = PLAYER_ANIMATION_NUM[i];
		else m_tAnimationInfo[i].nCnt = -1;
	}
}

CObj::CObj()
{
	m_bIsDead = false;
	m_bIsInit = false;
}

CObj::~CObj()
{
}


