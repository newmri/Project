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
	void RenderDragRect();
	void RenderUI();

public:
	void CheckSwapTile();
	void CheckSelectObj();
	void CheckDragSelectObj();
	CObj* GetTile();

public:
	void MouseScroll();
	
public:
	const RECT& GetMiniMapArea() { return m_tMiniMapRect; }

public:
	void SetMiniMapArea(RECT rc);

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
	POINT				m_tDragPos[DRAG_POS_END];
	RECT				m_tRect;
	RECT				m_tMiniMapRect;
	RECT				m_tSelectRect;
	RECT				m_tSelectRenderRect;
	RECT				m_tDragRenderRect;



private:
	ANIMATION_INFO		m_tAnimationInfo[CURSOR_END];
	IMAGE_INFO* m_tSelectImage;
	STATIC_UI_IMAGE_VECTOR_LIST	m_portraitList[PORTRAIT::PORTRAIT_END];

private:
	CURSOR_ID			m_eCurrId;
	UNIT_SELECT			m_eSelectedUnitsize;
	PORTRAIT::ID		m_eSelectedPortraitId;

private:
	DWORD				m_dwAnimationTime;
	int					m_nAnimationIdx;

private:
	bool				m_bIsSelectedObj;
	bool				m_bIsDragging;
};