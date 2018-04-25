#pragma once

#include "Enum.h"

class CScene
{
public:
	virtual void Init() = 0;
	virtual SCENE_ID Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	CScene() = default;
	virtual ~CScene() = default;

protected:
	int		m_nProcessPercent;
};

