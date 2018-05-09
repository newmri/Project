#pragma once
#include "Unit.h"

class CGhost : public CUnit
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
	void UpdateNuclear();

public:
	void SetNuclear(POINT tMousePos);

public:
	virtual bool CheckCommand(POINT tMousePos);

public:
	virtual void RenderUI();

public:
	virtual void Move();
	virtual void Attack();

private:
	STATIC_UI_IMAGE_VECTOR_LIST	m_SkillList;

private:
	bool m_bNuclearOn;
	bool m_bNuclearLaunchOn;
	int	 m_nNuclearIdx;


	float m_fNuclearArea;
	float m_fNuclearDmg;

private:
	INTPOINT m_tNuclearPos;
	INTPOINT m_tNuclearTargetPos;
	DWORD	 m_dwNuclearLaunchTime;
};