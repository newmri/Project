#pragma once
#include "Obj.h"

class CMine :
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
	CMine();
	virtual ~CMine();

private:
	IMAGE_INFO* m_tImageInfo;

	int m_eId;
};

