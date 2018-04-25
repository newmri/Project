#pragma once

#include "Obj.h"

class CSinglePlayUI : public CObj
{
public:

	// Obj��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;


public:
	CSinglePlayUI();
	virtual ~CSinglePlayUI();

private:
	UI_ID m_eCurrId;
};