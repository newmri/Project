#include "stdafx.h"
#include "Player.h"

void CPlayer::Init()
{

	m_stat.nDamage = 0;
	m_stat.nMaxHP = 1;
	m_stat.nHP = 1;

	m_info.fX = 200.f;
	m_info.fY = WINDOWS_WIDTH - 50;

	m_info.fSpeed = 3.f;
	m_info.nJumpPower = 12;
	m_info.fAcc = 0.f;
	m_info.fFallAcc = 0.f;

	m_eCurrAnim = ANIM_RIGHT_IDLE;
	IsWallJumpOn = false;
	for (int i = 0; i < ANIM_END; ++i) {
		if (i == ANIM_UP || i == ANIM_DOWN) continue;

		m_tAnimationInfo[i].dwAnimationTime = GetTickCount();

		if (i == ANIM_LEFT_IDLE || i == ANIM_LEFT || i == ANIM_LEFT_JUMP) m_tAnimationInfo[i].nCnt = PLAYER_ANIMATION_NUM[i];
		else m_tAnimationInfo[i].nCnt = 0;

		m_tAnimationInfo[i].nImageW = BITMAPMANAGER->GetImage()[PLAYER_IMG_STR[i]]->GetWidth();
		m_tAnimationInfo[i].nImageH = BITMAPMANAGER->GetImage()[PLAYER_IMG_STR[i]]->GetHeight();

	}

	bIsCheatOn = false;
}

void CPlayer::LateInit()
{


}

int CPlayer::Update()
{
	CObj::LateInit();

	Move();
	Jump();

	if (m_bIsDead);

	CObj::UpdateLine();

	return m_bIsDead;
}

void CPlayer::LateUpdate()
{
	SetRect();
	OffSet();

	if (!bIsCheatOn) {
		POS pos;
		pos.fX = m_info.fX;
		pos.fY = m_info.fY;
		COLLISION collision;

		bool bColl = CCollisionManager::CollisionLine(OBJMANAGER->GetObLst()[OBJTYPE::OBSTACLE], OBJMANAGER->GetObLst()[OBJTYPE::PLAYER], pos, collision);

		if (LEFT_COLLISION == collision || RIGHT_COLLISION == collision) {

			IsWallJumpOn = true;
			m_info.fX = pos.fX;

		}
		else IsWallJumpOn = false;

		//else IsWallJumpOn = false;

		if (!bColl && !IsJumpOn()) m_bIsFalling = true;

		if (IsWallJumpOn && IsJumpOn()) {
			m_bIsFalling = false;
			m_info.fFallAcc = 0.f;
			m_info.fY = pos.fY;
		}

		if (m_bIsFalling) {
			m_info.fY += GRAVITY * m_info.fFallAcc * m_info.fFallAcc * 0.5f;
			if (abs(GRAVITY * m_info.fFallAcc * m_info.fFallAcc* 0.5) >= 25)
				m_info.fFallAcc = m_info.fFallAcc - 0.1f;
			else
				m_info.fFallAcc += 0.1f;
		}
		else {

			if (!IsJumpOn() && !IsWallJumpOn) {
				m_bIsFalling = false;
				m_info.fFallAcc = 0.f;
				m_info.fY = pos.fY;
			}
		}

		bool bJump = false;


		if (IsJumpOn()) {
			bJump = true;

			// y 낙하에 대한 포물선 공식
			// y = v * sin@ * t - g * t^2 * 0.5f;
			float fJumpAcc = m_info.nJumpPower * m_info.fAcc - GRAVITY * m_info.fAcc * m_info.fAcc * 0.5f;

			m_info.fY -= fJumpAcc;
			if (abs(m_info.nJumpPower * m_info.fAcc - GRAVITY * m_info.fAcc * m_info.fAcc* 0.5) >= 25)
				m_info.fAcc = m_info.fAcc - 0.1f;
			else
				m_info.fAcc += 0.1f;

			POS move;
			move.fX = m_info.fX;
			move.fY = m_info.fY;

			COLLISION collision = NO_COLLISION;
			CCollisionManager::CollisionLine(OBJMANAGER->GetObLst()[OBJTYPE::OBSTACLE], OBJMANAGER->GetObLst()[OBJTYPE::PLAYER], move, collision);

			if (BOTTOM_COLLISION == collision) m_info.fAcc = 2.6f;

			if (ANIM_LEFT_JUMP == m_eCurrAnim) m_info.fX -= m_info.fAcc * 2;
			else m_info.fX += m_info.fAcc * 2;


			if (bColl && m_info.fY > pos.fY) {
				if (ANIM_RIGHT_JUMP == m_eCurrAnim) EnableAnimation(ANIM_RIGHT_IDLE);
				else EnableAnimation(ANIM_LEFT_IDLE);

				m_info.fAcc = 0.f;
				m_info.fY = pos.fY;
			}

		}

		if (m_info.fX <= -10)
			m_info.fX = -10;
		if (m_info.fX >= WINDOWS_WIDTH - 70)
			m_info.fX = WINDOWS_WIDTH - 70;
	}
}

