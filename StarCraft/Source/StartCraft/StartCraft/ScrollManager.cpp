#include "stdafx.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;

void CScrollManager::Init()
{
	m_fScrollX = 0;
	m_fScrollY = 0;

}

void CScrollManager::Update()
{
	if (m_fScrollX >= 0) m_fScrollX = 0;
	if (m_fScrollY >= 0) m_fScrollY = 0;

	int nWinX = RENDERMANAGER->GetWindowSize().x;
	int nWinY = RENDERMANAGER->GetWindowSize().x;
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
