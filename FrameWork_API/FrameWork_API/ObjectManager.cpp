#include "stdafx.h"
#include "Obj.h"

CObjectManager*	CObjectManager::m_pInstance = nullptr;

CObj * CObjectManager::GetPlayer()
{
	if(0 != m_objList[OBJTYPE::PLAYER].size()) return m_objList[OBJTYPE::PLAYER].front();

	return nullptr;
}

CObj* CObjectManager::GetTarget(CObj* pSrc, OBJTYPE eID)
{
	if (m_objList[eID].empty()) return nullptr;

	auto iter_begin = m_objList[eID].begin();
	auto iter_end = m_objList[eID].end();

	//CObj* pTarget = *iter_begin;
	//float fDistance = CMathMgr::CalcDistance(pTarget, pSrc);

	//for (auto& pObj : m_ObjLst[eID])
	//{
	//	float fTempDist = CMathMgr::CalcDistance(pObj, pSrc);

	//	if (fTempDist < fDistance)
	//	{
	//		pTarget = pObj;
	//		fDistance = fTempDist;
	//	}
	//}

	//return pTarget;
	return nullptr;
}

void CObjectManager::AddObject(CObj * pObj, OBJTYPE eID)
{
	m_objList[eID].push_back(pObj);
}

void CObjectManager::Update()
{
	for (int i = 0; i < OBJTYPE::END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_end = m_objList[i].end();
		for (; it_begin != it_end;) {
			if ((*it_begin)->Update()){
				if (i == OBJTYPE::PLAYER) {
					SCENEMANAGER->KillPlayer();
				}

				SafeDelete(*it_begin);
				it_begin = m_objList[i].erase(it_begin);
			}
			else it_begin++;
		}

	}
}

void CObjectManager::LateUpdate()
{
	for (int i = 0; i < OBJTYPE::END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_end = m_objList[i].end();
		for (; it_begin != it_end;) {
			(*it_begin)->LateUpdate();
			it_begin++;
		}

	}
}

void CObjectManager::Render()
{
	for (int i = 0; i < OBJTYPE::END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_end = m_objList[i].end();
		for (; it_begin != it_end;) {
			(*it_begin)->RenderCollsionBox();
			(*it_begin)->Render();
			it_begin++;
		}
	}
}

void CObjectManager::Release()
{
	for (int i = 0; i < OBJTYPE::END; ++i)
	{
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
}

void CObjectManager::ReSet()
{
	for (int i = 0; i < OBJTYPE::END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_end = m_objList[i].end();
		for (; it_begin != it_end;) {
			SafeDelete(*it_begin);
			it_begin = m_objList[i].erase(it_begin);

		}

	}

}
