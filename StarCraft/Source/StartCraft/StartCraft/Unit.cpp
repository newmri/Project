#include "stdafx.h"
#include "Unit.h"
#include "Tile.h"
#include "Structure.h"

void CUnit::Init()
{
	m_eCurrId = UNIT::IDLE;

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);
	m_tAnimationInfo = new ANIMATION_INFO[pAnim->nStateNum];
	for (int i = 0; i < pAnim->nStateNum; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(m_tAnimationInfo[i]));

	m_tInfo.fSpeed = TILE_SIZE / 2.f;
	m_bMove = false;
	m_tInfo.fAngle = BOTTOM;
	m_nMaxAttackCnt = 10;

	m_bAttack = false;
	m_tReturnPos.x = -1;

}

void CUnit::LateInit()
{

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);
	// Set Animation Name
	for (int i = 0; i < pAnim->nStateNum; ++i) {
	
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

	m_tSelectRect.left = m_tRect.left + fScrollX + TILE_SIZE;
	m_tSelectRect.top = (m_tRect.top + fScrollY) + TILE_SIZE;
	m_tSelectRect.right = m_tSelectRect.left + TILE_SIZE;
	m_tSelectRect.bottom = m_tSelectRect.top + TILE_SIZE;

	INTPOINT pos;
	pos.x = m_tSelectRect.left;
	pos.y = m_tSelectRect.top;

	m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);

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

	m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 10);
	m_tAnimationInfo[m_eCurrId].nCnt -= 2;

}


void CUnit::Render()
{
	if (0 == m_tAnimationInfo[m_eCurrId].nImageW) return;

	UpdateRect();
	HDC hDC = RENDERMANAGER->GetMemDC();

	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(hDC,
		static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
		static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));



}

void CUnit::Release()
{
}



void CUnit::RenderUI()
{
	
}

void CUnit::Move()
{

}

void CUnit::Attack()
{

}



void CUnit::UpdateRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tAnimationInfo[m_eCurrId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tAnimationInfo[m_eCurrId].nImageH);
}
