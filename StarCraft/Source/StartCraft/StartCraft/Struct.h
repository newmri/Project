#pragma once

#include <atlstr.h>

typedef struct tagFloatPoint
{
	float fX;
	float fY;

	tagFloatPoint()
	{
		fX = 0.f;
		fY = 0.f;
	}

	tagFloatPoint(float x, float y)
	{
		fX = x;
		fY = y;
	}

	tagFloatPoint(int x, int y)
	{
		fX = static_cast<float>(x);
		fY = static_cast<float>(y);
	}

	tagFloatPoint(LONG x, LONG y)
	{
		fX = static_cast<float>(x);
		fY = static_cast<float>(y);
	}

}FLOATPOINT;

typedef struct tagInfo {
	 
	FLOATPOINT		tPos;

	int			nW;
	int			nH;

	float		fSpeed;
	float		fAcc;
	float		fAngle;

	OWNER_ID			eOwnerId;
	UNIT_SELECT			eUnitSize;
	OBJ_ID				eObjId;
	PORTRAIT::ID		ePortraitId;
	UNIT::LARGE_WIRE::LARGE_WIRE_ID		eLargeWireId;
	UNIT::SMALL_WIRE::SMALL_WIRE_ID		eSmallWireId;



}INFO;

typedef struct tagStat {

	int		nMaxHP; // 최대 체력
	int		nHP; // 현재 체력

	int		nDamage; // 공격력
	int		nAttackRange;
}STAT;

typedef struct tagBitmapAnimationInfo
{
	char**	tName;

	int		nImageW;
	int		nImageH;
	int		nAnimationNum;
	int		nStateNum;

}BITMAP_ANIMATION_INFO;

typedef struct tagAnimationInfo
{
	char**	tName;

	int		nImageW;
	int		nImageH;
	int		nCnt;
	int		nAnimationNum;
	int		nStateNum;

	DWORD	dwAnimationTime;

}ANIMATION_INFO;


typedef struct tagIntPoint
{
	int x;
	int y;

	void operator=(const tagIntPoint& other)
	{
		x = other.x;
		y = other.y;
	}
	tagIntPoint() {}
	tagIntPoint(int x, int y) : x(x), y(y) {}
	tagIntPoint(FLOATPOINT tPos) : x(tPos.fX), y(tPos.fY) {}


}INTPOINT;

typedef struct tagImageInfo
{
	char szName[STR_LEN];

	int		nImageW;
	int		nImageH;
	int		nImageNum;

}IMAGE_INFO;


typedef struct tagStaticUIImageInfo
{
	IMAGE_INFO  tInfo;
	INTPOINT	tPos;
	INTPOINT	tDrawSize;
	COLORREF	tColor;

}STATIC_UI_IMAGE_INFO;

typedef struct tagBuildInfo
{
	STATIC_UI_IMAGE_INFO tImage;
	
	INTPOINT tClickArea;
	int nMineCost;
	int nGasCost;

	tagBuildInfo()
	{
		nMineCost = 0;
		nGasCost = 0;

	}

}BUILD_INFO;

typedef struct tagCommandInfo
{
	STATIC_UI_IMAGE_INFO tImage;

	INTPOINT tClickArea;
	bool bRender;

	tagCommandInfo()
	{
		bRender = false;

	}

}COMMAND_INFO;

typedef struct tagUnitSelectInfo
{
	OBJ_ID				eId;
	UNIT_SELECT			eSelectedUnitsize;
	PORTRAIT::ID		eSelectedPortraitId;
	UNIT::WIRE_ID		eSelectedWireSizeId;
	UNIT::LARGE_WIRE::LARGE_WIRE_ID		eSelectedLargeWireId;
	UNIT::SMALL_WIRE::SMALL_WIRE_ID		eSelectedSmallWireId;

	bool				bIsStructure;

	RECT				tSelectRenderRect;
	POINT				tDrawPos;
	INTPOINT				tPos;
	TCHAR 				szName[STR_LEN];
	TCHAR 				szHp[STR_LEN];

}UNIT_SELECT_INFO;

typedef struct tagPathScore
{
	int** nPos;

}PATH_SCORE;

//노드에 대한 정의
typedef struct node_s {
	int degree;                          //현재 이 노드의 깊이 값. 즉, 자료 구조 트리에서 깊이 값. 
	int distance;                        //이 노드로부터 목적지까지의 거리
	int value_factor;                   //평가치 값( degree + distance ) 

	INTPOINT pos;                           //이 노드의 위치 (그리드의 위치) 
	struct node_s* direct[8];       //확장 가능한 8방향에 대한 노드
	struct node_s* prev_node;    //링크드 리스트 이전 노드 
	struct node_s* next_node;     //링크드 리스트 다음 노드 

} node_t;



//노드를 재정렬할 때 쓸 스택.
typedef struct node_stack_s {
	node_t*  node;                            //이 스택 위치에서 가리키고 있는 노드 
	struct node_stack_s*  next_node;    //이 스택의 다음 위치  
} node_stack_t;

typedef struct tagResources
{
	int nValue;
	TCHAR szValue[STR_LEN];

	INTPOINT tPos;

	tagResources()
	{
		nValue = 1000;
	}
}RESOURCES;