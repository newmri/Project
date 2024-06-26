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
	void SetName(BITMAP_ANIMATION_INFO** tAnimationInfo, int nType, int idx, char* filemask);
	void CountAnimationNum(char* filemask);
	void AllocMemoryByImageNum(BITMAP_ANIMATION_INFO** tAnimationInfo, int nType, char* filemask);

public:
	void LoadObjImg();
	void LoadPortraitImg();
	void LoadLargeWireImg();
	void LoadSmallWireImg();
	void LoadButtonImage();
	void LoadStaticImg();



public:
	BITMAP_ANIMATION_INFO* GetAnimationInfo(OBJ_ID eId) { return m_tAnimationInfo[eId]; }
	BITMAP_ANIMATION_INFO* GetButtonAnimationInfo(BUTTON_ID eId) { return m_tButtonAnimationInfo[eId]; }
	
public:
	IMAGE_INFO* GetImageInfo(IMAGE_ID eId) { return m_tImageInfo[eId]; }
	IMAGE_INFO* GetPortraitImageInfo(PORTRAIT::ID eId) { return m_tPortraitImageInfo[eId]; }
	IMAGE_INFO* GetLargeWireImageInfo(UNIT::LARGE_WIRE::LARGE_WIRE_ID eId) { return m_tLargeWireImageInfo[eId]; }
	IMAGE_INFO* GetSmallWireImageInfo(UNIT::SMALL_WIRE::SMALL_WIRE_ID eId) { return m_tSmallWireImageInfo[eId]; }



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
	static CBitmapManager*		m_pInstance;

private:
	int m_nAnimationCnt[ANIMATION_NUM_END];

private:
	BITMAP_ANIMATION_INFO* m_tAnimationInfo[OBJ_END];
	BITMAP_ANIMATION_INFO* m_tButtonAnimationInfo[BUTTON_END];

private:
	IMAGE_INFO*			   m_tImageInfo[IMAGE_END];
	IMAGE_INFO*			   m_tPortraitImageInfo[PORTRAIT::PORTRAIT_END];
	IMAGE_INFO*			   m_tLargeWireImageInfo[UNIT::LARGE_WIRE::LARGE_WIRE_END];
	IMAGE_INFO*			   m_tSmallWireImageInfo[UNIT::SMALL_WIRE::SMALL_WIRE_END];



	OBJ_ID				m_eId;

	BUTTON_ID			m_eButtonId;


};