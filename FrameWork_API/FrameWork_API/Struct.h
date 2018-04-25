#pragma once
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

typedef struct tagAnimationInfo
{
	int		nImageW;
	int		nImageH;
	int		nCnt;

	DWORD	dwAnimationTime;

}ANIMATION_INFO;