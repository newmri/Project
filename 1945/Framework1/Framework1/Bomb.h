#pragma once
#include"Obj.h"

class Bomb:public Obj
{
public:
	Bomb();
	~Bomb();
	// Obj��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;

private:
	DWORD m_time;

};

