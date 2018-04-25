#pragma once
#define WINDOWS_WIDTH 1920
#define WINDOWS_HEIGHT 1080
#define PI 3.141592

static const float FPS = 60.f;

static const float GRAVITY = 9.8f;

// Char
static const int STR_LEN = 128;

// Stage
static const int NUM_OF_STAGE = 1;

// Cursor
static const int CURSOR_SIZE = 128;

const char OBJ_DIR[OBJ_END][STR_LEN] = 
{
	{ "Resources/Image/Cursor/*.*" },
	{ "Resources/Image/MainMenu/Menu/*.*" },
	{ "Resources/Image/MainMenu/SinglePlay/*.*" }
};

#define GAMEMANAGER CGameManager::GetInstance()
#define SOUNDMANAGER CSoundManager::GetInstance()
#define COLLISIONMANAGER CCollisionManager::GetInstance()
#define BITMAPMANAGER CBitmapManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()
#define SCENEMANAGER CSceneManager::GetInstance()
#define KEYMANAGER CKeyManager::GetInstance()
#define OBJMANAGER CObjectManager::GetInstance()
#define MOUSEMANAGER CMouseManager::GetInstance()