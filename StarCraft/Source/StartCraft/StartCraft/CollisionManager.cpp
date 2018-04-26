#include "stdafx.h"
#include "Obj.h"

CCollisionManager* CCollisionManager::m_pInstance = nullptr;

void CCollisionManager::RectCollision(OBJLIST& dest, OBJLIST& src)
{
	RECT rc{};

	for (auto& pDst : dest) {
		for (auto& pSrc : src) {
			if (IntersectRect(&rc, &(pDst->GetRect()), &(pSrc->GetRect()))) {
				//pDst->SetDamage(pSrc->GetStat().m_Atk);
				//pSrc->SetDead();
			}
		}
	}
}

void CCollisionManager::SphereCollision(OBJLIST& dest, OBJLIST& src)
{
	/*for (auto& pDst : dest) {
		for (auto& pSrc : src) {
			if (CheckSphere(pDst, pSrc)) {
				pDst->SetDamage(pSrc->GetStat().m_Atk);
				pSrc->SetDead();
			}
		}
	}*/
}


void CCollisionManager::Release()
{
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}

}

bool CCollisionManager::CheckSphere(CObj* pDest, CObj* pSrc)
{
	//// 원충돌

	//// 두 원의 반지름 합을 구한다.
	//float fSumRad = pDest->GetInfo().m_x * 0.5f + pSrc->GetInfo().m_y * 0.5f;

	//// 두 원의 중점 거리를 구한다.
	//float w = pDest->GetInfo().m_x - pSrc->GetInfo().m_y;
	//float h = pDest->GetInfo().m_x - pSrc->GetInfo().m_y;
	//float fDist = sqrtf(w * w + h * h); // 피타고라스

	//									// 반지름의 합이 거리보다 클 경우 충돌!
	//if (fSumRad >= fDist)
	//	return true;

	return false;
}
