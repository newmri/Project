#include "stdafx.h"
#include "Obj.h"

void CObj::LateInit()
{
	if (!m_bIsInit) this->LateInit();

	m_bIsInit = true;
	m_bIsFalling = false;
}

void CObj::RenderCollsionBox()
{
	if (SCENEMANAGER->ShowCollisionBox()) {
		Rectangle(RENDERMANAGER->GetMemDC(), m_rect.left, m_rect.top + SCROLLMANAGER->GetScrollY(), m_rect.right, m_rect.bottom + SCROLLMANAGER->GetScrollY());
	}
}

void CObj::UpdateRect()
{
	m_rect.left = m_info.fX - m_info.nW / 2;
	m_rect.right = m_info.fX + m_info.nW / 2;
	m_rect.top = (m_info.fY - m_info.nH / 2);
	m_rect.bottom = (m_info.fY + m_info.nH / 2);

}

void CObj::SetRect()
{
	int w = (m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim]);
	m_rect.left = m_info.fX + 10;
	m_rect.right = m_rect.left + w - 20;
	m_rect.top = (m_info.fY + 5);
	m_rect.bottom = (m_info.fY + m_tAnimationInfo[m_eCurrAnim].nImageH);

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
		if (ANIM_UP == i || ANIM_DOWN == i) continue;
		if (ANIM_LEFT_IDLE == i || ANIM_LEFT == i || ANIM_LEFT_JUMP == i) m_tAnimationInfo[i].nCnt = PLAYER_ANIMATION_NUM[i];
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



void CObj::UpdateLine()
{
	m_tLine[SegmentPos::TOP].iFirstPtX = m_rect.left;
	m_tLine[SegmentPos::TOP].iFirstPtY = m_rect.top;
	m_tLine[SegmentPos::TOP].iLastPtX = m_rect.right;
	m_tLine[SegmentPos::TOP].iLastPtY = m_rect.top;

	m_tLine[SegmentPos::BOTTOM].iFirstPtX = m_rect.left;
	m_tLine[SegmentPos::BOTTOM].iFirstPtY = m_rect.bottom;
	m_tLine[SegmentPos::BOTTOM].iLastPtX = m_rect.right;
	m_tLine[SegmentPos::BOTTOM].iLastPtY = m_rect.bottom;

	m_tLine[SegmentPos::LEFT].iFirstPtX = m_rect.left;
	m_tLine[SegmentPos::LEFT].iFirstPtY = m_rect.top;
	m_tLine[SegmentPos::LEFT].iLastPtX = m_rect.left;
	m_tLine[SegmentPos::LEFT].iLastPtY = m_rect.bottom;

	m_tLine[SegmentPos::RIGHT].iFirstPtX = m_rect.right;
	m_tLine[SegmentPos::RIGHT].iFirstPtY = m_rect.top;
	m_tLine[SegmentPos::RIGHT].iLastPtX = m_rect.right;
	m_tLine[SegmentPos::RIGHT].iLastPtY = m_rect.bottom;
}


