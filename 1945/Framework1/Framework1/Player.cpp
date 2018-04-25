#include "stdafx.h"
#include "Player.h"
#include"Weapone.h"
#include"Missile.h"
#include"StrongMissile.h"
#include"Skill.h"
#include"Bomb.h"
#include "Item.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_info.m_x = W_MAX / 2;
	m_info.m_y = H_MAX * 9 / 10;
	m_info.m_h = C_H;
	m_info.m_w = C_W;
	m_info.m_degree = 90.f;
	m_info.m_speed = 3;


	m_stat.m_Atk = 0;
	m_stat.m_cHp = 1;

	my_gun = 1;

	missle_speed = GetTickCount();

	m_moveHCnt = PLAYER_STILL_IMG;
	m_moveVCnt = 0;


	for(int i = 0; i< MOVE_END; ++i) m_IsMoving[i] = false;


}

void Player::LateInit()
{
	m_info.m_w = BITMAPMANAGER->GetImage()["PLAYERLR"]->GetWidth();
	m_info.m_h = BITMAPMANAGER->GetImage()["PLAYERLR"]->GetHeight();
	m_tbImageW = BITMAPMANAGER->GetImage()["PLAYERTB"]->GetWidth();
	m_tbImageH = BITMAPMANAGER->GetImage()["PLAYERTB"]->GetHeight();

	m_shiledW = BITMAPMANAGER->GetImage()["SHIELD"]->GetWidth();
	m_shiledH = BITMAPMANAGER->GetImage()["SHIELD"]->GetHeight();

	m_animationTime = GetTickCount();
}

