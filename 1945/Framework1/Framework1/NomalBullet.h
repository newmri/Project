#pragma once
#include "Bullet.h"
class NomalBullet : public Bullet
{
public:
	NomalBullet();
	~NomalBullet();

	// Inherited via Bullet
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;
};

