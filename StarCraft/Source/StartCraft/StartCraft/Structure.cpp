#include "stdafx.h"
#include "Structure.h"
#include "Tile.h"

void CStructure::Init()
{
	m_eCurrId = STRUCTURE_IDLE;
	m_tAnimationInfo = new ANIMATION_INFO[STRUCTURE_STATE_END];
	for (int i = 0; i < STRUCTURE_STATE_END; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(m_tAnimationInfo[i]));
}

void CStructure::LateInit()
{
	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);

	// Set Animation Name
	for (int i = 0; i < STRUCTURE_STATE_END; ++i) {

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

	}

	UpdateRect();

	// Swap Tail
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();


	m_tSelectRect.left = m_tRect.left + fScrollX;
	m_tSelectRect.top = (m_tRect.top + fScrollY) + TILE_SIZE;
	m_tSelectRect.right = m_tRect.right + fScrollX + TILE_SIZE;
	m_tSelectRect.bottom = m_tSelectRect.top + TILE_SIZE * 3;


	for (int posY = m_tSelectRect.top; posY < m_tSelectRect.bottom; posY += TILE_SIZE) {

		for (int posX = m_tSelectRect.left; posX < m_tSelectRect.right; posX += TILE_SIZE) {

			int x = (posX - static_cast<int>(fScrollX)) / TILE_SIZE;
			int y = (posY - static_cast<int>(fScrollY)) / TILE_SIZE;
			int k = TILEMANAGER->GetTileNum().x;
			int nIdx = x + TILEMANAGER->GetTileNum().x * y;

			CObj* pTile = TILEMANAGER->SelectTile(nIdx);

			if (nullptr == pTile) return;

			dynamic_cast<CTile*>(pTile)->SetTileUnMovable();
		}
	}

}

int CStructure::Update()
{
	CObj::LateInit();
	return 0;
}

void CStructure::LateUpdate()
{
}

void CStructure::Render()
{
	if (0 == m_tAnimationInfo[m_eCurrId].nImageW) return;

	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
		static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(0,0,0));
}

void CStructure::Release()
{
}

void CStructure::UpdateRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tAnimationInfo[m_eCurrId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tAnimationInfo[m_eCurrId].nImageH);
}
