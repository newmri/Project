#pragma once

#include "Enum.h"

class CScene
{
public:
	virtual void Init();
	virtual void LateInit();
	virtual SCENE::SCENE_ID Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release() = 0;

public:
	void LateUIInit();
	void UIUpdate();
	void LateUIUpdate();
	void UIRender();

public:
	void RenderCollsionBox();

public:
	const INFO& GetInfo() const { return m_tInfo; }
	const RECT& GetRect() const { return m_tRect; }
	const bool& IsUI() const { return m_bIsUI; }

public:
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }

public:
	void SetMouseOver();
	void SetIdle();

public:
	void AddUI(CUI* pObj, UI_ID eID);

public:
	void ChangeAnimation(UI_STATE_ID eId);

public:
	void UpdateRect();

public:
	CScene();
	virtual ~CScene();

protected:
	bool	m_bIsDead;
	bool	m_bIsInit;
	bool	m_bIsUI;

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

protected:
	UI_STATE_ID		m_eCurrId;
	SCENE::SCENE_ID		m_eId;

protected:
	ANIMATION_INFO* m_tAnimationInfo;

protected:
	UILIST	m_uiList[UI_END];
};

