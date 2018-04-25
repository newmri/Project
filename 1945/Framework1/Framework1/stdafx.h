// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
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


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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

/////////�Ŵ���///////////////
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
//////////////////////////////���� ������ ���� ���� ���ϱ