#pragma once


class CScene
{
public:
	virtual void Initialize() = 0;
	virtual SCENE_ID Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	void CreateNormalEnemy();
	void CreateBoss(char* name);

	void MoveToBoss() { m_nY = 0; }
public:
	CScene() = default;
	virtual ~CScene() = default;

protected:
	float m_nY;
	int m_nProcessPercent;
	float m_nImageHeight;
	DWORD m_createNormalEnemyTime;
	bool m_bBossIsCreated;
	DWORD m_nextStageTime;
};

