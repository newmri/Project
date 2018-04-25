#include "stdafx.h"

CMouseManager*	CMouseManager::m_pInstance = nullptr;

void CMouseManager::Init()
{
	m_eCurrId = ARROW;

	BITMAP_ANIMATION_INFO* pAnim = BITMAPMANAGER->GetAnimationInfo(CURSOR);

	// Set Animation Name
	for (int i = 0; i < CURSOR_END; ++i) {

		m_tAnimationInfo[i].tName = new char*[pAnim[i].nAnimationNum];
		ZeroMemory(m_tAnimationInfo[i].tName, pAnim[i].nAnimationNum);

		for (int j = 0; j < pAnim[i].nAnimationNum; ++j) {
			 
			m_tAnimationInfo[i].tName[j] = new char[STR_LEN];
			strcpy_s(m_tAnimationInfo[i].tName[j], strlen(m_tAnimationInfo[i].tName[j]), pAnim[i].tName[j]);
			
			m_tAnimationInfo[i].nAnimationNum = pAnim[i].nAnimationNum;

			m_tAnimationInfo[i].dwAnimationTime = GetTickCount();
			m_tAnimationInfo[i].nCnt = 0;

		}

	}

}

void CMouseManager::Update()
{
	// Update Mouse Pos
	GetCursorPos(&m_tPos);
	ScreenToClient(RENDERMANAGER->GethWnd(), &m_tPos);

	if (m_tAnimationInfo[m_eCurrId].dwAnimationTime + 1000 / m_tAnimationInfo[m_eCurrId].nAnimationNum < GetTickCount()) {

		m_tAnimationInfo[m_eCurrId].nCnt = (m_tAnimationInfo[m_eCurrId].nCnt + 1) % m_tAnimationInfo[m_eCurrId].nAnimationNum;
		m_tAnimationInfo[m_eCurrId].dwAnimationTime = GetTickCount();
	}
}

void CMouseManager::Render()
{
	
	BITMAPMANAGER->GetImage()[m_tAnimationInfo[m_eCurrId].tName[m_tAnimationInfo[m_eCurrId].nCnt]]->TransparentBlt(RENDERMANAGER->GetMemDC(),
		m_tPos.x - CURSOR_SIZE / 2,
		m_tPos.y - CURSOR_SIZE / 2,
		CURSOR_SIZE,
		CURSOR_SIZE,
		0,
		0,
		CURSOR_SIZE,
		CURSOR_SIZE, RGB(0, 0, 0));
}

void CMouseManager::Release()
{
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName[i]);
	for (int i = 0; i < CURSOR_END; ++i) SafeDelete(m_tAnimationInfo[i].tName);


	
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
