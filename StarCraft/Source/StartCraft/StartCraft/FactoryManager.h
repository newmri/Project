#pragma once

// 추상 팩토리 패턴
// 객체 생성시에 동반되는 동일한 문장들을 추상화 시킨 디자인 패턴.
// 객체 생성에 대한 디자인 패턴 (구조 설계)

class CObj;
class CScene;
class CUI;

template <typename T>
class CFactoryManager
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Init();

		return pObj;
	}

	static CObj* CreateObj(FLOATPOINT tPos)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetPos(tPos);

		return pObj;
	}

	static CObj* CreateObj(OWNER_ID eId, UNIT_SELECT eUnitSize, FLOATPOINT tPos)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetOwnerId(eId);
		pObj->SetSize(eUnitSize);
		pObj->SetPos(tPos);

		return pObj;
	}

	static CObj* CreateObj(OWNER_ID eId, OBJ_ID eObjId, PORTRAIT::ID ePortId, UNIT::LARGE_WIRE::LARGE_WIRE_ID eWireLarge,
		UNIT_SELECT eUnitSize, FLOATPOINT tPos, int hp)
	{
		CObj* pObj = new T;
		pObj->SetObjId(eObjId);
		pObj->Init();
		pObj->SetOwnerId(eId);
		pObj->SetPortraitId(ePortId);
		pObj->SetLargeWireId(eWireLarge);

		pObj->SetSize(eUnitSize);
		pObj->SetPos(tPos);
		pObj->SetHP(hp);

		return pObj;
	}

	static CObj* CreateObj(OWNER_ID eId, OBJ_ID eObjId, PORTRAIT::ID ePortId, UNIT::LARGE_WIRE::LARGE_WIRE_ID eWireLarge,
		UNIT::SMALL_WIRE::SMALL_WIRE_ID eWireSmall,
		UNIT_SELECT eUnitSize, FLOATPOINT tPos, float hp)
	{
		CObj* pObj = new T;
		pObj->SetObjId(eObjId);
		pObj->Init();
		pObj->SetOwnerId(eId);
		pObj->SetPortraitId(ePortId);
		pObj->SetLargeWireId(eWireLarge);
		pObj->SetSmallWireId(eWireSmall);

		pObj->SetSize(eUnitSize);
		pObj->SetPos(tPos);
		pObj->SetHP(hp);


		return pObj;
	}

	static CObj* CreateTileObj(OWNER_ID eId, UNIT::LARGE_WIRE::LARGE_WIRE_ID eWireLarge,
		UNIT_SELECT eUnitSize, FLOATPOINT tPos, float hp)
	{
		CObj* pObj = new T;
		
		pObj->Init();
		pObj->SetOwnerId(eId);
		pObj->SetLargeWireId(eWireLarge);

		pObj->SetSize(eUnitSize);
		pObj->SetPos(tPos);
		pObj->SetHP(hp);


		return pObj;
	}



	static CScene* CreateScene(FLOATPOINT tPos)
	{
		CScene* pObj = new T;
		pObj->Init();
		pObj->SetPos(tPos);

		return pObj;
	}

	static CUI* CreateUI(FLOATPOINT tPos)
	{
		CUI* pObj = new T;
		pObj->Init();
		pObj->SetPos(tPos);
		return pObj;
	}

	static CObj* CreateObj(FLOATPOINT tPos, float speed)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetPos(tPos);
		pObj->SetSpeed(speed);

		return pObj;
	}
};