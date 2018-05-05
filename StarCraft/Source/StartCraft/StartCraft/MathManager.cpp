#include "stdafx.h"

CMathManager* CMathManager::m_pInstance = nullptr;

float CMathManager::CalcDistance(FLOATPOINT tDest, FLOATPOINT tSrc)
{
	float fWidth = tDest.fX - tSrc.fX;
	float fHeight = tDest.fY - tSrc.fY;

	return sqrtf(fWidth * fWidth + fHeight * fHeight);
}

float CMathManager::CalcRadian(FLOATPOINT tDest, FLOATPOINT tSrc)
{
	float fWidth = tDest.fX - tSrc.fX;
	float fHeight = tDest.fY - tSrc.fY;
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fAngle = acosf(fWidth / fDist);

	if (tSrc.fY < tDest.fY) fAngle *= -1.f;

	return fAngle;
}

float CMathManager::CalcDegree(FLOATPOINT tDest, FLOATPOINT tSrc)
{
	float fWidth = tDest.fX - tSrc.fX;
	float fHeight = tDest.fY - tSrc.fY;
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fAngle = acosf(fWidth / fDist);

	if (tSrc.fY < tDest.fY) fAngle *= -1.f;

	fAngle = fAngle * 180.f / PI;

	if (0 > fAngle) fAngle = 360 + fAngle;
	else if (0 == fAngle) fAngle = 360;

	return fAngle;
}
