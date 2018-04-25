#pragma once
#include "Obj.h"

class CTrap :
	public CObj
{
public:
	CTrap();
	virtual ~CTrap();

public:
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

public:
	POINT* GetPoint() { return m_pPoint; }
	void SetPoint(POINT pPoint[]);

private:
	void UpdateLine();

private:
	POINT m_pPoint[3];
};

