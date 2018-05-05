#include "stdafx.h"
#include "Unit.h"
#include "Tile.h"

void CUnit::Init()
{
	m_eCurrId = UNIT::IDLE;

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);
	m_tAnimationInfo = new ANIMATION_INFO[pAnim->nStateNum];
	for (int i = 0; i < pAnim->nStateNum; ++i) ZeroMemory(&m_tAnimationInfo[i], sizeof(m_tAnimationInfo[i]));

	m_tInfo.fSpeed = TILE_SIZE / 2.f;
	m_bMove = false;
	m_tInfo.fAngle = BOTTOM;

}

void CUnit::LateInit()
{
	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(m_tInfo.eObjId);
	// Set Animation Name
	for (int i = 0; i < pAnim->nStateNum; ++i) {
	
		m_tAnimationInfo[i].tName = new char*[pAnim[i].nAnimationNum];
		ZeroMemory(m_tAnimationInfo[i].tName, pAnim[i].nAnimationNum);

		for (int j = 0; j < pAnim[i].nAnimationNum; ++j) {

			m_tAnimationInfo[i].tName[j] = new char[STR_LEN];
			strcpy_s(m_tAnimationInfo[i].tName[j], strlen(m_tAnimationInfo[i].tName[j]), pAnim[i].tName[j]);
			m_tAnimationInfo[i].nAnimationNum = pAnim[i].nAnimationNum;
			m_tAnimationInfo[i].nImageW = pAnim[i].nImageW;
			m_tAnimationInfo[i].nImageH = pAnim[i].nImageH;
			m_tAnimationInfo[i].dwAnimationTime = GetTickCount();
			m_tAnimationInfo[i].nCnt = 0;

		}

	}

	UpdateRect();

	// Swap Tail
	float fScrollX = SCROLLMANAGER->GetScrollX();
	float fScrollY = SCROLLMANAGER->GetScrollY();

	m_tSelectRect.left = m_tRect.left + fScrollX + TILE_SIZE;
	m_tSelectRect.top = (m_tRect.top + fScrollY) + TILE_SIZE;
	m_tSelectRect.right = m_tSelectRect.left + TILE_SIZE;
	m_tSelectRect.bottom = m_tSelectRect.top + TILE_SIZE;

	INTPOINT pos;
	pos.x = m_tSelectRect.left;
	pos.y = m_tSelectRect.top;

	m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);

	for (int posY = m_tSelectRect.top; posY < m_tSelectRect.bottom; posY += TILE_SIZE) {

		for (int posX = m_tSelectRect.left; posX < m_tSelectRect.right; posX += TILE_SIZE) {

			int x = (posX - static_cast<int>(fScrollX)) / TILE_SIZE;
			int y = (posY - static_cast<int>(fScrollY)) / TILE_SIZE;
			int k = TILEMANAGER->GetTileNum().x;
			int nIdx = x + TILEMANAGER->GetTileNum().x * y;

			CObj* pTile = TILEMANAGER->SelectTile(nIdx);

			if (nullptr == pTile) return;

			dynamic_cast<CTile*>(pTile)->SetTileUnMovable();
		}
	}

	m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 10);
	m_tAnimationInfo[m_eCurrId].nCnt -= 2;
}

int CUnit::Update()
{
	CObj::LateInit();


	if (!m_route.empty()) {
		

		// Rotate
		m_tAnimationInfo[m_eCurrId].nCnt = (static_cast<int>(m_tInfo.fAngle) / 10);
		if(360 == m_tInfo.fAngle) m_tAnimationInfo[m_eCurrId].nCnt -= 3;
		else m_tAnimationInfo[m_eCurrId].nCnt -= 1;


		float x = cosf(m_tInfo.fAngle * PI / 180.f) * m_tInfo.fSpeed;
		float y = sinf(m_tInfo.fAngle * PI / 180.f) * m_tInfo.fSpeed;


		INTPOINT pos;
		pos.x = m_tSelectRect.left;
		pos.y = m_tSelectRect.top;
		m_tSelectRectIdx = TILEMANAGER->GetIndex(pos);

		m_nBoforeIdx = m_tSelectRectIdx.x + TILEMANAGER->GetTileNum().x * m_tSelectRectIdx.y;
		TILEMANAGER->SetTileMovable(m_nBoforeIdx);
		
		if (m_cnt < m_maxCnt) {
			if (m_dwTime + 10 < GetTickCount()) {
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
			if (m_route.empty()) return 0;
			
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

			m_maxCnt = _R / m_tInfo.fSpeed;

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

			return 0;

		}

		
	}

	return 0;
}

void CUnit::LateUpdate()
{
}

void CUnit::Render()
{
	if (0 == m_tAnimationInfo[m_eCurrId].nImageW) return;

	UpdateRect();

	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		static_cast<int>(m_tRect.left + SCROLLMANAGER->GetScrollX()),
		static_cast<int>(m_tRect.top + SCROLLMANAGER->GetScrollY()),
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH,
		0,
		0,
		m_tAnimationInfo[m_eCurrId].nImageW,
		m_tAnimationInfo[m_eCurrId].nImageH, RGB(0, 0, 0));
}

void CUnit::Release()
{
}

void CUnit::UpdateRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.tPos.fX);
	m_tRect.right = static_cast<LONG>(m_tInfo.tPos.fX + m_tAnimationInfo[m_eCurrId].nImageW);
	m_tRect.top = static_cast<LONG>(m_tInfo.tPos.fY);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.tPos.fY + m_tAnimationInfo[m_eCurrId].nImageH);
}
