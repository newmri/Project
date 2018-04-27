#pragma once
#include "UI.h"
class CButton : public CUI
{
public:
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release() override;

public:
	void SetId(BUTTON_ID eId) { m_eId = eId; }

public:
	CButton();
	virtual ~CButton();

private:
	BUTTON_ID	m_eId;
};

