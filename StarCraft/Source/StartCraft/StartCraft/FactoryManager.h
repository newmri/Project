#pragma once

// 추상 팩토리 패턴
// 객체 생성시에 동반되는 동일한 문장들을 추상화 시킨 디자인 패턴.
// 객체 생성에 대한 디자인 패턴 (구조 설계)

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