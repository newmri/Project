#pragma once

class CMouseManager
{
	
public:
	void Init();
	void UpdateRect();
	void Update();
	void Render();
	void Release();

public:
	void CheckMouseOver(UILIST& target);


public:
	static CMouseManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMouseManager;

		return m_pInstance;
	}

private:
	CMouseManager() = default;
	~CMouseManager() = default;

private:
	static CMouseManager* m_pInstance;

private:
	POINT				m_tImageSize;
	POINT				m_tPos;
	RECT				m_tRect;

private:
	ANIMATION_INFO		m_tAnimationInfo[CURSOR_END];
	CURSOR_ID			m_eCurrId;
};