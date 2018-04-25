#include "stdafx.h"
#include "Obj.h"
#include "Obstacle.h"

CCollisionManager* CCollisionManager::m_pInstance = nullptr;

void CCollisionManager::Release()
{
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}

}

void CCollisionManager::CollisionRect(OBJLIST& dstLst, OBJLIST& srcLst)
{
	RECT rc = {};
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			if (IntersectRect(&rc, &(pDst->GetRect()), &(pSrc->GetRect())))
			{
				pSrc->SetDead();
			}
		}
	}
}

bool CCollisionManager::CollisionLine(OBJLIST& dstLst, OBJLIST& srcLst, POS& out, COLLISION& collision)
{
	bool ret{ false };

	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			int w = (pSrc->GetRect().right - pSrc->GetRect().left) / 2;
			int h = (pSrc->GetRect().bottom - pSrc->GetRect().top) / 2;

			int x = pSrc->GetCenter().x;
			int y = pSrc->GetCenter().y;

			if (PointToSegmentDist(pSrc, pDst->GetLine()[SegmentPos::LEFT], w))
			{
				int eID = pDst->GetObstacleType();

				if (eID == ObstacleID::WALL)
				{
					collision = LEFT_COLLISION;
					out.fX = pDst->GetRect().left - w * 2 - 20;
					out.fY = pSrc->GetInfo().fY;

					ret = true;
					return ret;

				}
				else
				{
					out.fX = pDst->GetRect().left - w * 2 - 20;
					out.fY = pSrc->GetInfo().fY;

					ret = false;
					return ret;


				}
			}

			if (PointToSegmentDist(pSrc, pDst->GetLine()[SegmentPos::BOTTOM], h))
			{
				collision = BOTTOM_COLLISION;
				out.fX = pSrc->GetInfo().fX;
				out.fY = pDst->GetRect().bottom - 5;
				ret = false;
				return ret;


			}



			if (PointToSegmentDist(pSrc, pDst->GetLine()[SegmentPos::RIGHT], w))
			{
				int eID = pDst->GetObstacleType();

				if (eID == ObstacleID::WALL)
				{
					collision = RIGHT_COLLISION;

					out.fX = pDst->GetRect().right;
					out.fY = pSrc->GetInfo().fY;

					ret = true;
					return ret;


				}
				else
				{
					out.fX = pDst->GetRect().right;
					out.fY = pSrc->GetInfo().fY;

					ret = false;
					return ret;


				}

			}

			if (PointToSegmentDist(pSrc, pDst->GetLine()[SegmentPos::TOP], h))
			{

				int eID = pDst->GetObstacleType();

				if (eID == ObstacleID::RAIL_RIGHT)
				{
					out.fX = pSrc->GetInfo().fX;
					out.fY = pDst->GetRect().top - h * 2 - 5;

					pSrc->SetPosX(pSrc->GetInfo().fX + pSrc->GetInfo().fSpeed);

				}
				else if (eID == ObstacleID::RAIL_LEFT)
				{
					out.fX = pSrc->GetInfo().fX;
					out.fY = pDst->GetRect().top - h * 2 - 5;

					pSrc->SetPosX(pSrc->GetInfo().fX - pSrc->GetInfo().fSpeed);
				}
				else
				{
					out.fX = pSrc->GetInfo().fX;
					out.fY = pDst->GetRect().top - h * 2 - 5;

					pDst->SetDead();
				}

				ret = true;
				return ret;


			}
		}
	}

	return ret;

}


void CCollisionManager::CollisionTrap(OBJLIST& dstLst, OBJLIST& srcLst)
{
	for (auto& pDst : dstLst)
	{
		for (auto& pSrc : srcLst)
		{
			int w = (pSrc->GetRect().right - pSrc->GetRect().left) / 2;
			int h = (pSrc->GetRect().bottom - pSrc->GetRect().top) / 2;

			if (PointToSegmentDist(pSrc, pDst->GetLine()[SegmentPos::LEFT], h))
			{
				//pSrc->SetDead();
			}

			if (PointToSegmentDist(pSrc, pDst->GetLine()[SegmentPos::RIGHT], h))
			{
				//pSrc->SetDead();
			}
		}
	}
}

bool CCollisionManager::PointToSegmentDist(CObj* pPlayer, LINEINFO tLine, int iDist)
{

	float A = pPlayer->GetCenter().x - tLine.iFirstPtX;
	float B = pPlayer->GetCenter().y - tLine.iFirstPtY;
	float C = tLine.iLastPtX - tLine.iFirstPtX;
	float D = tLine.iLastPtY - tLine.iFirstPtY;

	float dot = A * C + B * D;
	float len_sq = C * C + D * D;
	float param = -1;

	if (len_sq != 0)
		param = dot / len_sq;

	float xx, yy;

	if (param < 0) {
		xx = tLine.iFirstPtX;
		yy = tLine.iFirstPtY;
	}
	else if (param > 1) {
		xx = tLine.iLastPtX;
		yy = tLine.iLastPtY;
	}
	else {
		xx = tLine.iFirstPtX + param * C;
		yy = tLine.iFirstPtY + param * D;
	}

	float dx = pPlayer->GetCenter().x - xx;
	float dy = pPlayer->GetCenter().y - yy;

	if (sqrtf(dx * dx + dy * dy) < iDist) {
		return true;
	}
	//if (sqrtf(dx * dx + dy * dy) <= iDist)   // ´ú´ú x
	//	return true;

	return false;
}
