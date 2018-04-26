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
	//// ���浹

	//// �� ���� ������ ���� ���Ѵ�.
	//float fSumRad = pDest->GetInfo().m_x * 0.5f + pSrc->GetInfo().m_y * 0.5f;

	//// �� ���� ���� �Ÿ��� ���Ѵ�.
	//float w = pDest->GetInfo().m_x - pSrc->GetInfo().m_y;
	//float h = pDest->GetInfo().m_x - pSrc->GetInfo().m_y;
	//float fDist = sqrtf(w * w + h * h); // ��Ÿ���

	//									// �������� ���� �Ÿ����� Ŭ ��� �浹!
	//if (fSumRad >= fDist)
	//	return true;

	return false;
}
