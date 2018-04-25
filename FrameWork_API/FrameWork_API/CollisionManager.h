#pragma once

#include "Type.h"

class CCollisionManager
{
public:
	void Release();

public:
	void RectCollision(OBJLIST& dest, OBJLIST& src);
	void ItemCollision(OBJLIST& dest, OBJLIST& src);
	void SphereCollision(OBJLIST& dest, OBJLIST& src);

public:
	static CCollisionManager* GetInstance()
	{
		if (m_pInstance == nullptr) m_pInstance = new CCollisionManager;
		return m_pInstance;
	}

private:
	bool CheckSphere(CObj* pDest, CObj* pSrc);

private:
	CCollisionManager() = default;
	~CCollisionManager() = default;
	CCollisionManager(const CCollisionManager&) = delete;
	void operator=(const CCollisionManager&) = delete;

private:
	static CCollisionManager* m_pInstance;
};