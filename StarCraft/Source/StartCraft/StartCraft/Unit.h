#pragma once
#include "Obj.h"

class CUnit : public CObj
{
public:

	// Obj을(를) 통해 상속됨
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

public:
	void Move();
	void Attack();

public:
	void UpdateRect();

private:
	UNIT::STATE_ID m_eCurrId;

private:
	int m_nAttackAnim;
	int m_nAttackCnt;
	int m_nMaxAttackCnt;

	CObj* m_pControlTarget;

	bool m_bIsRetunning;

};