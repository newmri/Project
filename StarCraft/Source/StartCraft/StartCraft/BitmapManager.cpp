#include "stdafx.h"
#include "BitmapManager.h"

CBitmapManager* CBitmapManager::m_pInstance = nullptr;

void CBitmapManager::Init()
{
	LoadObjImg();
	LoadButtonImage();
	LoadSceneImg();
	LoadMapImg();
	
}

void CBitmapManager::Release()
{

	// Need to be fixed
	for (int i = 0; i < OBJ_END; ++i) {
		for (int j = 0; j < CURSOR_END; ++j) SafeDelete(m_tAnimationInfo[i][j].tName[i]);
		for (int j = 0; j < CURSOR_END; ++j) SafeDelete(m_tAnimationInfo[i][j].tName);

		SafeDelete(m_tAnimationInfo[i]);
	}

	for (int i = 0; i < SCENE::SCENE_END; ++i) {
		for (int j = 0; j < SCENE::SCENE_END; ++j) SafeDelete(m_tSceneAnimationInfo[i][j].tName[i]);
		for (int j = 0; j < SCENE::SCENE_END; ++j) SafeDelete(m_tSceneAnimationInfo[i][j].tName);

		SafeDelete(m_tSceneAnimationInfo[i]);
	}


	for (auto& d : m_map) {
		delete d.second;
		d.second = nullptr;
	}

	m_map.clear();
	
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CBitmapManager::SetName(BITMAP_ANIMATION_INFO** tAnimationInfo, int nType, int idx, char* filemask)
{
	char path[STR_LEN];
	char name[STR_LEN];
	char* p = nullptr;

	struct _finddata_t info;
	intptr_t hFile;

	char chE[2];
	chE[0] = '*';
	chE[1] = '\0';
	char chD[2];
	chD[0] = '.';
	chD[1] = '\0';

	int cnt = 0;

	hFile = _findfirst(filemask, &info);
	if (-1 == hFile) return;

	while (_findnext(hFile, &info) != -1L) {
		// Cut *
		strcpy_s(path, STR_LEN, filemask);
		strtok_s(path, chE, &p);

		if ((_A_SUBDIR & info.attrib)) {
			if (!strcmp(info.name, ".") || !strcmp(info.name, "..")) continue;

			strcat_s(path, info.name);
			strcat_s(path, "/*.*");
			strcat_s(path, "\0");
			SetName(tAnimationInfo, nType, idx++, path);
		
		}
		else {
			// Cut .
			strcat_s(path, info.name);
			strcat_s(path, "\0");
			strtok_s(info.name, chD, &p);
			strcat_s(info.name, "\0");
			strcpy_s(name, STR_LEN, info.name);

			CImage* pImg = new CImage;
			pImg->Load(CString(path));
			m_map.insert(make_pair(string(name), pImg));
			strcpy_s(tAnimationInfo[nType][idx].tName[cnt], STR_LEN, name);

			tAnimationInfo[nType][idx].nImageW = m_map[name]->GetWidth();
			tAnimationInfo[nType][idx].nImageH = m_map[name]->GetHeight();

			if (cnt < tAnimationInfo[nType][idx].nAnimationNum - 1) ++cnt;


		}
	};
	

}

void CBitmapManager::CountAnimationNum(char* filemask)
{
	char path[STR_LEN];
	char* p = nullptr;

	struct _finddata_t info;
	intptr_t hFile;

	char chE[2];
	chE[0] = '*';
	chE[1] = '\0';

	hFile = _findfirst(filemask, &info);
	if (-1 == hFile) return;

	while (_findnext(hFile, &info) != -1L) {
		// Cut *
		strcpy_s(path, STR_LEN, filemask);
		strtok_s(path, chE, &p);

		if ((_A_SUBDIR & info.attrib)) {
			if (!strcmp(info.name, ".") || !strcmp(info.name, "..")) continue;

			strcat_s(path, info.name);
			strcat_s(path, "/*.*");
			strcat_s(path, "\0");
			CountAnimationNum(path);
			++m_nAnimationCnt[TYPE_NUM];

		}

	};
	

}

void CBitmapManager::AllocMemoryByImageNum(BITMAP_ANIMATION_INFO** tAnimationInfo, int nType, char* filemask)
{
	char path[STR_LEN];
	char* p = nullptr;

	struct _finddata_t info;
	intptr_t hFile;

	char chE[2];
	chE[0] = '*';
	chE[1] = '\0';

	m_nAnimationCnt[IMAGE_NUM] = 0;
	int idx = 0;

	hFile = _findfirst(filemask, &info);
	if (-1 == hFile) return;
	
	while (_findnext(hFile, &info) != -1L) {
		// Cut *
		strcpy_s(path, STR_LEN, filemask);
		strtok_s(path, chE, &p);

		if ((_A_SUBDIR & info.attrib)) {
			if (!strcmp(info.name, ".") || !strcmp(info.name, "..")) continue;

			strcat_s(path, info.name);
			strcat_s(path, "/*.*");
			strcat_s(path, "\0");

			AllocMemoryByImageNum(tAnimationInfo, nType, path);

			tAnimationInfo[nType][idx].nAnimationNum = m_nAnimationCnt[IMAGE_NUM];
			tAnimationInfo[nType][idx].tName = new char*[m_nAnimationCnt[IMAGE_NUM]];
			ZeroMemory(tAnimationInfo[nType][idx++].tName, m_nAnimationCnt[IMAGE_NUM]);

		}
		else ++m_nAnimationCnt[IMAGE_NUM];

	};
	

}

void CBitmapManager::LoadObjImg()
{

	for (int i = 0; i < OBJ_END; ++i) {
		m_eId = static_cast<OBJ_ID>(i);
		m_nAnimationCnt[TYPE_NUM] = 1;

		char filemask[STR_LEN];
		strcpy_s(filemask, STR_LEN, OBJ_DIR[i]);
		strcat_s(filemask, "\0");

		CountAnimationNum(filemask);

		m_tAnimationInfo[i] = new BITMAP_ANIMATION_INFO[m_nAnimationCnt[TYPE_NUM]];
		ZeroMemory(m_tAnimationInfo[i], sizeof(BITMAP_ANIMATION_INFO));
		

		AllocMemoryByImageNum(m_tAnimationInfo, m_eId, filemask);

		// have no animation
		if (1 == m_nAnimationCnt[IMAGE_NUM]) {
			m_tAnimationInfo[m_eId][0].nAnimationNum = m_nAnimationCnt[IMAGE_NUM];
			m_tAnimationInfo[m_eId][0].tName = new char*[m_nAnimationCnt[IMAGE_NUM]];
			ZeroMemory(m_tAnimationInfo[m_eId][0].tName, m_nAnimationCnt[IMAGE_NUM]);
		}

		for (int i = 0; i < m_nAnimationCnt[TYPE_NUM]; ++i) {
			if (0 == m_tAnimationInfo[m_eId][i].nAnimationNum) m_tAnimationInfo[m_eId][i].nAnimationNum = 1;

			for (int j = 0; j < m_tAnimationInfo[m_eId][i].nAnimationNum; ++j) {
				m_tAnimationInfo[m_eId][i].tName[j] = new char[STR_LEN];
				ZeroMemory(m_tAnimationInfo[m_eId][i].tName[j], STR_LEN);

			}

		}
		SetName(m_tAnimationInfo, m_eId, 0, (char*)filemask);
	}

}

void CBitmapManager::LoadButtonImage()
{
	for (int i = 0; i < BUTTON_END; ++i) {
		m_eButtonId = static_cast<BUTTON_ID>(i);
		m_nAnimationCnt[TYPE_NUM] = 1;

		char filemask[STR_LEN];
		strcpy_s(filemask, STR_LEN, BUTTON_DIR[i]);
		strcat_s(filemask, "\0");

		CountAnimationNum(filemask);

		m_tButtonAnimationInfo[i] = new BITMAP_ANIMATION_INFO[m_nAnimationCnt[TYPE_NUM]];
		ZeroMemory(m_tButtonAnimationInfo[i], sizeof(BITMAP_ANIMATION_INFO));

		AllocMemoryByImageNum(m_tButtonAnimationInfo, m_eButtonId, filemask);

		// have no animation
		if (1 == m_nAnimationCnt[IMAGE_NUM]) {
			m_tButtonAnimationInfo[m_eButtonId][0].nAnimationNum = m_nAnimationCnt[IMAGE_NUM];
			m_tButtonAnimationInfo[m_eButtonId][0].tName = new char*[m_nAnimationCnt[IMAGE_NUM]];
			ZeroMemory(m_tButtonAnimationInfo[m_eButtonId][0].tName, m_nAnimationCnt[IMAGE_NUM]);
		}

		for (int i = 0; i < m_nAnimationCnt[TYPE_NUM]; ++i) {
			if (0 == m_tButtonAnimationInfo[m_eButtonId][i].nAnimationNum) m_tButtonAnimationInfo[m_eButtonId][i].nAnimationNum = 1;

			for (int j = 0; j < m_tButtonAnimationInfo[m_eButtonId][i].nAnimationNum; ++j) {
				m_tButtonAnimationInfo[m_eButtonId][i].tName[j] = new char[STR_LEN];
				ZeroMemory(m_tButtonAnimationInfo[m_eButtonId][i].tName[j], STR_LEN);

			}

		}
		SetName(m_tButtonAnimationInfo, m_eButtonId, 0, (char*)filemask);
	}
}

void CBitmapManager::LoadSceneImg()
{
	for (int i = 0; i < SCENE::SCENE_END; ++i) {
		m_eSceneId = static_cast<SCENE::SCENE_ID>(i);
		m_nAnimationCnt[TYPE_NUM] = 1;

		char filemask[STR_LEN];
		strcpy_s(filemask, STR_LEN, SCENE_DIR[i]);
		strcat_s(filemask, "\0");

		CountAnimationNum(filemask);

		m_tSceneAnimationInfo[i] = new BITMAP_ANIMATION_INFO[m_nAnimationCnt[TYPE_NUM]];
		ZeroMemory(m_tSceneAnimationInfo[i], sizeof(BITMAP_ANIMATION_INFO));

		AllocMemoryByImageNum(m_tSceneAnimationInfo, m_eSceneId, filemask);

		// have no animation
		if (1 == m_nAnimationCnt[IMAGE_NUM]) {
			m_tSceneAnimationInfo[m_eSceneId][0].nAnimationNum = m_nAnimationCnt[IMAGE_NUM];
			m_tSceneAnimationInfo[m_eSceneId][0].tName = new char*[m_nAnimationCnt[IMAGE_NUM]];
			ZeroMemory(m_tSceneAnimationInfo[m_eSceneId][0].tName, m_nAnimationCnt[IMAGE_NUM]);
		}

		for (int i = 0; i < m_nAnimationCnt[TYPE_NUM]; ++i) {
			if (0 == m_tSceneAnimationInfo[m_eSceneId][i].nAnimationNum) m_tSceneAnimationInfo[m_eSceneId][i].nAnimationNum = 1;

			for (int j = 0; j < m_tSceneAnimationInfo[m_eSceneId][i].nAnimationNum; ++j) {
				m_tSceneAnimationInfo[m_eSceneId][i].tName[j] = new char[STR_LEN];
				ZeroMemory(m_tSceneAnimationInfo[m_eSceneId][i].tName[j], STR_LEN);

			}

		}
		SetName(m_tSceneAnimationInfo, m_eSceneId, 0, (char*)filemask);
	}
}

void CBitmapManager::LoadMapImg()
{
	for (int i = 0; i < MAP_END; ++i) {
		m_eMapId = static_cast<MAP_ID>(i);
		m_nAnimationCnt[TYPE_NUM] = 1;

		char filemask[STR_LEN];
		strcpy_s(filemask, STR_LEN, MAP_DIR[i]);
		strcat_s(filemask, "\0");

		CountAnimationNum(filemask);

		m_tMapInfo[i] = new BITMAP_ANIMATION_INFO[m_nAnimationCnt[TYPE_NUM]];
		ZeroMemory(m_tMapInfo[i], sizeof(BITMAP_ANIMATION_INFO));

		AllocMemoryByImageNum(m_tMapInfo, m_eMapId, filemask);

		// have no animation
		if (1 == m_nAnimationCnt[IMAGE_NUM]) {
			m_tMapInfo[m_eMapId][0].nAnimationNum = m_nAnimationCnt[IMAGE_NUM];
			m_tMapInfo[m_eMapId][0].tName = new char*[m_nAnimationCnt[IMAGE_NUM]];
			ZeroMemory(m_tMapInfo[m_eMapId][0].tName, m_nAnimationCnt[IMAGE_NUM]);
		}

		for (int i = 0; i < m_nAnimationCnt[TYPE_NUM]; ++i) {
			if (0 == m_tMapInfo[m_eMapId][i].nAnimationNum) m_tMapInfo[m_eMapId][i].nAnimationNum = 1;

			for (int j = 0; j < m_tMapInfo[m_eMapId][i].nAnimationNum; ++j) {
				m_tMapInfo[m_eMapId][i].tName[j] = new char[STR_LEN];
				ZeroMemory(m_tMapInfo[m_eMapId][i].tName[j], STR_LEN);

			}

		}
		SetName(m_tMapInfo, m_eMapId, 0, (char*)filemask);
	}
}


void CBitmapManager::RotateSizingImage(HDC hdc, HBITMAP hBmp, RECT rt, double dblAngle, int ixRotateAxis, int iyRotateAxis, int ixDisplay, int iyDisplay, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	int i;
	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);
	POINT apt[3] = { 0 };
	double dblWidth = (double)bm.bmWidth*dblSizeRatio;
	double dblHeight = (double)bm.bmHeight*dblSizeRatio;
	double ixRotate = (int)((double)ixRotateAxis*dblSizeRatio); // 크기가 변하는 것 고려
	double iyRotate = (int)((double)iyRotateAxis*dblSizeRatio);
	const double pi = 3.14159265358979323846;


	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * pi / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. 회전축을 기준으로 상대좌표를 구하고
	// 2. 회전후 위치좌표(상대좌표)를 얻은 후
	// 3. 얻은 값을 원래의 좌표에 적용.
	for (i = 0; i<3; i++) {
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  꼭지점 부분
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up 꼭지점 부분
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low 꼭지점 부분
		dblxDest = dblx * cosVal - dbly * sinVal;
		dblyDest = dblx * sinVal + dbly * cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = ixDisplay - (long)ixRotate + (long)dblxDest;
		apt[i].y = iyDisplay - (long)iyRotate + (long)dblyDest;

	}

	HDC hMemdc;
	HBITMAP hOldBmp;
	hMemdc = CreateCompatibleDC(hdc);
	hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);

	CImage img;

	BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
	SelectObject(hMemdc, hOldBmp);
	DeleteDC(hMemdc);

}

