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
	void Undo();

public:
	void SwapRenderMode() { m_bRenderUnOnly = !m_bRenderUnOnly; }

public:
	bool IsRenderUnMovableTileOnly() { return m_bRenderUnOnly; }

public:
	const INTPOINT& GetTileNum() { return m_nTileNum; }
	INTPOINT GetIndex(const POINT& pos);

public:
	CObj * SelectTile(int nIdx);

public:
	void SaveData();
	void LoadData();


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
	list<int>			m_listLog;

	INTPOINT				m_nTileNum;

private:
	bool				m_bRenderUnOnly;
};

