#include "stdafx.h"
#include "Mine.h"
#include "Tile.h"

void CMine::Init()
{
	IMAGE_INFO* p = BITMAPMANAGER->GetImageInfo(MINE_IMAGE);
	m_tImageInfo = new IMAGE_INFO[p->nImageNum];
	memcpy(m_tImageInfo, p, sizeof(IMAGE_INFO) * p->nImageNum);

	m_tInfo.eOwnerId = NEUTRAL;
	m_eId = 0;
}

void CMine::LateInit()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tImageInfo[m_eId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tImageInfo[m_eId].nImageH);

	// Swap Tail
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	m_tSelectRect.left = m_tRect.left + fScrollX;
	m_tSelectRect.top = (m_tRect.top + fScrollY);
	m_tSelectRect.right = m_tSelectRect.left + TILE_SIZE * 2;
	m_tSelectRect.bottom = m_tSelectRect.top + TILE_SIZE;

	INTPOINT pos;
	pos.x = m_tSelectRect.left;
	pos.y = m_tSelectRect.top;

	m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);
	bool bUnmovable = true;
	for (int posY = m_tSelectRect.top; posY < m_tSelectRect.bottom; posY += TILE_SIZE) {

		for (int posX = m_tSelectRect.left; posX < m_tSelectRect.right; posX += TILE_SIZE) {

			int x = (posX - static_cast<int>(fScrollX)) / TILE_SIZE;
			int y = (posY - static_cast<int>(fScrollY)) / TILE_SIZE;
			int k = TILEMANAGER->GetTileNum().x;
			int nIdx = x + TILEMANAGER->GetTileNum().x * y;

			CObj* pTile = TILEMANAGER->SelectTile(nIdx);

			if (nullptr == pTile) return;
			if(bUnmovable) dynamic_cast<CTile*>(pTile)->SetTileUnMovable();
			else dynamic_cast<CTile*>(pTile)->SetClickable();
		}
		bUnmovable = false;
	}
}

int CMine::Update()
{
	CObj::LateInit();
	return 0;
}

void CMine::LateUpdate()
{
}

void CMine::Render()
{

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

void CMine::Release()
{
	SafeDelete(m_tImageInfo);
}

CMine::CMine()
{
}

CMine::~CMine()
{
	Release();
}
