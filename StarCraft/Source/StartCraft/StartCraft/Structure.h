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
	void UpdateRect();

private:
	STRUCTURE_STATE_ID m_eCurrId;
};