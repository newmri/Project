#pragma once
#include "Enemy.h"
class CBoss :
	public CEnemy
{
public:
	CBoss();
	virtual ~CBoss();

	// Inherited via Obj
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;
};

