#pragma once

#include "Scene.h"

class CExit : public CScene
{
public:

	// Obj��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual SCENE::SCENE_ID Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;


public:
	CExit();
	virtual ~CExit();
};