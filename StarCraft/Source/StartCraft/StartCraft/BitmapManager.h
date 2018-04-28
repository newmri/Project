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
	void LoadButtonImage();
	void LoadSceneImg();
	void LoadMapImg();



public:
	BITMAP_ANIMATION_INFO* GetAnimationInfo(OBJ_ID eId) { return m_tAnimationInfo[eId]; }
	BITMAP_ANIMATION_INFO* GetButtonAnimationInfo(BUTTON_ID eId) { return m_tButtonAnimationInfo[eId]; }
	BITMAP_ANIMATION_INFO* GetSceneAnimationInfo(SCENE::SCENE_ID eId) { return m_tSceneAnimationInfo[eId]; }
	BITMAP_ANIMATION_INFO* GetMapInfo(MAP_ID eId) { return m_tMapInfo[eId]; }



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
	BITMAP_ANIMATION_INFO* m_tSceneAnimationInfo[SCENE::SCENE_END];
	BITMAP_ANIMATION_INFO* m_tMapInfo[MAP_END];


	OBJ_ID				m_eId;
	BUTTON_ID			m_eButtonId;
	SCENE::SCENE_ID		m_eSceneId;
	MAP_ID				m_eMapId;


};