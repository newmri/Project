#pragma once
class CScrollManager
{
private:
	CScrollManager();
	~CScrollManager();

public:
	void ReSet() { m_fScrollY = 0; }
public:
	float GetScrollY() { return m_fScrollY; }

public:
	void SetScrollY(float y) { m_fScrollY += y; }

public:
	static CScrollManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollManager;

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

private:
	static CScrollManager* m_pInstance;

	float	m_fScrollY;
};