void CPlayer::Render()
{
	DoAnimation();

	if (m_tAnimationInfo[m_eCurrAnim].nCnt >= PLAYER_ANIMATION_NUM[m_eCurrAnim]) 
		m_tAnimationInfo[m_eCurrAnim].nCnt = 0;

	if (m_tAnimationInfo[m_eCurrAnim].nCnt == -1) m_tAnimationInfo[m_eCurrAnim].nCnt = 0;
	
	BITMAPMANAGER->GetImage()[PLAYER_IMG_STR[m_eCurrAnim]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_info.fX),
		static_cast<int>(m_info.fY + SCROLLMANAGER->GetScrollY()),
		m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim],
		m_tAnimationInfo[m_eCurrAnim].nImageH,
		(m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim]) * m_tAnimationInfo[m_eCurrAnim].nCnt,
		0,
		m_tAnimationInfo[m_eCurrAnim].nImageW / PLAYER_ANIMATION_NUM[m_eCurrAnim],
		m_tAnimationInfo[m_eCurrAnim].nImageH, RGB(255, 255, 255));

}

void CPlayer::Release()
{

}

void CPlayer::Fall()
{

}

void CPlayer::Move()
{


	if (!IsJumpOn()) {
		if (KEYMANAGER->KeyPressing(VK_LEFT)) {
			if (ANIM_LEFT != m_eCurrAnim) EnableAnimation(ANIM_LEFT);
			m_info.fX -= m_info.fSpeed;

		}
		else if (KEYMANAGER->KeyPressing(VK_RIGHT)) {
			if (ANIM_RIGHT != m_eCurrAnim) EnableAnimation(ANIM_RIGHT);
			m_info.fX += m_info.fSpeed;

		}
		else if (KEYMANAGER->KeyPressing(VK_UP)) {
			SCROLLMANAGER->SetScrollY(m_info.fSpeed * 10);
			m_info.fY -= m_info.fSpeed * 10;

		}
		else if (KEYMANAGER->KeyPressing(VK_DOWN)) {
			SCROLLMANAGER->SetScrollY(-m_info.fSpeed * 10);
			m_info.fY += m_info.fSpeed * 10;

		}

		else if (KEYMANAGER->KeyDown(VK_F3)) {
			bIsCheatOn = !bIsCheatOn;
		}
		
		// Idle
		else {
			if (ANIM_RIGHT == m_eCurrAnim) EnableAnimation(ANIM_RIGHT_IDLE);
			else if (ANIM_LEFT == m_eCurrAnim) EnableAnimation(ANIM_LEFT_IDLE);

		}
	}
}

void CPlayer::Jump()
{
	POS pos;
	COLLISION collision;
	pos.fX = m_info.fX;
	pos.fY = m_info.fY;

	if (IsWallJumpOn && KEYMANAGER->KeyPressing(VK_SPACE)) {
		if (CCollisionManager::CollisionLine(OBJMANAGER->GetObLst()[OBJTYPE::OBSTACLE], OBJMANAGER->GetObLst()[OBJTYPE::PLAYER], pos, collision)) {
			
			if (ANIM_LEFT == m_eCurrAnim) EnableAnimation(ANIM_LEFT_JUMP);
			else if (ANIM_RIGHT == m_eCurrAnim) EnableAnimation(ANIM_RIGHT_JUMP);
			else if (ANIM_LEFT_IDLE == m_eCurrAnim) EnableAnimation(ANIM_LEFT_JUMP);
			else if (ANIM_RIGHT_IDLE == m_eCurrAnim) EnableAnimation(ANIM_RIGHT_JUMP);
			return;
		}

	}
	if (KEYMANAGER->KeyDown(VK_SPACE)) {
		if (CCollisionManager::CollisionLine(OBJMANAGER->GetObLst()[OBJTYPE::OBSTACLE], OBJMANAGER->GetObLst()[OBJTYPE::PLAYER], pos, collision)) {
			if (ANIM_LEFT == m_eCurrAnim) EnableAnimation(ANIM_LEFT_JUMP);
			else if (ANIM_RIGHT == m_eCurrAnim) EnableAnimation(ANIM_RIGHT_JUMP);

		}
		return;
	}
}

void CPlayer::OffSet()
{
	int nOffset = WINDOWS_HEIGHT / 2;

	float fScrollY = SCROLLMANAGER->GetScrollY();

	float fFallAcc;
	if(!IsJumpOn()) fFallAcc = GRAVITY * m_info.fFallAcc * m_info.fFallAcc * 0.5f;
	else fFallAcc = abs(m_info.nJumpPower * m_info.fAcc - GRAVITY * m_info.fAcc * m_info.fAcc * 0.5f);

	 //화면좌표 대 화면좌표로 비교해야함!

	if (nOffset + 100 < int(m_info.fY + fScrollY)) {
		if (!m_bIsFalling) SCROLLMANAGER->SetScrollY(-fFallAcc);
	}


	if (nOffset - 100 > int(m_info.fY + fScrollY))
		SCROLLMANAGER->SetScrollY(m_info.fSpeed);

}


void CPlayer::SetPlayerRect()
{
	m_rect.left = static_cast<LONG>(m_info.fX + 12);
	m_rect.top = static_cast<LONG>(m_info.fY);
	m_rect.right = static_cast<LONG>(m_info.fX + m_info.nW / 8);
	m_rect.bottom = static_cast<LONG>(m_info.fY + m_info.nH);
}

bool CPlayer::IsJumpOn()
{
	return (ANIM_LEFT_JUMP == m_eCurrAnim || ANIM_RIGHT_JUMP == m_eCurrAnim);
}

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}


