#pragma once
class CObj;

// 중재자
class CObjectManager
{
public:
	CObj* GetPlayer();
	OBJLIST* GetObLst() { return m_objList; }

	CObj* GetTarget(CObj* pSrc, OBJTYPE eID);

	bool IsPlayerDead() { return m_bIsPlayerDead; }

public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void AddObject(CObj* pObj, OBJTYPE eID);
public:
	void ReSet();

public:
	// 싱글톤
	static CObjectManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjectManager;	// 객체의 생성 수는 1개로 제한하고 있다!

		return m_pInstance;
	}

	void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:	// 외부 생성 제한.
	CObjectManager() = default;
	~CObjectManager() = default;

public:
	void LoadData();

private:
	static CObjectManager*	m_pInstance;

private:
	OBJLIST m_objList[OBJTYPE::END];

private:
	bool		m_bIsPlayerDead;

private:
	OBJLIST m_DeadBlock;
	DWORD dwOld;
};