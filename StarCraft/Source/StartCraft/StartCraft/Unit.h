#pragma once
#include "Obj.h"

class CUnit : public CObj
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
	bool CheckCommand(POINT tMousePos);

public:
	void RenderUI();

public:
	void Move();
	void Attack();
	void Build();

public:
	void UpdateRect();

private:
	UNIT::STATE_ID m_eCurrId;

private:
	int m_nAttackAnim;
	int m_nAttackCnt;
	int m_nMaxAttackCnt;

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
	DWORD m_dwBuildTime;

};