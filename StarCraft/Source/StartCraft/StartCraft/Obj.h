#pragma once

class CObj
{
public:
	virtual void Init() = 0;
	virtual void LateInit();
	virtual int Update()=0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	void UpdateRect();
	void RenderCollsionBox();

public:
	const INFO& GetInfo() const { return m_tInfo; }
	const RECT& GetRect() const { return m_tRect; }
	const STAT& GetStat() const { return m_tStat; }
	const bool& IsUI() const { return m_bIsUI; }

public:
	void SetDead() { m_bIsDead = true; }
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }
	void SetSpeed(float fSpeed) { m_tInfo.fSpeed = fSpeed; }
	void SetStat(STAT tagStat) { m_tStat = tagStat; }

public:
	CObj();
	~CObj();

protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	RECT	m_tRect;

	bool	m_bIsDead;
	bool	m_bIsInit;
	bool	m_bIsUI;

protected:
	ANIMATION_INFO*		m_tAnimationInfo;

};

