#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
	m_tInfo.ePortraitId = PORTRAIT::PORTRAIT_END;
}


CTile::~CTile()
{
	Release();
}

void CTile::Init()
{
	m_eId = MOVABLE;

	m_bIsUI = true;

	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(TILE_IMAGE);
	m_tImageInfo = new IMAGE_INFO[p->nImageNum];
	memcpy(m_tImageInfo, p, sizeof(IMAGE_INFO) * p->nImageNum);

	m_tInfo.eOwnerId = NEUTRAL;
}

void CTile::LateInit()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tImageInfo[m_eId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tImageInfo[m_eId].nImageH);
}

int CTile::Update()
{
	CObj::LateInit();
	return 0;
}

void CTile::LateUpdate()
{
}

void CTile::Render()
{
	if (MOVABLE == m_eId) {
	if(!TILEMANAGER->IsRenderUnMovableTileOnly())
	BITMAPMANAGER->GetImage()[m_tImageInfo[m_eId].szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
	static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
	static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
	m_tImageInfo[m_eId].nImageW,
	m_tImageInfo[m_eId].nImageH,
	0,
	0,
	m_tImageInfo[m_eId].nImageW,
	m_tImageInfo[m_eId].nImageH, RGB(255, 255, 255));
	}

	else
		BITMAPMANAGER->GetImage()[m_tImageInfo[m_eId].szName]->TransparentBlt(RENDERMANAGER->GetMemDC(),
			static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
			static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
			m_tImageInfo[m_eId].nImageW,
			m_tImageInfo[m_eId].nImageH,
			0,
			0,
			m_tImageInfo[m_eId].nImageW,
			m_tImageInfo[m_eId].nImageH, RGB(0, 0, 0));

}

void CTile::Release()
{
	SafeDelete(m_tImageInfo);
}
