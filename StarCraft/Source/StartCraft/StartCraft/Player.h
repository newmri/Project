#pragma once

#include "Obj.h"

class CPlayer : public CObj
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
	void SetPlayerRect();

public:
	void Move();
	void Jump();

public:
	CPlayer();
	~CPlayer();


};