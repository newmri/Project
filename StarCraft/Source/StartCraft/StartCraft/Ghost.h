#pragma once
#include "Unit.h"

class CGhost : public CUnit
{
public:

	// Obj��(��) ���� ��ӵ�
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



};