#pragma once
#include "Scene.h"
class CStage1 :
	public CScene
{
public:
	// Inherited via CScene
	virtual void Initialize() override;
	virtual SCENE_ID Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	CStage1();
	virtual ~CStage1();
};

