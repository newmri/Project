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

	int		nMaxHP; // �ִ� ü��
	int		nHP; // ���� ü��

	int		nDamage; // ���ݷ�

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