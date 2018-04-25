#pragma once
#include "Scene.h"
class CStage2 :
	public CScene
{
public:
	CStage2();
	virtual ~CStage2();

	// Inherited via CScene
	virtual void Initialize() override;
	virtual SCENE_ID Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

