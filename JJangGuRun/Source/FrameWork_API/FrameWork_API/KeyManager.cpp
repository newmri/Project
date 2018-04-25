#include "stdafx.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

void CKeyManager::Release()
{
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

CKeyManager::CKeyManager()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyManager::~CKeyManager()
{

}

bool CKeyManager::KeyPressing(int iVKey)
{
	if (GetAsyncKeyState(iVKey) & 0x8000)
		return true;

	return false;
}

bool CKeyManager::KeyDown(int iVKey)
{
	if (!m_bKeyState[iVKey] && GetAsyncKeyState(iVKey) & 0x8000)
	{
		m_bKeyState[iVKey] = !m_bKeyState[iVKey];
		return true;
	}

	return false;
}

bool CKeyManager::KeyUp(int iVKey)
{
	if (m_bKeyState[iVKey] && !(GetAsyncKeyState(iVKey) & 0x8000))
	{
		m_bKeyState[iVKey] = !m_bKeyState[iVKey];
		return true;
	}

	return false;
}

// 매 프레임마다 키의 상태는 원상복구가 되어야한다.
void CKeyManager::Update()
{
	for (int i = 0; i < MAX_VK; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if (!m_bKeyState[i] && GetAsyncKeyState(i) & 0x8000)
			m_bKeyState[i] = !m_bKeyState[i];
	}
}