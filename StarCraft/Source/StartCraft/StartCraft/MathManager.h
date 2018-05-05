#pragma once

class CMathManager
{
public:
	float CalcDistance(FLOATPOINT tDest, FLOATPOINT tSrc);
	float CalcRadian(FLOATPOINT tDest, FLOATPOINT tSrc);
	float CalcDegree(FLOATPOINT tDest, FLOATPOINT tSrc);

public:
	static CMathManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMathManager;

		return m_pInstance;
	}

private:
	CMathManager() = default;
	~CMathManager() = default;

private:
	static CMathManager* m_pInstance;

};