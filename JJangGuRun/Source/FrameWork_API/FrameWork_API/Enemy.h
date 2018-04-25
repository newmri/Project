#pragma once
#include "Obj.h"

class CEnemy :
	public CObj
{
public:
	CEnemy();
	virtual ~CEnemy();

public:
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();
};

