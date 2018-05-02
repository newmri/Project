#pragma once

#include <atlstr.h>

typedef struct tagInfo {
	 
	float		fX;
	float		fY;

	int			nW;
	int			nH;

	float		fSpeed;
	int			nJumpPower;
	float		fAcc;
	float		fJumpUpAcc;
	float		fJumpDownAcc;

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


typedef struct tagUnitSelectInfo
{
	UNIT_SELECT			eSelectedUnitsize;
	PORTRAIT::ID		eSelectedPortraitId;
	UNIT::WIRE_ID		eSelectedWireSizeId;
	UNIT::LARGE_WIRE::LARGE_WIRE_ID		eSelectedLargeWireId;
	UNIT::SMALL_WIRE::SMALL_WIRE_ID		eSelectedSmallWireId;

	RECT				tSelectRenderRect;
	POINT				tDrawPos;

}UNIT_SELECT_INFO;

