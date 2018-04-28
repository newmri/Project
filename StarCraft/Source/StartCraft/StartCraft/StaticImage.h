#pragma once
#include "Obj.h"

class CStaticImage : public CObj
{
public:
	virtual void Init() = 0;
	virtual void LateInit() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	void SetId(STATIC_IMAGE_ID eId) { m_eId = eId; }

public:
	CStaticImage();
	virtual ~CStaticImage();

private:
	STATIC_IMAGE_ID		m_eId;

private:
	STATIC_IMAGE_INFO	m_tImageInfo;

};

