#pragma once

#define MAX_VK 0xff

class CKeyManager
{

public:
	bool KeyPressing(int iVKey);
	bool KeyDown(int iVKey);
	bool KeyUp(int iVKey);

	// �� �����Ӹ��� Ű�� ���´� ���󺹱��� �Ǿ���Ѵ�.
	void Update();

public:
	static CKeyManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyManager;

		return m_pInstance;
	}

public:
	void Release();

private:
	CKeyManager();
	~CKeyManager();

private:
	static CKeyManager* m_pInstance;

private:
	bool		m_bKeyState[MAX_VK];
};