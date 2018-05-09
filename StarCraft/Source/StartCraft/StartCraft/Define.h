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

static const int MAX_UNIT_SELECT_NUM = 12;

static const int WIRE_IMAGE_SIZE_NUM = 2;

static const int DEGREE_INCREMENT = 10;

const TCHAR OBJ_NAME[OBJ_END - 1][STR_LEN] = 
{
	{L"Terran Barrack"},
	{L"Terran Command Center" },
	{ L"Terran Ghost" },
	{ L"Terran Marine" },
	{ L"Terran SCV" }

};
const char OBJ_DIR[OBJ_END][STR_LEN] = 
{
	{ "Resources/Image/Structure/Barrack/*.*" },
	{ "Resources/Image/Structure/Control/*.*" },
	{ "Resources/Image/Unit/Ghost/*.*" },
	{ "Resources/Image/Unit/Marine/*.*" },
	{ "Resources/Image/Unit/Scv/*.*" },
	{ "Resources/Image/Cursor/*.*" },

};

const char OBJ_PORTRAIT_DIR[PORTRAIT::PORTRAIT_END][STR_LEN] =
{
	{ "Resources/Image/Portrait/Advisor/*.*" },
	{ "Resources/Image/Portrait/Ghost/*.*" },
	{ "Resources/Image/Portrait/Marine/*.*" },
	{ "Resources/Image/Portrait/SCV/*.*" }

};

const char OBJ_LARGE_WIRE_DIR[UNIT::LARGE_WIRE::LARGE_WIRE_END][STR_LEN] =
{
	{ "Resources/Image/Wire/Large/Barrack/*.*" },
	{ "Resources/Image/Wire/Large/Control/*.*" },
	{ "Resources/Image/Wire/Large/Ghost/*.*" },
	{ "Resources/Image/Wire/Large/Marine/*.*" },
	{ "Resources/Image/Wire/Large/SCV/*.*" },
	{ "Resources/Image/Wire/Large/Mine/*.*" }


};

const char OBJ_SMALL_WIRE_DIR[UNIT::SMALL_WIRE::SMALL_WIRE_END][STR_LEN] =
{
	{ "Resources/Image/Wire/Small/Ghost/*.*" },
	{ "Resources/Image/Wire/Small/Marine/*.*" },
	{ "Resources/Image/Wire/Small/SCV/*.*" }

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


const char IMAGE_DIR[IMAGE_END][STR_LEN] =
{
	{ "Resources/Image/MainMenu/Menu/*.*" },
	{ "Resources/Image/UI/Bottom/*.*" },
	{ "Resources/Image/Map/MainMap/*.*" },
	{ "Resources/Image/Map/MiniMap/*.*" },
	{ "Resources/Image/Map/Tile/*.*" },
	{ "Resources/Image/UI/ResourcesIcon/*.*" },
	{ "Resources/Image/Select/*.*" },
	{ "Resources/Image/UI/UnitSummonQueue/*.*" },
	{ "Resources/Image/UI/Progress/*.*" },
	{ "Resources/Image/Build/BarrackBuild/*.*" },
	{ "Resources/Image/Build/ControlBuild/*.*" },
	{ "Resources/Image/UI/BuildIcon/Barrack/*.*" },
	{ "Resources/Image/UI/BuildIcon/Control/*.*" },
	{ "Resources/Image/UI/UnitCommandIcon/Marine/*.*" },
	{ "Resources/Image/UI/UnitCommandIcon/Scv/*.*" },
	{ "Resources/Image/UI/UnitCommandIcon/BasicBuild/*.*" },
	{ "Resources/Image/UI/Build/*.*" },
	{ "Resources/Image/Effect/Ghost/*.*" },
	{ "Resources/Image/Effect/Marine/*.*" },
	{ "Resources/Image/Map/Mine/*.*" }


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
#define PATHMANAGER CPathManager::GetInstance()
#define MATHMANAGER CMathManager::GetInstance()