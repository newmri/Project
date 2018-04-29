#pragma once

#include "Scene.h"

class CMainMenu :
	public CScene
{
public:
	CMainMenu();
	virtual ~CMainMenu();

	// Inherited via CScene
	virtual void Init() override;
	virtual void LateInit();
	virtual SCENE::SCENE_ID Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	IMAGE_INFO * m_tImageInfo;
};

