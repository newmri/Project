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
	void SelectObj();
	void DragSelectObj();
	void CheckSelectObj();
	void CheckMoveObj();

	CObj* GetTile();
	const POINT& GetPos() { return m_tPos; }
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
	INTPOINT			m_tIntPos;
	POINT				m_tDragPos[DRAG_POS_END];
	RECT				m_tRect;
	RECT				m_tMiniMapRect;
	RECT				m_tSelectRect;
	RECT				m_tDragRenderRect;
	RECT				m_tIllegalRect;


private:
	ANIMATION_INFO		m_tAnimationInfo[CURSOR_END];
	IMAGE_INFO* m_tSelectImage;

private:
	STATIC_UI_IMAGE_VECTOR_LIST	m_portraitList[PORTRAIT::PORTRAIT_END];
	STATIC_UI_IMAGE_VECTOR_LIST* m_wireList[WIRE_IMAGE_SIZE_NUM];

private:
	CURSOR_ID			m_eCurrId;
	UNIT_SELECT_INFO	m_tUnitSelect[MAX_UNIT_SELECT_NUM];

private:
	DWORD				m_dwAnimationTime;
	int					m_nAnimationIdx;
	int					m_nSelectedUnitNum;
	CObj*				m_selectedObj[MAX_UNIT_SELECT_NUM];

private:
	bool				m_bIsDragging;

};