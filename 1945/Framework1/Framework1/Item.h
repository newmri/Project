#pragma once
#include"Obj.h"

class Item :public Obj
{
public:
	Item();
	~Item();
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;

	void SetItemRect();
	int GetItem() { is_dead = true; return iIAM; }
private:
	DWORD m_time;
	DWORD m_animationTime;
	int m_animationCnt;
	int iIAM;
	int Dir[4] = { 45,135,225,315 };
};

