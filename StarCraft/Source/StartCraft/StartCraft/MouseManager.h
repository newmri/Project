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
	void CheckSwapTile();
	void CheckSelectObj();
	CObj* GetTile();

public:
	void MouseScroll();

public:
	void SetMiniMapArea(RECT rc) { m_tMiniMapRect = rc; }

public:
	void MoveScrollByMouse();

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
	RECT				m_tMiniMapRect;
	RECT				m_tSelectRect;
	RECT				m_tSelectRenderRect;


private:
	ANIMATION_INFO		m_tAnimationInfo[CURSOR_END];
	IMAGE_INFO* m_tSelectImage;

private:
	CURSOR_ID			m_eCurrId;
	UNIT_SELECT			m_eSelectedUnitsize;

private:
	bool				m_bIsSelectedObj;
};