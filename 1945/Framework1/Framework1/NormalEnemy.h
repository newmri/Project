#pragma once
#include "Enemy.h"
class CNormalEnemy :
	public CEnemy
{
public:
	CNormalEnemy();
	virtual ~CNormalEnemy();

	// Inherited via Obj
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;
};

