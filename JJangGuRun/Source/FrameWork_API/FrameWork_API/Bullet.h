#pragma once
#include "Obj.h"

class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Init();
	virtual void LateInit();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

private:
	DWORD	m_dwAnimTIme;
	int		m_AnimNum;

	int		m_PoopType;
};

