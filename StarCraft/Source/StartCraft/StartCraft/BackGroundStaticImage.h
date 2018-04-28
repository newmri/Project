#pragma once
#include "StaticImage.h"

class CBackGroundStaticImage : public CStaticImage
{
public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetId(STATIC_IMAGE_ID eId) { m_eId = eId; }

public:
	CBackGroundStaticImage();
	virtual ~CBackGroundStaticImage();

private:
	STATIC_IMAGE_ID		m_eId;

private:
	STATIC_IMAGE_INFO	m_tImageInfo;

};

