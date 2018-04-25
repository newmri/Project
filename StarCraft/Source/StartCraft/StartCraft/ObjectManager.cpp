#include "stdafx.h"
#include "Obj.h"

CObjectManager*	CObjectManager::m_pInstance = nullptr;

CObj * CObjectManager::GetPlayer()
{
	if(0 != m_objList[OBJ_ID::PLAYER].size()) return m_objList[OBJ_ID::PLAYER].front();

	return nullptr;
}



void CObjectManager::AddObject(CObj* pObj, OBJ_ID eID)
{
	m_objList[eID].push_back(pObj);
}

void CObjectManager::Update()
{
	for (int i = 0; i < OBJ_ID::OBJ_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			if ((*it_begin)->Update()){

				SafeDelete(*it_begin);
				it_begin = m_objList[i].erase(it_begin);
			}
			else it_begin++;
		}

	}
}

void CObjectManager::LateUpdate()
{
	for (int i = 0; i < OBJ_ID::OBJ_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->LateUpdate();
			it_begin++;
		}

	}
}

void CObjectManager::Render()
{
	for (int i = 0; i < OBJ_ID::OBJ_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			(*it_begin)->RenderCollsionBox();
			(*it_begin)->Render();
			it_begin++;
		}
	}
}

void CObjectManager::Release()
{
	for (int i = 0; i < OBJ_ID::OBJ_END; ++i){
		for_each(m_objList[i].begin(), m_objList[i].end(),
			[](auto& obj)
		{
			if (obj)
			{
				delete obj;
				obj = nullptr;
			}
		});
		m_objList[i].clear();
	}

	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CObjectManager::ReSet()
{
	for (int i = 0; i < OBJ_ID::OBJ_END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_OBJ_END = m_objList[i].end();
		for (; it_begin != it_OBJ_END;) {
			SafeDelete(*it_begin);
			it_begin = m_objList[i].erase(it_begin);

		}

	}

}
