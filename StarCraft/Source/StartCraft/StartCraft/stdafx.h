// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <vector>
#include <math.h>
#include <iostream>
#include <functional>
#include <algorithm>
#include <io.h>
#include <queue>

using namespace std;

// 98.Headers
#include "Enum.h"
#include "Define.h"
#include "Extern.h"
#include "Struct.h"
#include "Type.h"
#include "Function.h"

// 01.01. UI
#include "UI.h"

// 02.Scene
#include "Scene.h"
#include "MainMenu.h"
#include "SinglePlay.h"


// 97.Managers
#include "GameManager.h"
#include "BitmapManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "FactoryManager.h"
#include "ObjectManager.h"
#include "MouseManager.h"
#include "ScrollManager.h"
#include "TileManager.h"
#include "PathManager.h"
#include "MathManager.h"


// TODO: reference additional headers your program requires here
