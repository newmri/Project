#pragma once
#include"Obj.h"

static int score = 0;

class Player :public Obj
{
public:
	Player();
	~Player();

	// Obj¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Realease() override;


	void RenderShiled();
	int GetLevel() { return my_gun; };

	//////////////////////¿œπ› √—/////////////////////////////////
	void SetWEAPONEList(OBJLIST* lis) { m_weaponelist = lis; }
	void SetNOMALList(OBJLIST* lis) { m_nomallist = lis; }


	///////////////////πÃªÁ¿œ/////////////////////////
	void SetMISSILEist(OBJLIST* lis) { m_missilelist = lis; }
	void SetMONSTERist(OBJLIST* lis) { m_monsterlist = lis; }


	//////////////////Ω∫≈≥/////////////////////////
	void SetSKILLList(OBJLIST* lis) { m_skilllist = lis; }
	void SetSKILLBULLETList(OBJLIST* lis) { m_skillbulletlist = lis; }
	///////////////////////////////////////////////////∆¯≈∫//////////
	void SetBOMBList(OBJLIST* lis) { m_bomblist = lis; }


	void SetItemList(OBJLIST* lis) { m_itemlist = lis; }

	void SetItem(int a);

	void SetPlayerRect();

	void SetLevelMax() { my_gun = 5; }
	Obj* CreateMISSILE(int x, int y);

	Obj * CreateSTRONG(int x, int y);


private:
	OBJLIST * m_weaponelist;
	OBJLIST* m_nomallist;

	OBJLIST* m_missilelist;
	OBJLIST* m_monsterlist;

	OBJLIST* m_skilllist;
	OBJLIST* m_skillbulletlist;

	OBJLIST* m_bomblist;
	OBJLIST* m_itemlist;

	int target_dis;
	int target_x;
	int target_y;

	Obj* m_weapone;
	Obj* m_missile;
	Obj* m_skill;

	Obj* m_bomb;


	bool m_key_up = true;

	bool m_Space_up = true;


	///∑π∫ß, ∆¯≈∫∞πºˆ//
	int my_gun;
	int my_bomb;


	DWORD missle_speed;

	DWORD skill_time;

	DWORD bomb_time;


	bool savior = false;

private:
	int m_moveHCnt;
	int m_moveVCnt;

	bool m_IsMoving[MOVE_END];

private:
	DWORD m_animationTime;
	int m_tbImageW;
	int m_tbImageH;
	int m_shiledW;
	int m_shiledH;


};