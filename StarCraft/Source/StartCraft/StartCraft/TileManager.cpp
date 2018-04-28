#include "stdafx.h"
#include "Tile.h"

CTileManager* CTileManager::m_pInstance = nullptr;


void CTileManager::Init()
{
	float x = 0.f, y = 0.f;

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetMapInfo(BEGINNER_MAP);
	SCENEMANAGER->SetMapSize(pAnim[MAIN_MAP].nImageW, pAnim[MAIN_MAP].nImageH);


	m_nTileSize.x = pAnim[MAIN_MAP].nImageW / TILE_SIZE;
	m_nTileSize.y = pAnim[MAIN_MAP].nImageH / TILE_SIZE;

	for (int i = 0; i < m_nTileSize.y; ++i)
	{
		for (int j = 0; j < m_nTileSize.x; ++j)
		{
			x = static_cast<float>(TILE_SIZE * j);
			y = static_cast<float>(TILE_SIZE * i);

			m_vecTile.push_back(CFactoryManager<CTile>::CreateObj(x, y));
		}
	}
}

void CTileManager::LateInit()
{
	for (auto& d : m_vecTile) d->LateInit();
}

void CTileManager::Update()
{
}

void CTileManager::LateUpdate()
{
}

void CTileManager::Render()
{
	int nScrollX = static_cast<int>(SCROLLMANAGER->GetScrollX());
	int nScrollY = static_cast<int>(SCROLLMANAGER->GetScrollY());

	int nCullX = -nScrollX / TILE_SIZE;
	int nCullY = -nScrollY / TILE_SIZE;

	int iCullEndX = static_cast<int>(RENDERMANAGER->GetWindowSize().x) / TILE_SIZE;
	int iCullEndY = static_cast<int>(RENDERMANAGER->GetWindowSize().y) / TILE_SIZE;

	for (int i = nCullY; i < nCullY + iCullEndY + 2; ++i)
	{
		for (int j = nCullX; j < nCullX + iCullEndX + 2; ++j)
		{
			int iIndex = j + (m_nTileSize.x * i);

			if (0 > iIndex || m_vecTile.size() <= static_cast<size_t>(iIndex)) continue;

			m_vecTile[iIndex]->Render();
		}
	}

}

void CTileManager::Release()
{
}
