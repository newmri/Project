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

	void RenderCollsionBox();

public:
	const INFO& GetInfo() const { return m_tInfo; }
	const RECT& GetRect() const { return m_tRect; }
	const STAT& GetStat() const { return m_tStat; }
	const OWNER_ID& GetOwnerId() const { return m_tInfo.eOwnerId; }
	const UNIT_SELECT& GetSize() const { return  m_tInfo.eUnitSize; }
	const RECT& GetSelectRect() const { return m_tSelectRect; }
	const OBJ_ID& GetObjId() const { return m_tInfo.eObjId; }

	const bool& IsUI() const { return m_bIsUI; }
	bool IsClicked(const POINT& pos) const;

public:
	void SetDead() { m_bIsDead = true; }
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }
	void SetSpeed(float fSpeed) { m_tInfo.fSpeed = fSpeed; }
	void SetStat(STAT tagStat) { m_tStat = tagStat; }
	void SetOwnerId(OWNER_ID eId) { m_tInfo.eOwnerId = eId; }
	void SetSize(UNIT_SELECT eId) { m_tInfo.eUnitSize = eId; }
	void SetObjId(OBJ_ID eId) { m_tInfo.eObjId = eId; }



public:
	CObj();
	~CObj();

protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	RECT	m_tRect;
	RECT	m_tSelectRect;

	bool	m_bIsDead;
	bool	m_bIsInit;
	bool	m_bIsUI;

protected:
	ANIMATION_INFO*		m_tAnimationInfo;

};

