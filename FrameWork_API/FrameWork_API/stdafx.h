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
#include <math.h>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

// 02.Scene
#include "MainMenu.h"
#include "Stage1.h"

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

// TODO: reference additional headers your program requires here

// 98.Headers
#include "Define.h"
#include "Enum.h"
#include "Extern.h"
#include "Struct.h"
#include "Type.h"
#include "Function.h"