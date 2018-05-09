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

	int		nMaxHP; // �ִ� ü��
	int		nHP; // ���� ü��

	int		nDamage; // ���ݷ�
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

//��忡 ���� ����
typedef struct node_s {
	int degree;                          //���� �� ����� ���� ��. ��, �ڷ� ���� Ʈ������ ���� ��. 
	int distance;                        //�� ���κ��� ������������ �Ÿ�
	int value_factor;                   //��ġ ��( degree + distance ) 

	INTPOINT pos;                           //�� ����� ��ġ (�׸����� ��ġ) 
	struct node_s* direct[8];       //Ȯ�� ������ 8���⿡ ���� ���
	struct node_s* prev_node;    //��ũ�� ����Ʈ ���� ��� 
	struct node_s* next_node;     //��ũ�� ����Ʈ ���� ��� 

} node_t;



//��带 �������� �� �� ����.
typedef struct node_stack_s {
	node_t*  node;                            //�� ���� ��ġ���� ����Ű�� �ִ� ��� 
	struct node_stack_s*  next_node;    //�� ������ ���� ��ġ  
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