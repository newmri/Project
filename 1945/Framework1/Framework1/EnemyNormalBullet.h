#pragma once
#include "Bullet.h"

class CEnymyNormalBullet : public Bullet
{
public:
	// Inherited via Obj
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;
};