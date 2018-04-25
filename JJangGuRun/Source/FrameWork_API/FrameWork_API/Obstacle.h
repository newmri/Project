#pragma once
#include "Obj.h"

class CObstacle :
	public CObj
{
public:
	CObstacle();
	CObstacle(const BLOCKINFO& rInfo);
	virtual ~CObstacle();

public:
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

public:
	void SetCount();
	void SetRevival() { m_bIsDead = false; m_dwOld = -1; }

private:
	void MovingStone();
	void CreateBullet(ObstacleID::OBSTACLE eID);
	void CreatePoop(ObstacleID::OBSTACLE eID);
	void CreateThorn(ObstacleID::OBSTACLE eID);

private:
	DWORD		m_dwOld;
	DWORD		m_dwBullet;
	DWORD		m_dwPoop;
	DWORD		m_dwPoopBlock;

	float		m_fOldposX;
	float		m_fOldposY;


	int			m_AnimNum;
};

