#pragma once

class CCollisionManager
{

public:
	void RectCollision(OBJLIST& dest, OBJLIST& src);
	void ItemCollision(OBJLIST& dest, OBJLIST& src);
	void SphereCollision(OBJLIST& dest, OBJLIST& src);
	void SphereCollision(OBJLIST& dest, OBJLIST& src, int a);

public:
	void Release();

public:
	static CCollisionManager* GetInstance()
	{
		if (m_instance == nullptr) m_instance = new CCollisionManager;
		return m_instance;
	}

	~CCollisionManager();
private:
	bool CheckSphere(Obj* pDest, Obj* pSrc);

private:
	CCollisionManager();
	CCollisionManager(const CCollisionManager&) = delete;
	void operator=(const CCollisionManager&) = delete;

private:
	static CCollisionManager* m_instance;
};