#pragma once
class CObj;

// ������
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
	// �̱���
	static CObjectManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjectManager;	// ��ü�� ���� ���� 1���� �����ϰ� �ִ�!

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


private:	// �ܺ� ���� ����.
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