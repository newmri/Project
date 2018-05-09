#pragma once
#include "Obj.h"

class CUnit : public CObj
{
public:

	// Obj을(를) 통해 상속됨
	virtual void Init();
	virtual void LateInit();
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render();
	virtual void Release();
	
public:
	virtual bool CheckCommand(POINT tMousePos) = 0;

public:
	virtual void RenderUI() = 0;

public:
	virtual void Move();
	virtual void Attack();
	bool Die();

public:
	void SetAttack(INTPOINT returnPos, float fAngle) { m_tReturnPos = returnPos; m_bAttack = true; m_fAttackAngle = fAngle; }
	void SetTarget(CObj* pTarget, INTPOINT pos);

	void SetAttack();

public:
	void UpdateRect();

protected:
	UNIT::STATE_ID m_eCurrId;

protected:
	INTPOINT m_tReturnPos;
	INTPOINT m_tAttackTargetPos;
protected:
	CObj* m_pTarget;

protected:
	int m_nAttackAnim;
	int m_nAttackCnt;
	int m_nMaxAttackCnt;

	bool	m_bMove;
	bool	m_bAttack;
	bool	m_bBuild;

	int nAnimationCnt;
	int nAnimationMinNum;
	int m_nEffectIdx;

protected:
	COMMAND_VECTOR_LIST		m_commandList;
	STATIC_UI_IMAGE_VECTOR_LIST	m_effectList;
	DWORD					m_dwAttackTime;

	float	m_fAttackAnimDivide;
	float	m_fMoveAnimDivide;

};