HBITMAP CBitmapManager::CreateMask(HDC hdcBitmap, int width, int height)
{
	// 투명색 지정 현재 투명색은 분홍색으로 지정되어 있습니다만,
	// 흰색이나 검정색으로 하시려면 RGB(255, 255, 255) 또는 RGB(0, 0, 0) 으로 수정하시면 됩니다.
	COLORREF oldBackColor = SetBkColor(hdcBitmap, RGB(255, 255, 255));

	// 마스크 비트맵을 만듭니다. (물론 DC도 같이 만듭니다.)
	// 보통 마스크 비트맵은 1BPP 짜리 흑백 비트맵으로 만듭니다.
	HDC hdcMask = CreateCompatibleDC(NULL);
	HBITMAP hBitmapMask = CreateBitmap(width, height, 1, 1, NULL); // 마스크 비트맵 생성
	SelectObject(hdcMask, hBitmapMask);

	// hdcMask와 hBitmapMask에 hdcBitmap(출력할 스프라이트)의 마스크를 만듭니다.
	BitBlt(
		hdcMask,
		0, 0,
		width, height,
		hdcBitmap,
		0, 0,
		NOTSRCCOPY);

	// 배경색을 원래 색으로 돌려놓습니다.    
	SetBkColor(hdcBitmap, oldBackColor);

	// 생성된 마스크비트맵을 리턴
	return hBitmapMask;
}




map<string, CImage*>& CBitmapManager::GetImage()
{
	return m_map;
}
