#pragma once

#include "Obj.h"

class CPlayer : public CObj
{
public:

	// Obj을(를) 통해 상속됨
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