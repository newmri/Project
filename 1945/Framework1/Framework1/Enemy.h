#pragma once
#include "Obj.h"
class CEnemy :
	public Obj
{
public:
	CEnemy();
	virtual ~CEnemy();

	// Inherited via Obj
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;

	void SetNormalBulletList(OBJLIST* p) { m_normalBulletLlist = p; }
	void SetNormalBulletSpawnTime(int time) { m_normalBulletSpawnTime = time; }

protected:
	OBJLIST* m_normalBulletLlist;
	DWORD m_bulletSpawnTime;

	int m_normalBulletSpawnTime;
	int m_firstX;
	int m_firstY;

};

