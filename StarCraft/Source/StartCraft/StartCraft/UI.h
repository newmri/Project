#pragma once

#include "Obj.h"

class CUI : public CObj
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
	void SetMouseOver();
	void SetIdle();

public:
	void ChangeAnimation(UI_ID eId);

public:
	void UpdateUIRect();

public:
	CUI();
	virtual ~CUI();

protected:
	UI_ID		m_eCurrId;
	OBJ_ID		m_eId;
};