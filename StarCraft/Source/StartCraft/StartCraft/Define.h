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

static const int TILE_SIZE = 32;

static const float SCROLL_SPEED = static_cast<float>(TILE_SIZE);


const char OBJ_DIR[OBJ_END][STR_LEN] = 
{
	{ "Resources/Image/Cursor/*.*" },
	{ "Resources/Image/Structure/Barrack/*.*" },
	{ "Resources/Image/Structure/Control/*.*" }
};

const char BUTTON_DIR[BUTTON_END][STR_LEN] =
{
	{ "Resources/Image/MainMenu/Button/SinglePlay/*.*" },
	{ "Resources/Image/MainMenu/Button/MultiPlay/*.*" },
	{ "Resources/Image/MainMenu/Button/Editor/*.*" },
	{ "Resources/Image/MainMenu/Button/Exit/*.*" },
	{ "Resources/Image/MainMenu/Button/STR/SinglePlay/*.*" },
	{ "Resources/Image/MainMenu/Button/STR/MultiPlay/*.*" },
	{ "Resources/Image/MainMenu/Button/STR/Editor/*.*" },
	{ "Resources/Image/MainMenu/Button/STR/Exit/*.*" }

};

const char MAP_DIR[MAP_END][STR_LEN] =
{
	{ "Resources/Image/Map/Tile/*.*" },
	{ "Resources/Image/Map/Beginner/*.*" }
};

const char IMAGE_DIR[IMAGE_END][STR_LEN] =
{
	{ "Resources/Image/MainMenu/Menu/*.*" },
	{ "Resources/Image/UI/Bottom/*.*" },
	{ "Resources/Image/Map/MainMap/*.*" },
	{ "Resources/Image/Map/MiniMap/*.*" },
	{ "Resources/Image/Map/Tile/*.*" },
	{ "Resources/Image/UI/ResourcesIcon/*.*" },
	{ "Resources/Image/Select/*.*" }


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
#define SCROLLMANAGER CScrollManager::GetInstance()
#define TILEMANAGER CTileManager::GetInstance()