#pragma once
class CObj;

// ������
class CObjectManager
{
public:
	CObj* GetPlayer();
	CObj* GetTarget(CObj* pSrc, OBJTYPE eID);

public:
	void AddObject(CObj* pObj, OBJTYPE eID);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

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

private:
	static CObjectManager*	m_pInstance;

private:
	OBJLIST m_objList[OBJTYPE::END];

private:
	bool		m_bIsPlayerDead;
};