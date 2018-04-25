#pragma once
typedef struct tagInfo {
	 
	float		fX;
	float		fY;

	int			nW;
	int			nH;

	float		fSpeed;
	int			nJumpPower;
	float		fAcc;
	float		fFallAcc;


}INFO;

typedef struct tagStat {

	int		nMaxHP; // 최대 체력
	int		nHP; // 현재 체력

	int		nDamage; // 공격력

}STAT;

typedef struct tagLineInfo
{
	int iFirstPtX;
	int iFirstPtY;
	int iLastPtX;
	int iLastPtY;

}LINEINFO;

typedef struct tagAnimationInfo
{
	int		nImageW;
	int		nImageH;
	int		nCnt;

	DWORD	dwAnimationTime;

}ANIMATION_INFO;

typedef struct tagBlockPos
{
	tagBlockPos()
		: fX(0.f), fY(0.f), nW(0), nH(0), eID(ObstacleID::END) {}

	tagBlockPos(float x, float y, ObstacleID::OBSTACLE _eID)
		: fX(x), fY(y), eID(_eID) {}

	tagBlockPos(INFO tInfo, ObstacleID::OBSTACLE _eID)
		: fX(tInfo.fX), fY(tInfo.fY), nW(tInfo.nW), nH(tInfo.nH), eID(_eID) {}

	float fX;
	float fY;
	int			nW;
	int			nH;

	ObstacleID::OBSTACLE eID;

}BLOCKPOS;


typedef struct tagBlockInfo
{
	tagBlockInfo()
		: tBlock({}) {}

	tagBlockInfo(const BLOCKPOS& tBlock)
		: tBlock(tBlock) {}

	BLOCKPOS tBlock;

}BLOCKINFO;

typedef struct tagPos
{
	float fX;
	float fY;

}POS;