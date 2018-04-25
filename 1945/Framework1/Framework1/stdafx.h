// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <list>
#include <math.h>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include"My_Define.h"
#include"My_Enum.h"
#include"My_Extern.h"
#include"My_Struct.h"
#include"My_Type.h"

// Scene
#include "Scene.h"
#include "MainMenu.h"
#include "Stage1.h"
#include "Stage2.h"

// Enemy
#include "NormalEnemy.h"

/////////매니저///////////////
#include"ObjDelete.h"
#include"ObjMaker.h"

#include "CollisionManager.h"
#include "SoundManager.h"
#include "BitmapManager.h"
#include "RenderManager.h"
#include "SceneManager.h"

//////////////////////////////
#define SOUNDMANAGER CSoundManager::GetInstance()
#define COLLISIONMANAGER CCollisionManager::GetInstance()
#define BITMAPMANAGER CBitmapManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()
#define SCENEMANAGER CSceneManager::GetInstance()
//////////////////////////////웨폰 레벨에 따라 갯수 정하기