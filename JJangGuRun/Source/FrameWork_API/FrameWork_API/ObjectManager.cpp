#include "stdafx.h"
#include "Obj.h"
#include "Obstacle.h"
#include "Player.h"

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

void CObjectManager::Init()
{
	dwOld = 0;
	m_bIsPlayerDead = false;
}

void CObjectManager::Update()
{
	for (int i = 0; i < OBJTYPE::END; i++) {
		auto it_begin = m_objList[i].begin();
		auto it_end = m_objList[i].end();
		for (; it_begin != it_end;) {
			int iEvent = (*it_begin)->Update();
			if (DEAD_OBJ == iEvent) {
				if (i == OBJTYPE::PLAYER) {
					m_bIsPlayerDead = true;
					SCENEMANAGER->KillPlayer();
					SafeDelete(*it_begin);
					it_begin = m_objList[i].erase(it_begin);
				}
				else {
					SafeDelete(*it_begin);
					it_begin = m_objList[i].erase(it_begin);
				}
			}

			else if (DEAD_OBSTACLE == iEvent) {
				m_DeadBlock.push_back((*it_begin));
				it_begin = m_objList[i].erase(it_begin);
			}
			else it_begin++;
		}
	}

	if (!m_DeadBlock.empty()){
		if (dwOld + 3500 < GetTickCount()){
			auto iter_begin = m_DeadBlock.begin();

			dynamic_cast<CObstacle*>(*iter_begin)->SetRevival();
			m_objList[OBJTYPE::OBSTACLE].push_back(*iter_begin);
			m_DeadBlock.erase(iter_begin);

			dwOld = GetTickCount();
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

	if (0 != m_objList[OBJTYPE::PLAYER].size()) {
		if(!dynamic_cast<CPlayer*>(m_objList[OBJTYPE::PLAYER].front())->IsCheatOn()) {
			CCollisionManager::CollisionRect(m_objList[OBJTYPE::OBSTACLE], m_objList[OBJTYPE::BULLET]);
			CCollisionManager::CollisionRect(m_objList[OBJTYPE::BULLET], m_objList[OBJTYPE::PLAYER]);
			CCollisionManager::CollisionRect(m_objList[OBJTYPE::ENEMY], m_objList[OBJTYPE::PLAYER]);
			CCollisionManager::CollisionTrap(m_objList[OBJTYPE::TRAP], m_objList[OBJTYPE::PLAYER]);
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

	for_each(m_DeadBlock.begin(), m_DeadBlock.end(),
		[](auto& obj)
	{
		if (obj)
		{
			delete obj;
			obj = nullptr;
		}
	});
	m_DeadBlock.clear();

}

void CObjectManager::ReSet()
{
	Release();

}

void CObjectManager::LoadData()
{
	HANDLE hFile = CreateFile(L"Data/Line.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(RENDERMANAGER->GethWnd(), L"No Data", L"Load failed", MB_OK);
		return;
	}

	BLOCKINFO tLoad = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tLoad, sizeof(BLOCKINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_objList[OBJTYPE::OBSTACLE].push_back(new CObstacle(tLoad));
	}

	CloseHandle(hFile);
}
