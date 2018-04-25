#pragma once
#define WINDOWS_WIDTH 600
#define WINDOWS_HEIGHT 800
#define PI 3.141592

#define DEAD_OBJ 1
#define DEAD_OBSTACLE 2

static const float FPS = 60.f;

static const float GRAVITY = 9.8f;

// Stage
static const int NUM_OF_STAGE = 1;

// Block
static const int NUM_OF_BLOCK = 14;

// Bullet
static const int NUM_OF_BULLET = 7;

// Enemy
static const int NUM_OF_ENEMY = 1;

// Char
static const int STR_LEN = 128;

// Player
static const int PLAYER_ANIMATION_NUM[ANIM_END] =
{
	6, // Left Idle 
	6, // Right Idle
	4, // Left
	4, // Right
	4, // Up
	4, // Down
	4, // Left Jump
	4, // Right Jump

};


const char PLAYER_IMG_STR[ANIM_END][STR_LEN] =
{
	{ "PlayerLeftIdle" },
	{ "PlayerRightIdle" },
	{ "PlayerMoveLeft" },
	{ "PlayerMoveRight" },
	{ "PlayerMoveUp" },
	{ "PlayerMoveDown" },
	{ "PlayerLeftJump" },
	{ "PlayerRightJump" },
};

#define GAMEMANAGER CGameManager::GetInstance()
#define SOUNDMANAGER CSoundManager::GetInstance()
#define COLLISIONMANAGER CCollisionManager::GetInstance()
#define BITMAPMANAGER CBitmapManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()
#define SCENEMANAGER CSceneManager::GetInstance()
#define KEYMANAGER CKeyManager::GetInstance()
#define OBJMANAGER CObjectManager::GetInstance()
#define SCROLLMANAGER CScrollManager::GetInstance()