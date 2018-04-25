#pragma once

// �߻� ���丮 ����
// ��ü �����ÿ� ���ݵǴ� ������ ������� �߻�ȭ ��Ų ������ ����.
// ��ü ������ ���� ������ ���� (���� ����)

class CObj;

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

	static CObj* CreateObj(float x, float y, float speed)
	{
		CObj* pObj = new T;
		pObj->Init();
		pObj->SetPos(x, y);
		pObj->SetSpeed(speed);

		return pObj;
	}
};