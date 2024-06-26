#pragma once

#include <atlimage.h>
#include <map>
#include <string>
#include <atlstr.h>

class CBitmapManager
{

public:
	void Initialize();
	void Release();

public:
	void LoadMenuImg();
	void LoadBackImg();
	void LoadPlayerImg();
	void LoadEnemyImg();
	void LoadBulletImg();
	void LoadItemImg();
	void LoadEffectImg();
	void LoadSkillImg();
	void LoadEndingImg();

public:
	void RotateSizingImage(HDC hdc, HBITMAP hBmp, RECT rt,
		double dblAngle,
		int ixRotateAxis, int iyRotateAxis,
		int ixDisplay, int iyDisplay,
		double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

	HBITMAP CreateMask(HDC hdcBitmap, int width, int height);

public:
	std::map<CString, CImage*>& GetImage();

public:
	static CBitmapManager* GetInstance()
	{
		if (m_instance == nullptr) m_instance = new CBitmapManager;
		return m_instance;
	}

	~CBitmapManager();

private:
	CBitmapManager();

	CBitmapManager(const CBitmapManager&) = delete;
	void operator=(const CBitmapManager&) = delete;

private:
	std::map<CString, CImage*> m_map;

private:
	static CBitmapManager* m_instance;
};