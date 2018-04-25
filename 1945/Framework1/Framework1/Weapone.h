#pragma once
#include"Obj.h"
class Weapone :public Obj
{
public:
	Weapone();
	~Weapone();

	// Obj을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;



	void SetBULLETList(OBJLIST* lis) { m_bulletlist = lis; }

	void SetPlayerLevel(int level) { my_level = level; }



private:

	int my_level;
	DWORD m_time;



	OBJLIST* m_bulletlist;
	OBJLIST* m_skillist;

};

