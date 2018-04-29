#pragma once
#include "Obj.h"

class CTile :
	public CObj
{

public:
	// Inherited via CObj
	virtual void Init() override;
	virtual void LateInit();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	const TILE_ID& GetId() { return m_eId; }
	void SetId(TILE_ID eId) { m_eId = eId; }


public:
	void SwapTile() { m_eId = static_cast<TILE_ID>((m_eId + 1) % TILE_END); }

public:
	CTile();
	virtual ~CTile();

private:
	TILE_ID		m_eId;

private:
	IMAGE_INFO* m_tImageInfo;
};