int Player::Update()
{
	Obj::LateInit();

	float ex_x = m_info.m_x;
	float ex_y = m_info.m_y;

	//////이동 구현////////////////////////////////////////////

	// 애니메이션을 초기 상태로
	if (!(GetAsyncKeyState(VK_LEFT) & 0x8000) && m_IsMoving[MOVE_LEFT]) {
		m_animationTime = GetTickCount();
		m_IsMoving[MOVE_LEFT] = false;
		m_moveHCnt = PLAYER_STILL_IMG;
	}

	else if (!(GetAsyncKeyState(VK_RIGHT) & 0x8000) && m_IsMoving[MOVE_RIGHT]) {
		m_animationTime = GetTickCount();
		m_IsMoving[MOVE_RIGHT] = false;
		m_moveHCnt = PLAYER_STILL_IMG;
	}

	if (!(GetAsyncKeyState(VK_UP) & 0x8000) && m_IsMoving[MOVE_UP]) {
		m_animationTime = GetTickCount();
		m_IsMoving[MOVE_UP] = false;
		m_moveHCnt = PLAYER_STILL_IMG;
		m_moveVCnt = 0;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{

		for (int i = 0; i< MOVE_END; ++i) m_IsMoving[i] = false;
		m_IsMoving[MOVE_LEFT] = true;

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			// 직각 삼각형의 비를 이용한 대각선 이동처리 1 : 1 : 루트2
			m_info.m_x -= m_info.m_speed / sqrtf(2.f);
			m_info.m_y -= m_info.m_speed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_info.m_x -= m_info.m_speed / sqrtf(2.f);
			m_info.m_y += m_info.m_speed / sqrtf(2.f);
		}
		else m_info.m_x -= m_info.m_speed;
	
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		for (int i = 0; i< MOVE_END; ++i) m_IsMoving[i] = false;
		m_IsMoving[MOVE_RIGHT] = true;

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			// 직각 삼각형의 비를 이용한 대각선 이동처리 1 : 1 : 루트2
			m_info.m_x += m_info.m_speed / sqrtf(2.f);
			m_info.m_y -= m_info.m_speed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_info.m_x += m_info.m_speed / sqrtf(2.f);
			m_info.m_y += m_info.m_speed / sqrtf(2.f);
		}
		else
			m_info.m_x += m_info.m_speed;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		for (int i = 0; i< MOVE_END; ++i) m_IsMoving[i] = false;
		m_IsMoving[MOVE_UP] = true;

		m_moveHCnt = -1;

		m_info.m_y -= m_info.m_speed;

	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		for (int i = 0; i< MOVE_END; ++i) m_IsMoving[i] = false;
		m_IsMoving[MOVE_DOWN] = true;

		m_info.m_y += m_info.m_speed; 
	}
	///일반 총알 발사	//////////////////////////////////////////
	if (GetAsyncKeyState('A') & 0x8000)
	{
		//SOUNDMANAGER->PlayerEffectSound(NORMAL_BULLET_EFSD);
		if (m_key_up) {
			skill_time = GetTickCount();
			m_weapone = ObjMaker<Weapone>::Create(m_info.m_x, m_info.m_y);
			dynamic_cast<Weapone*>(m_weapone)->SetBULLETList(m_nomallist);
			dynamic_cast<Weapone*>(m_weapone)->SetPlayerLevel(my_gun);

			m_weaponelist->push_back(m_weapone);
			m_key_up = false;
		}

	}
	/////////////////////////스킬 발사/////////////////////////////////
	if (!GetAsyncKeyState('A'))
	{

		if (m_key_up == false && skill_time + 3000 < GetTickCount())
		{
			SOUNDMANAGER->PlayerEffectSound(SKILL_EFSD);
			m_skill = ObjMaker<Skill>::Create(m_info.m_x, m_info.m_y);
			dynamic_cast<Skill*>(m_skill)->SetSKILLBULLETList(m_skillbulletlist);
			dynamic_cast<Skill*>(m_skill)->SetPlayerLevel(my_gun);

			m_skilllist->push_back(m_skill);
			skill_time = GetTickCount();

		}
		m_key_up = true;

	}
	
	


	//////////////////////미사일 발사/////////////////////////////
	if (missle_speed + 5000 < GetTickCount()) {

		SOUNDMANAGER->PlayerEffectSound(MISSILE_EFSD);
		if (my_gun == 1) {
			m_missilelist->push_back(CreateMISSILE(m_info.m_x - FIRST_W, m_info.m_y + FIRST_H));
			m_missilelist->push_back(CreateMISSILE(m_info.m_x + FIRST_W, m_info.m_y + FIRST_H));
		}
		else if (my_gun == 2) {

			m_missilelist->push_back(CreateSTRONG(m_info.m_x - FIRST_W, m_info.m_y + FIRST_H));
			m_missilelist->push_back(CreateSTRONG(m_info.m_x + FIRST_W, m_info.m_y + FIRST_H));

		}
		else if (my_gun == 3) {
			m_missilelist->push_back(CreateMISSILE(m_info.m_x - SECOND_W, m_info.m_y + SECOND_H));
			m_missilelist->push_back(CreateMISSILE(m_info.m_x + SECOND_W, m_info.m_y + SECOND_H));

			m_missilelist->push_back(CreateSTRONG(m_info.m_x - FIRST_W, m_info.m_y + FIRST_H));
			m_missilelist->push_back(CreateSTRONG(m_info.m_x + FIRST_W, m_info.m_y + FIRST_H));

		}
		else if (my_gun == 4) {

			m_missilelist->push_back(CreateSTRONG(m_info.m_x - SECOND_W, m_info.m_y + SECOND_H));
			m_missilelist->push_back(CreateSTRONG(m_info.m_x + SECOND_W, m_info.m_y + SECOND_H));

			m_missilelist->push_back(CreateSTRONG(m_info.m_x - FIRST_W, m_info.m_y + FIRST_H));
			m_missilelist->push_back(CreateSTRONG(m_info.m_x + FIRST_W, m_info.m_y + FIRST_H));
		}
		else if (my_gun == 5) {

			m_missilelist->push_back(CreateMISSILE(m_info.m_x - THIRD_W, m_info.m_y + THIRD_H));
			m_missilelist->push_back(CreateMISSILE(m_info.m_x + THIRD_W, m_info.m_y + THIRD_H));

			m_missilelist->push_back(CreateSTRONG(m_info.m_x - SECOND_W, m_info.m_y + SECOND_H));
			m_missilelist->push_back(CreateSTRONG(m_info.m_x + SECOND_W, m_info.m_y + SECOND_H));

			m_missilelist->push_back(CreateSTRONG(m_info.m_x - FIRST_W, m_info.m_y + FIRST_H));
			m_missilelist->push_back(CreateSTRONG(m_info.m_x + FIRST_W, m_info.m_y + FIRST_H));

		}
		missle_speed = GetTickCount();
	}
	////폭탄////////////////////////////////////////////////////////////
	
	////폭탄////////////////////////////////////////////////////////////
	
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	//{
	//	//if (0 < my_bomb)
	//	//{
	//		if (m_Space_up) {
	//			bomb_time = GetTickCount();
	//			m_bomb = ObjMaker<Bomb>::Create(m_info.m_x, m_info.m_y);
	//			m_bomblist->push_back(m_bomb);

	//			m_Space_up = false;
	//		}
	//		my_bomb--;
	//	//}
	//}

	//if (bomb_time + 50 < GetTickCount())
	//{
	//	bomb_time = GetTickCount();
	//	m_Space_up = true;
	//}


	//외부 충돌
	if (NoOut()) {
		m_info.m_x = ex_x;
		m_info.m_y = ex_y;
	}
	if (is_dead) {
		SOUNDMANAGER->PlayerEffectSound(PLAYER_DIE_EFSD);
		SCENEMANAGER->RenderDie();
	}
	return is_dead;
}

void Player::LateUpdate()
{
	SetPlayerRect();

	// Left Animation
	if (m_IsMoving[MOVE_LEFT] && m_animationTime + (1000 / PLAYER_H_ANIMATION_NUM) < GetTickCount() && m_moveHCnt > PLAYER_LEFT_IMG_END) {
		m_animationTime = GetTickCount();
		m_moveHCnt -= 1;
	}
	// Right Animation
	else if (m_IsMoving[MOVE_RIGHT] && m_animationTime + (1000 / PLAYER_H_ANIMATION_NUM) < GetTickCount() && m_moveHCnt < PLAYER_RIGHT_IMG_END) {
		m_animationTime = GetTickCount();
		m_moveHCnt += 1;
	}

	// Up Animation
	if (m_IsMoving[MOVE_UP] && m_animationTime + (1000 / PLAYER_V_ANIMATION_NUM) < GetTickCount()  && m_moveVCnt < PLAYER_UP_IMG_END) {

		m_animationTime = GetTickCount();
		m_moveVCnt += 1;
	}
}

void Player::Render()
{

	{if (my_gun == 1)
		Ellipse(RENDERMANAGER->GetMemDC(), 0, 0, 10, 10);
	else if (my_gun == 2)
	{
		Ellipse(RENDERMANAGER->GetMemDC(), 0, 0, 10, 10);
		Rectangle(RENDERMANAGER->GetMemDC(), 10, 0, 20, 10);
	}
	else if (my_gun == 3)
	{
		Ellipse(RENDERMANAGER->GetMemDC(), 0, 0, 10, 10);
		Rectangle(RENDERMANAGER->GetMemDC(), 10, 0, 20, 10);
		Ellipse(RENDERMANAGER->GetMemDC(), 20, 0, 30, 10);
	}
	else if (my_gun == 4)
	{
		Ellipse(RENDERMANAGER->GetMemDC(), 0, 0, 10, 10);
		Rectangle(RENDERMANAGER->GetMemDC(), 10, 0, 20, 10);
		Ellipse(RENDERMANAGER->GetMemDC(), 20, 0, 30, 10);
		Rectangle(RENDERMANAGER->GetMemDC(), 30, 0, 40, 10);

	}
	else if (my_gun == 5)
	{
		Ellipse(RENDERMANAGER->GetMemDC(), 0, 0, 10, 10);
		Rectangle(RENDERMANAGER->GetMemDC(), 10, 0, 20, 10);
		Ellipse(RENDERMANAGER->GetMemDC(), 20, 0, 30, 10);
		Rectangle(RENDERMANAGER->GetMemDC(), 30, 0, 40, 10);
		Ellipse(RENDERMANAGER->GetMemDC(), 40, 0, 50, 10);

	}}
	if (m_moveHCnt != -1) {
		BITMAPMANAGER->GetImage()["PLAYERLR"]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
			m_info.m_w / PLAYER_IMAGE_NUM,
			m_info.m_h,
			(m_info.m_w / PLAYER_IMAGE_NUM) * m_moveHCnt,
			0,
			m_info.m_w / PLAYER_IMAGE_NUM,
			m_info.m_h, RGB(255, 255, 255));
	}

	else {
		BITMAPMANAGER->GetImage()["PLAYERTB"]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
			m_tbImageW / PLAYER_IMAGE_NUM,
			m_tbImageH,
			(m_tbImageW / PLAYER_IMAGE_NUM) * m_moveVCnt,
			0,
			m_tbImageW / PLAYER_IMAGE_NUM,
			m_tbImageH, RGB(255, 255, 255));

	}



}

void Player::Realease()
{

}

void Player::RenderShiled()
{

	BITMAPMANAGER->GetImage()["SHIELD"]->TransparentBlt(RENDERMANAGER->GetMemDC(), m_info.m_x, m_info.m_y,
		m_shiledW,
		m_info.m_h,
		0,
		0,
		m_shiledW,
		m_info.m_h, RGB(255, 255, 255));
}

void Player::SetItem(int a)
{
	if (a == 0)
	{
		if (my_gun < 5)
		{
			my_gun++;
			return;
		}
	}
	if (a == 1)
	{
		if (my_bomb < 4)
		{
			my_bomb++;
			return;
		}
	}
}

void Player::SetPlayerRect()
{
	m_rect.left = m_info.m_x + 12;
	m_rect.top = m_info.m_y;
	m_rect.right = m_info.m_x + m_info.m_w / 8;
	m_rect.bottom = m_info.m_y + m_info.m_h;
}

Obj * Player::CreateMISSILE(int x, int y)
{
	m_missile = ObjMaker<Missile>::Create(x, y);
	dynamic_cast<Missile*>(m_missile)->SetMONSTERist(m_monsterlist);
	return m_missile;
}

Obj * Player::CreateSTRONG(int x, int y)
{
	m_missile = ObjMaker<StrongMissile>::Create(x, y);
	dynamic_cast<StrongMissile*>(m_missile)->SetMONSTERist(m_monsterlist);
	return m_missile;

}

