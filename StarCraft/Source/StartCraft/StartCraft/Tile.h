#pragma once
#include "Obj.h"

class CTile :
	public CObj
{

public:
	// Inherited via CObj
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	CTile();
	virtual ~CTile();

private:
	TILE_ID m_eId;
};

