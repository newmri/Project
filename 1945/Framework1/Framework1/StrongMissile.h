#pragma once
#include"Bullet.h"
class StrongMissile:public Bullet
{
public:
	StrongMissile();
	~StrongMissile();
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;
	void SetMONSTERist(OBJLIST* lis) { m_monsterlist = lis; }

private:
	OBJLIST* m_monsterlist;

	int target_x;
	int target_y;
	int target_dis;
	int ex_target_dis;
};


