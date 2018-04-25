#pragma once
class Obj
{
public:
	Obj();
	virtual void Init() = 0;
	virtual void LateInit();
	virtual int Update()=0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Realease() = 0;
	bool NoOut();
	void RenderCollsionBox();

public:
	const INFO& GetInfo() const { return m_info; }
	const RECT& GetRect() const { return m_rect; }
	const STAT& GetStat() const { return m_stat; }

public:
	void SetDead() { is_dead = true; }

	void SetRect();
	void SetPos(float x, float y) { m_info.m_x = x, m_info.m_y = y; }
	void SetSpeed(float speed) { m_info.m_speed = speed; }

	void SetStat(float fHp, float fAtk);
	void SetDegre(float degre) { m_info.m_degree = degre; }

	void SetDamage(const float& damage) { m_stat.m_cHp -= damage; if (m_stat.m_cHp <= 0) is_dead = true; }
	void SetImageName(char* str) { strcpy_s(m_imageName, IMAGE_NAME_LEN, str); }
	~Obj();

protected:
	INFO m_info;
	STAT m_stat;
	RECT m_rect;
	bool wall_Collide = false;
	bool is_dead = false;

	bool m_bIsInit = false;

	char m_imageName[IMAGE_NAME_LEN];

};

