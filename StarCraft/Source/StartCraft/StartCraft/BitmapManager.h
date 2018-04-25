#pragma once

#include <atlimage.h>
#include <map>
#include <string>
#include <atlstr.h>

class CBitmapManager
{
public:
	void Init();
	void Release();

public:
	void SetName(int idx, char* filemask);
	void CountAnimationNum(char* filemask);
	void AllocMemoryByImageNum(char* filemask);

public:
	void LoadMenuImg();
	void LoadCursorImg();
	void LoadBackImg();
	void LoadPlayerImg();
	void LoadEnemyImg();
	void LoadItemImg();
	void LoadEffectImg();
	void LoadEndingImg();

public:
	BITMAP_ANIMATION_INFO* GetAnimationInfo(OBJ_ID eId) { return m_tAnimationInfo[eId]; }

public:
	void RotateSizingImage(HDC hdc, HBITMAP hBmp, RECT rt,
		double dblAngle,
		int ixRotateAxis, int iyRotateAxis,
		int ixDisplay, int iyDisplay,
		double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

	HBITMAP CreateMask(HDC hdcBitmap, int nWidth, int nHeight);

public:
	std::map<string, CImage*>& GetImage();

public:
	static CBitmapManager* GetInstance()
	{
		if (m_pInstance == nullptr) m_pInstance = new CBitmapManager;
		return m_pInstance;
	}

private:
	CBitmapManager() = default;
	~CBitmapManager() = default;
	CBitmapManager(const CBitmapManager&) = delete;
	void operator=(const CBitmapManager&) = delete;

private:
	map<string, CImage*>		m_map;

private:
	static CBitmapManager*			m_pInstance;

private:
	int m_nAnimationCnt[ANIMATION_NUM_END];

private:
	BITMAP_ANIMATION_INFO* m_tAnimationInfo[OBJ_END];
	OBJ_ID m_eId;
};