#pragma once

class CObj
{
public:
	virtual void Init() = 0;
	virtual void LateInit();
	virtual int Update()=0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Realease() = 0;

	void RenderCollsionBox();

public:
	const INFO& GetInfo() const { return m_tInfo; }
	const RECT& GetRect() const { return m_tRect; }
	const STAT& GetStat() const { return m_tStat; }

public:
	void SetDead() { m_bIsDead = true; }
	void SetRect();
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }
	void SetSpeed(float fSpeed) { m_tInfo.fSpeed = fSpeed; }
	void SetStat(STAT tagStat) { m_tStat = tagStat; }

public:
	void DoAnimation();
	/*void EnableAnimation(ANIMATION eAnim);*/
	void ReSetAnimation();

public:
	CObj();
	~CObj();

protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	RECT	m_tRect;

	bool	m_bIsDead;
	bool	m_bIsInit;

protected:
	ANIMATION_INFO*		m_tAnimationInfo;

};

