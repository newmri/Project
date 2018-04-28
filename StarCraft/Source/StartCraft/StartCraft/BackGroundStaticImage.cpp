#include "stdafx.h"
#include "BackGroundStaticImage.h"

void CBackGroundStaticImage::Init()
{
}

void CBackGroundStaticImage::LateInit()
{
	STATIC_IMAGE_INFO p = BITMAPMANAGER->GetStaticImageInfo(m_eId);

	strcpy_s(m_tImageInfo.szName, STR_LEN, p.szName);
	m_tImageInfo.nImageW = p.nImageW;
	m_tImageInfo.nImageH = p.nImageH;

	m_tRect.left = static_cast<LONG>(m_tInfo.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + m_tImageInfo.nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + m_tImageInfo.nImageH);
}

int CBackGroundStaticImage::Update()
{
	CObj::LateInit();

	return 0;
}

void CBackGroundStaticImage::LateUpdate()
{
}

void CBackGroundStaticImage::Render()
{
	/*BITMAPMANAGER->GetImage()[m_tImageInfo.szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_tRect.left),
		static_cast<int>(m_tRect.top),
		RENDERMANAGER->GetWindowSize().x,
		m_tImageInfo.nImageH,
		0,
		0,
		m_tImageInfo.nImageW,
		m_tImageInfo.nImageH, RGB(0, 0, 0));
*/
	StretchBlt(RENDERMANAGER->GetMemDC(), 0, 0, RENDERMANAGER->GetWindowSize().x,
		RENDERMANAGER->GetWindowSize().y,
		BITMAPMANAGER->GetImage()[m_tImageInfo.szName]->GetDC(), 0, 0,
		m_tImageInfo.nImageW, m_tImageInfo.nImageH, SRCCOPY);
}

void CBackGroundStaticImage::Release()
{
}

CBackGroundStaticImage::CBackGroundStaticImage()
{
}

CBackGroundStaticImage::~CBackGroundStaticImage()
{
}
