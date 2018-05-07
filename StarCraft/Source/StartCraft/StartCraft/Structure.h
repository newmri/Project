#pragma once
#include "Obj.h"

class CStructure : public CObj
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
	void SetState(STRUCTURE_STATE_ID eId) { m_eCurrId = eId; }

public:
	void RenderUI();

public:
	void UpdateRect();

public:
	bool CheckBuildUnit(POINT tMousePos);

public:
	void BuildUnit();

private:
	STRUCTURE_STATE_ID m_eCurrId;

	STATIC_UI_IMAGE_INFO m_unitQueue;
	STATIC_UI_IMAGE_INFO m_unitProgress[2];
	BUILD_VECTOR_LIST			m_BuildList[OBJ_ID::CURSOR];
	BUILD_LIST					m_BuildQueueList;

private:
	DWORD dwUnitBuildTime;

private:
	float fUnitBuildReMainPercent;
};