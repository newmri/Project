#include "stdafx.h"
#include "Player.h"

void CPlayer::Init()
{

	m_tStat.nDamage = 0;
	m_tStat.nMaxHP = 1;
	m_tStat.nHP = 1;

	m_tInfo.fX = 100.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fSpeed = 3.f;
	m_tInfo.nJumpPower = 10;
	m_tInfo.fAcc = 0.f;
	m_tInfo.fJumpUpAcc = 0.f;
	m_tInfo.fJumpDownAcc = 0.f;

	//m_eCurrAnim = ANIM_RIGHT_IDLE;

	//for (int i = 0; i < ANIM_END; ++i) {
	//	if (i == ANIM_UP || i == ANIM_DOWN) continue;

	//	m_tAnimationInfo[i].dwAnimationTime = GetTickCount();

	//	if (i == ANIM_LEFT_IDLE || i == ANIM_LEFT || i == ANIM_LEFT_JUMP) m_tAnimationInfo[i].nCnt = PLAYER_ANIMATION_NUM[i];
	//	else m_tAnimationInfo[i].nCnt = 0;

	//	m_tAnimationInfo[i].nImageW = BITMAPMANAGER->GetImage()[PLAYER_IMG_STR[i]]->GetWidth();
	//	m_tAnimationInfo[i].nImageH = BITMAPMANAGER->GetImage()[PLAYER_IMG_STR[i]]->GetHeight();

	//}
}

void CPlayer::LateInit()
{


}

int CPlayer::Update()
{
	CObj::LateInit();

	Move();
	Jump();



	return m_bIsDead;
}

void CPlayer::LateUpdate()
{
	//SetRect();

}

void CPlayer::Render()
{
	DoAnimation();

	//BITMAPMANAGER->GetImage()[PLAYER_IMG_STR[m_eCurrAnim]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
	//	static_cast<int>(m_tInfo.fX),
	//	static_cast<int>(m_tInfo.fY),
	//	m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim],
	//	m_tAnimationInfo[m_eCurrAnim].nImageH,
	//	(m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim]) * m_tAnimationInfo[m_eCurrAnim].nCnt,
	//	0,
	//	m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim],
	//	m_tAnimationInfo[m_eCurrAnim].nImageH, RGB(255, 255, 255));
	
}

void CPlayer::Release()
{

}


void CPlayer::SetPlayerRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.fX + 12);
	m_tRect.top = static_cast<LONG>(m_tInfo.fY);
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + m_tInfo.nW / 8);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + m_tInfo.nH);
}

void CPlayer::Move()
{

	//if (KEYMANAGER->KeyPressing(VK_LEFT)) {
	//	if (ANIM_LEFT != m_eCurrAnim) EnableAnimation(ANIM_LEFT);
	//	m_tInfo.fX -= m_tInfo.fSpeed;

	//}
	//else if (KEYMANAGER->KeyPressing(VK_RIGHT)) {
	//	if (ANIM_RIGHT != m_eCurrAnim) EnableAnimation(ANIM_RIGHT);
	//	m_tInfo.fX += m_tInfo.fSpeed;

	//}
	//else if (KEYMANAGER->KeyPressing(VK_UP)) {
	//	m_tInfo.fY -= m_tInfo.fSpeed;
	//}
	//else if (KEYMANAGER->KeyPressing(VK_DOWN)) {
	//	m_tInfo.fY += m_tInfo.fSpeed;

	//}
	//// Idle
	//else {
	//	if (ANIM_RIGHT == m_eCurrAnim) EnableAnimation(ANIM_RIGHT_IDLE);
	//	else if (ANIM_LEFT == m_eCurrAnim) EnableAnimation(ANIM_LEFT_IDLE);

	//}
	
}

void CPlayer::Jump()
{
}

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}


