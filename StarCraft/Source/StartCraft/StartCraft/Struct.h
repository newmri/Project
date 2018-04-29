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

}BITMAP_ANIMATION_INFO;

typedef struct tagAnimationInfo
{
	char**	tName;

	int		nImageW;
	int		nImageH;
	int		nCnt;
	int		nAnimationNum;

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

}STATIC_UI_IMAGE_INFO;
