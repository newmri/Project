#pragma once
class CObj;

// ������
class CObjectManager
{
public:
	CObj* GetPlayer();

public:
	void AddObject(CObj* pObj, OBJ_ID eID);
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

private:	// �ܺ� ���� ����.
	CObjectManager() = default;
	~CObjectManager() = default;

private:
	static CObjectManager*	m_pInstance;

private:
	OBJLIST m_objList[OBJ_ID::OBJ_END];

private:
	bool		m_bIsPlayerDead;
};