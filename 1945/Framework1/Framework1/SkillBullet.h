#pragma once
#include "Bullet.h"

class SkillBullet : public Bullet
{
public:
	SkillBullet();
	~SkillBullet();


	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;
};

