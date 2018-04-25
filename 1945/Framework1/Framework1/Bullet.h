#pragma once
#include "Obj.h"

class Bullet : public Obj
{
public:
	// Inherited via Obj
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;
	virtual bool NoOut();

	void SetMissileRect();

};