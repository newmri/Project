#include "stdafx.h"
#include "Tile.h"

CTileManager* CTileManager::m_pInstance = nullptr;


void CTileManager::Init()
{
	float x = 0.f, y = 0.f;
	m_bRenderUnOnly = true;
	IMAGE_INFO* imageInfo = BITMAPMANAGER->GetImageInfo(MAIN_MAP_IMAGE);

	SCENEMANAGER->SetMapSize(imageInfo->nImageW, imageInfo->nImageH);

	m_nTileNum.x = imageInfo->nImageW / TILE_SIZE;
	m_nTileNum.y = imageInfo->nImageH / TILE_SIZE;
	m_vecTile.reserve(static_cast<size_t>(m_nTileNum.x * m_nTileNum.y));

	for (int i = 0; i < m_nTileNum.y; ++i) {
		for (int j = 0; j < m_nTileNum.x; ++j) {
			x = static_cast<float>(TILE_SIZE * j);
			y = static_cast<float>(TILE_SIZE * i);

			m_vecTile.push_back(CFactoryManager<CTile>::CreateObj(NEUTRAL, UNIT_SELECT1, x, y));
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

	for (int i = nCullY; i < nCullY + iCullEndY + 2; ++i) {
		for (int j = nCullX; j < nCullX + iCullEndX + 2; ++j) {
			int iIndex = j + (m_nTileNum.x * i);

			if (0 > iIndex || m_vecTile.size() <= static_cast<size_t>(iIndex)) continue;

			m_vecTile[iIndex]->Render();
		}
	}

}

void CTileManager::Release()
{
}

void CTileManager::Undo()
{
	if (m_listLog.empty()) return;

	int idx = m_listLog.back();
	dynamic_cast<CTile*>(m_vecTile[idx])->SwapTile();
	m_listLog.pop_back();

}

CObj* CTileManager::SelectTile(int nIdx)
{
	if (m_vecTile.empty()) return nullptr;

	if (0 > nIdx || m_vecTile.size() <= static_cast<size_t>(nIdx)) return nullptr;

	m_listLog.push_back(nIdx);

	return m_vecTile[nIdx];
}

void CTileManager::SaveData()
{
	HANDLE hFile = CreateFile(L"Data/Tile.dat", GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile) return;


	DWORD dwByte = 0;
	TILE_ID eTileId;

	for (auto& pTile : m_vecTile) {
		eTileId = dynamic_cast<CTile*>(pTile)->GetId();
		WriteFile(hFile, &eTileId, sizeof(TILE_ID), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	hFile = CreateFile(L"Data/TileLog.dat", GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	int nLog = 0;

	dwByte = 0;

	for (auto& pLog : m_listLog) {
		nLog = pLog;
		WriteFile(hFile, &nLog, sizeof(int), &dwByte, nullptr);
	}
}

void CTileManager::LoadData()
{
	HANDLE hFile = CreateFile(L"Data/Tile.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile) return;


	DWORD dwByte = 0;
	TILE_ID eTileId;

	int nCnt = 0;

	while (true) {
		ReadFile(hFile, &eTileId, sizeof(TILE_ID), &dwByte, nullptr);

		if (0 == dwByte) break;

		dynamic_cast<CTile*>(m_vecTile[nCnt++])->SetId(eTileId);
	}

	CloseHandle(hFile);

	hFile = CreateFile(L"Data/TileLog.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	int nLog = 0;

	dwByte = 0;

	while (true) {
		ReadFile(hFile, &nLog, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte) break;

		m_listLog.push_back(nLog);
	}

}
