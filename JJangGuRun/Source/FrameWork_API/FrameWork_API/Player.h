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
	virtual void Release() override;


public:
	bool IsCheatOn() { return bIsCheatOn; }

	void Fall();
	void Move();
	void Jump();
	void OffSet();
	void SetPlayerRect();


public:
	bool IsJumpOn();

public:
	CPlayer();
	~CPlayer();

private:
	bool IsWallJumpOn;
	bool bIsStayJumpOn;
	bool bIsCheatOn;

};