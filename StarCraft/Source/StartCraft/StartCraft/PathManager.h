#pragma once

class CPathManager
{
public:
	void Init();
	void Release();

public:

	void init_astar();
	bool is_available_grid(int x, int y);
	node_t* is_open(INTPOINT pos);
	node_t* is_closed(INTPOINT pos);
	void push_into_stack(node_t* node);
	node_t* pop_from_stack();
	void make_sort(node_t *old);
	void insert_node(node_t* present);
	void extend_child_node(node_t* node, int x, int y, INTPOINT tDest, int cur_direct);
	char make_child(node_t* node, INTPOINT tDest);
	node_t* FindPath(INTPOINT tSrc, INTPOINT tDest);




public:
	static CPathManager* GetInstance()
	{
		if (m_pInstance == nullptr) m_pInstance = new CPathManager;
		return m_pInstance;
	}


private:
	CPathManager() = default;
	~CPathManager() = default;
	CPathManager(const CPathManager&) = delete;
	void operator=(const CPathManager&) = delete;

private:
	static CPathManager* m_pInstance;


};