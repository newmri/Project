#pragma once
#include "Scene.h"

class CSinglePlay :
	public CScene
{
public:
	// Inherited via CScene
	virtual void Init() override;
	virtual SCENE_ID Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	CSinglePlay();
	virtual ~CSinglePlay();
};

