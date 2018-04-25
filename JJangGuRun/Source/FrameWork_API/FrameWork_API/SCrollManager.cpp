#include "stdafx.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;

CScrollManager::CScrollManager()
	: m_fScrollY(0.f)
{
}


CScrollManager::~CScrollManager()
{
}
