#pragma once

// �߻� ���丮 ����
// ��ü �����ÿ� ���ݵǴ� ������ ������� �߻�ȭ ��Ų ������ ����.
// ��ü ������ ���� ������ ���� (���� ����)

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

	static CObj* CreateObj(float x, float y)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetPos(x, y);

		return pObj;
	}

	static CObj* CreateObj(OWNER_ID eId, UNIT_SELECT eUnitSize, float x, float y)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetOwnerId(eId);
		pObj->SetSize(eUnitSize);
		pObj->SetPos(x, y);

		return pObj;
	}

	static CObj* CreateObj(OWNER_ID eId, OBJ_ID eObjId, PORTRAIT::ID ePortId, UNIT_SELECT eUnitSize, float x, float y)
	{
		CObj* pObj = new T;
		pObj->SetObjId(eObjId);
		pObj->Init();
		pObj->SetOwnerId(eId);
		pObj->SetPortraitId(ePortId);
		pObj->SetSize(eUnitSize);
		pObj->SetPos(x, y);

		return pObj;
	}

	static CScene* CreateScene(float x, float y)
	{
		CScene* pObj = new T;
		pObj->Init();
		pObj->SetPos(x, y);

		return pObj;
	}

	static CUI* CreateUI(float x, float y)
	{
		CUI* pObj = new T;
		pObj->Init();
		pObj->SetPos(x, y);
		return pObj;
	}

	static CObj* CreateObj(float x, float y, float speed)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetPos(x, y);
		pObj->SetSpeed(speed);

		return pObj;
	}
};