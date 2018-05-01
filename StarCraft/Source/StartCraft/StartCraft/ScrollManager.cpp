#include "stdafx.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;

void CScrollManager::Init()
{
	m_fScrollX = 0;
	m_fScrollY = 0;

	int nWinX = RENDERMANAGER->GetWindowSize().x;
	int nWinY = RENDERMANAGER->GetWindowSize().y;
	int nTileX = TILEMANAGER->GetTileNum().x;
	int nTileY = TILEMANAGER->GetTileNum().y;

	m_tEndPos.x = nWinX - TILE_SIZE * nTileX;
	m_tEndPos.y = nWinY - TILE_SIZE * nTileY;
}

void CScrollManager::Update()
{
	if (m_fScrollX >= 0) m_fScrollX = 0;
	if (m_fScrollY >= 0) m_fScrollY = 0;

	int nWinX = RENDERMANAGER->GetWindowSize().x;
	int nWinY = RENDERMANAGER->GetWindowSize().y;
	int nTileX = TILEMANAGER->GetTileNum().x;
	int nTileY = TILEMANAGER->GetTileNum().y;


	if (nWinX - TILE_SIZE * nTileX >= static_cast<int>(m_fScrollX))
		m_fScrollX = float(nWinX - TILE_SIZE * nTileX);
	if (nWinY - TILE_SIZE * nTileY >= static_cast<int>(m_fScrollY))
		m_fScrollY = float(nWinY - TILE_SIZE * nTileY);

}

void CScrollManager::ReSet()
{
	m_fScrollX = 0;
	m_fScrollY = 0;
}

void CScrollManager::SetScrollXY(float fPercentX, float fPercentY)
{
	m_fScrollX = m_tEndPos.x * fPercentX;
	m_fScrollY = m_tEndPos.y * fPercentY;
}
