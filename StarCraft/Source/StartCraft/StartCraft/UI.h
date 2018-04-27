#pragma once

class CUI
{
public:

	// Obj을(를) 통해 상속됨
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release() = 0;

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
	void ChangeAnimation(UI_STATE_ID eId);

public:
	void UpdateRect();

public:
	CUI();
	virtual ~CUI();

protected:
	bool	m_bIsDead;
	bool	m_bIsInit;
	bool	m_bIsUI;

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

protected:
	UI_STATE_ID		m_eCurrId;

protected:
	ANIMATION_INFO* m_tAnimationInfo;
};