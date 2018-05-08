#pragma once
#include "Unit.h"

class CScv : public CUnit
{
public:

	// Obj을(를) 통해 상속됨
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

public:
	virtual bool CheckCommand(POINT tMousePos);

public:
	virtual void RenderUI();

public:
	virtual void Move();
	virtual void Attack();

public:
	void BuildStructure(OBJ_ID eId, INTPOINT pos, float fAngle);
	void Build();

public:
	void UpdateRect();


private:
	int m_nBuildCnt;

	CObj* m_pControlTarget;

	bool m_bIsRetunning;

private:
	SCV_COMMAND m_eCommand;

private:
	COMMAND_VECTOR_LIST		m_commandList;
	BUILD_VECTOR_LIST		m_buildList[2];
	STATIC_UI_IMAGE_VECTOR_LIST m_buildImageList[2];

private:
	SCV_STATE::ID m_eCurrId;

private:
	DWORD m_dwBuildTime;

private:
	OBJ_ID m_eBuildId;
	INTPOINT m_BuildPos;
};