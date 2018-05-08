#include "stdafx.h"
#include "Marine.h"
#include "Tile.h"

void CMarine::Init()
{
	CUnit::Init();
	m_tAnimationInfo[m_eCurrId].nCnt = 144;
	nAnimationCnt = -1;
}

void CMarine::LateInit()
{
	CUnit::LateInit();

}

int CMarine::Update()
{
	CObj::LateInit();

	Move();
	Attack();
	return 0;
}

void CMarine::LateUpdate()
{
}

void CMarine::Render()
{
	CUnit::Render();
}

void CMarine::Release()
{
}

bool CMarine::CheckCommand(POINT tMousePos)
{
	return false;
}

void CMarine::RenderUI()
{
}

void CMarine::Move()
{
	if (!m_route.empty()) {
		m_maxCnt = 8;


		if (-1 == nAnimationCnt) {
			m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 2.98f);
			nAnimationCnt = m_tAnimationInfo[m_eCurrId].nCnt + 8;

		}


		INTPOINT pos;
		pos.x = m_tSelectRect.left;
		pos.y = m_tSelectRect.top;
		m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);

		m_nBoforeIdx = m_tSelectRectIdx.x + TILEMANAGER->GetTileNum().x * m_tSelectRectIdx.y;
		if (!dynamic_cast<CTile*>(TILEMANAGER->SelectTile(m_nBoforeIdx))->IsClickable())
			TILEMANAGER->SetTileMovable(m_nBoforeIdx);
		if (m_cnt < m_maxCnt) {

			if (m_dwTime + 10 < GetTickCount()) {
				m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % nAnimationCnt;
				if (m_tAnimationInfo[m_eCurrId].nCnt > 124) m_tAnimationInfo[m_eCurrId].nCnt = 124;
				m_tInfo.tPos.fX += m_tMovePos.fX;
				m_tInfo.tPos.fY += m_tMovePos.fY;
				m_tSelectRect.left += m_tMovePos.fX;
				m_tSelectRect.right += m_tMovePos.fX;
				m_tSelectRect.top += m_tMovePos.fY;
				m_tSelectRect.bottom += m_tMovePos.fY;
				m_dwTime = GetTickCount();
				m_cnt++;
			}

		}
		else {
			int nIdx = m_tSelectRectIdx.x + TILEMANAGER->GetTileNum().x * m_tSelectRectIdx.y;
			TILEMANAGER->SetTileUnMovable(nIdx);
			m_route.pop_front();
			if (m_route.empty()) {
				m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 2.98f);
				nAnimationCnt = -1;
				return;
			}
			pos.x = m_tSelectRect.left;
			pos.y = m_tSelectRect.top;

			INTPOINT idx = TILEMANAGER->GetIndex(pos);

			FLOATPOINT tSrc(static_cast<float>(idx.x * TILE_SIZE), static_cast<float>(idx.y * TILE_SIZE));
			FLOATPOINT tDest(static_cast<float>(m_route.front().x * TILE_SIZE), static_cast<float>((m_route.front().y * TILE_SIZE)));

			int angle = m_tInfo.fAngle;

			m_tInfo.fAngle = MATHMANAGER->CalcDegree(tDest, tSrc);

			float _Height = (float)abs(idx.y * TILE_SIZE - m_route.front().y * TILE_SIZE); // 현재 캐릭터의 좌표와 마우스와의 좌표 사이의 높이를 구해준다. 
			float _Bottom = (float)abs(idx.x * TILE_SIZE - m_route.front().x * TILE_SIZE); // 현재 캐릭터의 좌표와 마우스와의 좌표 사이의 밑변의 길이를 구해준다. 
			float _R = sqrt((_Height*_Height) + (_Bottom*_Bottom)); // 빗변을 구하는 공식. 
																	// 길이 = 속도(이동픽셀) * 시간 =&gt; 시간 = 길이 / 이동 픽셀 


			m_maxCnt = 8;

			m_tMovePos.fX = _Bottom / m_maxCnt;
			m_tMovePos.fY = _Height / m_maxCnt;

			angle = m_tInfo.fAngle;


			if (angle == TOP) m_tMovePos.fY = -m_tMovePos.fY;
			else if (angle == LEFT) m_tMovePos.fX = -m_tMovePos.fX;
			else if (angle > TOP && angle < LEFT) {
				m_tMovePos.fX = -m_tMovePos.fX;
				m_tMovePos.fY = -m_tMovePos.fY;


			}
			else if (angle > LEFT && angle < BOTTOM) m_tMovePos.fX = -m_tMovePos.fX;


			else if (angle > 0 && angle < TOP) m_tMovePos.fY = -m_tMovePos.fY;

			m_dwTime = GetTickCount();
			m_cnt = 0;

			m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 2.98f);
			nAnimationCnt = m_tAnimationInfo[m_eCurrId].nCnt + 8;

			return;

		}


	}
}

void CMarine::Attack()
{
}

void CMarine::UpdateRect()
{
}
