#pragma once

class CObj;

class CGameManager
{
public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	static CGameManager* GetInstance()
	{
		if (nullptr == m_pInstance) m_pInstance = new CGameManager;
		return m_pInstance;
	}

private:
	CGameManager();
	~CGameManager();

private:
	static CGameManager* m_pInstance;
};

