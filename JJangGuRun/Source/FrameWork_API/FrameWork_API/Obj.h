#pragma once

class CObj
{
public:
	virtual void Init() = 0;
	virtual void LateInit();
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	void RenderCollsionBox();
	void UpdateRect();

public:
	const INFO& GetInfo() const { return m_info; }
	const RECT& GetRect() const { return m_rect; }
	const STAT& GetStat() const { return m_stat; }
	const POINT GetCenter() const
	{
		POINT pos;

		pos.x = m_rect.left + ((m_rect.right - m_rect.left) / 2);
		pos.y = m_rect.bottom - ((m_rect.bottom - m_rect.top) / 2);

		return pos;
	}
	float GetSpeed() { return m_info.fSpeed; }
	LINEINFO* GetLine() { return m_tLine; }
	ObstacleID::OBSTACLE GetObstacleType() { return m_eStoneType; }


public:
	void SetDead() { m_bIsDead = true; }
	void SetRect();
	void SetPos(float fX, float fY) { m_info.fX = fX, m_info.fY = fY; }
	void SetPosX(float fX) { m_info.fX = fX; }
	void SetPosY(float fY) { m_info.fY = fY; }
	void SetCenterPos(float fX, float fY)
	{
		m_info.fX = fX - ((m_rect.right - m_rect.left) / 2);
		m_info.fY = fY - ((m_rect.bottom - m_rect.top) / 2);
	}
	void SetSpeed(float fSpeed) { m_info.fSpeed = fSpeed; }
	void SetStat(STAT tagStat) { m_stat = tagStat; }

	void SetObstacleType(ObstacleID::OBSTACLE eID) { m_eStoneType = eID; }

public:
	void DoAnimation();
	void EnableAnimation(ANIMATION eAnim);
	void ReSetAnimation();

public:
	CObj();
	~CObj();

protected:
	void UpdateLine();

protected:
	INFO	m_info;
	STAT	m_stat;
	RECT	m_rect;

	bool	m_bIsDead;
	bool	m_bIsInit;
	bool	m_bIsFalling;

protected:
	ANIMATION_INFO		m_tAnimationInfo[ANIM_END];
	ANIMATION			m_eCurrAnim;

protected:
	ObstacleID::OBSTACLE	m_eStoneType;
	LINEINFO				m_tLine[SegmentPos::END];


};

