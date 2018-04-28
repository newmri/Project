#pragma once

class CObj;

class CTileManager
{
public:
	void Init();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	const POINT& GetTileSize() { return m_nTileSize; }

public:
	static CTileManager* GetInstance()
	{
		if (nullptr == m_pInstance) m_pInstance = new CTileManager;
		return m_pInstance;
	}

private:
	CTileManager() = default;
	~CTileManager() = default;

private:
	static CTileManager* m_pInstance;

private:
	vector<CObj*>		m_vecTile;
	POINT				m_nTileSize;
};

