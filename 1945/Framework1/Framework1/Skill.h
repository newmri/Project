#pragma once
#include "Bullet.h"
class Skill : public Bullet
{
public:
	Skill();
	~Skill();

	// Inherited via Bullet
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;


	void SetSKILLBULLETList(OBJLIST* lis) { m_skillbulletlist = lis; }

	void SetPlayerLevel(int level) { my_level = level; }


private:

	int my_level;
	DWORD m_time;

	bool rl = false;

	OBJLIST* m_skillbulletlist;

};

