#pragma once

class CObj;

class CScrollManager
{
public:
	void Init();
	void Update();
	void ReSet();

public:
	float GetScrollX() { return m_fScrollX; }
	float GetScrollY() { return m_fScrollY; }
	const INTPOINT& GetScrollEndPos() { return m_tEndPos; }

public:
	void SetScrollX(float x) { m_fScrollX += x; }
	void SetScrollY(float y) { m_fScrollY += y; }
	void SetScrollXY(float x, float y) { m_fScrollX = x; m_fScrollY = y; }

public:
	static CScrollManager* GetInstance()
	{
		if (nullptr == m_pInstance) m_pInstance = new CScrollManager;
		return m_pInstance;
	}

private:
	CScrollManager() = default;
	~CScrollManager() = default;

private:
	static CScrollManager* m_pInstance;

private:
	float	m_fScrollX;
	float	m_fScrollY;
	float	m_fSpeed;

private:
	INTPOINT m_tEndPos;
};

