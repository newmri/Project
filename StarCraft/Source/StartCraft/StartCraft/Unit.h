#pragma once
#include "Obj.h"

class CUnit : public CObj
{
public:

	// Obj��(��) ���� ��ӵ�
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

public:
	void UpdateRect();

private:
	UNIT::STATE_ID m_eCurrId;
};