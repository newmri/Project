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
	const RECT GetRectWithScroll() const;
	const RECT GetSelectRectWithScroll() const;
	const STAT& GetStat() const { return m_tStat; }
	const OWNER_ID& GetOwnerId() const { return m_tInfo.eOwnerId; }
	const UNIT_SELECT& GetSize() const { return  m_tInfo.eUnitSize; }
	const RECT& GetSelectRect() const { return m_tSelectRect; }
	const OBJ_ID& GetObjId() const { return m_tInfo.eObjId; }
	const PORTRAIT::ID& GetPortraitId() { return m_tInfo.ePortraitId; }
	const UNIT::LARGE_WIRE::LARGE_WIRE_ID& GetLargeWireId() { return m_tInfo.eLargeWireId; }
	const UNIT::SMALL_WIRE::SMALL_WIRE_ID& GetSmallWireId() { return m_tInfo.eSmallWireId; }
	
public:
	const bool& IsUI() const { return m_bIsUI; }
	bool IsClicked(const INTPOINT& pos) const;
	const bool& IsStructure() const { return m_bIsStructure; }

public:
	void SetDead() { m_bIsDead = true; }
	void SetPos(FLOATPOINT tPos) { m_tInfo.tPos = tPos; }
	void SetSpeed(float fSpeed) { m_tInfo.fSpeed = fSpeed; }
	void SetStat(STAT tagStat) { m_tStat = tagStat; }
	void SetOwnerId(OWNER_ID eId) { m_tInfo.eOwnerId = eId; }
	void SetSize(UNIT_SELECT eId) { m_tInfo.eUnitSize = eId; }
	void SetObjId(OBJ_ID eId) { m_tInfo.eObjId = eId; }
	void SetPortraitId(PORTRAIT::ID eId) { m_tInfo.ePortraitId = eId; }
	void SetLargeWireId(UNIT::LARGE_WIRE::LARGE_WIRE_ID eId) { m_tInfo.eLargeWireId = eId; }
	void SetSmallWireId(UNIT::SMALL_WIRE::SMALL_WIRE_ID eId) { m_tInfo.eSmallWireId = eId; }
	void SetHP(int hp) { m_tStat.nMaxHP = hp; m_tStat.nHP = hp; }
	void SetAttack(INTPOINT returnPos, float fAngle) { m_tReturnPos = returnPos; m_bAttack = true; m_fAttackAngle = fAngle; }

public:
	void SetMove(node_t* node);

public:
	CObj();
	~CObj();

protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	RECT	m_tRect;
	RECT	m_tSelectRect;
	INTPOINT	m_tSelectRectIdx;

	bool	m_bIsDead;
	bool	m_bIsInit;
	bool	m_bIsUI;
	bool	m_bMove;
	bool	m_bAttack;
	bool	m_bIsStructure;

protected:
	list<INTPOINT> m_route;

protected:
	ANIMATION_INFO*		m_tAnimationInfo;

	DWORD m_dwTime;
	DWORD m_dwAttackTime;

	FLOATPOINT m_tMovePos;
	INTPOINT m_tReturnPos;

	float m_fAttackAngle;

	int m_cnt;
	int m_maxCnt;
	int m_nBoforeIdx;
};

