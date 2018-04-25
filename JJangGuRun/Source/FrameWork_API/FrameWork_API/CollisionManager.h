#pragma once

#include "Type.h"

class CCollisionManager
{
public:
	void Release();

public:
	static void CollisionRect(OBJLIST& dstLst, OBJLIST& srcLst);
	static bool CollisionLine(OBJLIST& dstLst, OBJLIST& srcLst, POS& out, COLLISION& collision);
	static void CollisionTrap(OBJLIST& dstLst, OBJLIST& srcLst);

private:
	static bool PointToSegmentDist(CObj* pPlayer, LINEINFO tLine, int iDist);

public:
	static CCollisionManager* GetInstance()
	{
		if (m_pInstance == nullptr) m_pInstance = new CCollisionManager;
		return m_pInstance;
	}

private:
	CCollisionManager() = default;
	~CCollisionManager() = default;
	CCollisionManager(const CCollisionManager&) = delete;
	void operator=(const CCollisionManager&) = delete;

private:
	static CCollisionManager* m_pInstance;
};