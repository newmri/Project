#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Init()
{
	m_eId = MOVABLE;

	m_bIsUI = true;

	m_tAnimationInfo = new ANIMATION_INFO[TILE_END];
	for (int i = 0; i < TILE_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(ANIMATION_INFO));

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetMapInfo(TILE);

	// Set Animation Name
	for (int i = 0; i < TILE_END; ++i) {

		m_tAnimationInfo[i].tName = new char*[pAnim[i].nAnimationNum];
		ZeroMemory(m_tAnimationInfo[i].tName, pAnim[i].nAnimationNum);

		for (int j = 0; j < pAnim[i].nAnimationNum; ++j) {

			m_tAnimationInfo[i].tName[j] = new char[STR_LEN];
			strcpy_s(m_tAnimationInfo[i].tName[j], strlen(m_tAnimationInfo[i].tName[j]), pAnim[i].tName[j]);

			m_tAnimationInfo[i].nAnimationNum = pAnim[i].nAnimationNum;
			m_tAnimationInfo[i].nImageW = pAnim[i].nImageW;
			m_tAnimationInfo[i].nImageH = pAnim[i].nImageH;
			m_tAnimationInfo[i].dwAnimationTime = GetTickCount();
			m_tAnimationInfo[i].nCnt = 0;

		}
		if (1 == pAnim[i].nAnimationNum) break;
	}
}

void CTile::LateInit()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + m_tAnimationInfo[m_eId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + m_tAnimationInfo[m_eId].nImageH);
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
	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eId].tName[m_tAnimationInfo[m_eId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
	static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
	static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
	m_tAnimationInfo[m_eId].nImageW,
	m_tAnimationInfo[m_eId].nImageH,
	0,
	0,
	m_tAnimationInfo[m_eId].nImageW,
	m_tAnimationInfo[m_eId].nImageH, RGB(255, 255, 255));
	}

	else
	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eId].tName[m_tAnimationInfo[m_eId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
	static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
	static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
	m_tAnimationInfo[m_eId].nImageW,
	m_tAnimationInfo[m_eId].nImageH,
	0,
	0,
	m_tAnimationInfo[m_eId].nImageW,
	m_tAnimationInfo[m_eId].nImageH, RGB(0, 0, 0));
}

void CTile::Release()
{
}
