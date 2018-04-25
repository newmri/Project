#pragma once
#include "Scene.h"
class CMainMenu :
	public CScene
{
public:
	CMainMenu();
	virtual ~CMainMenu();

	// Inherited via CScene
	virtual void Initialize() override;
	virtual SCENE_ID Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

