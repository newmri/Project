#pragma once

#define MAX_VK 0xff

class CKeyManager
{

public:
	bool KeyPressing(int iVKey);
	bool KeyDown(int iVKey);
	bool KeyUp(int iVKey);

	// 매 프레임마다 키의 상태는 원상복구가 되어야한다.
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