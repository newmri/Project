#pragma once

#include "Scene.h"

class CEditor : public CScene
{
public:

	// Obj을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual SCENE::SCENE_ID Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;


public:
	CEditor();
	virtual ~CEditor();

private:
	IMAGE_INFO*	m_tImageInfo;

};