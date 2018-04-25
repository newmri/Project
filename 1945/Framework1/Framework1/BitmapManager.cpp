#include "stdafx.h"

CBitmapManager* CBitmapManager::m_instance = nullptr;

CBitmapManager::CBitmapManager()
{
	//Initialize();
}

CBitmapManager::~CBitmapManager()
{
	Release();
}

void CBitmapManager::Initialize()
{
	LoadMenuImg();
	LoadBackImg();
	LoadPlayerImg();
	LoadEnemyImg();
	LoadBulletImg();
	LoadItemImg();
	LoadEffectImg();
	LoadSkillImg();
	LoadEndingImg();
}

void CBitmapManager::Release()
{
	for (auto& d : m_map) {
		delete d.second;
		d.second = nullptr;
	}

	m_map.clear();
	ObjDelete(m_instance);
}

void CBitmapManager::LoadMenuImg()
{
	CImage* pImg = new CImage;
	CString tDir = L"Resources/Image/Menu/MainMenu.png";
	CString tKey = L"MAINMENU";
	pImg->Load(tDir);
	m_map.insert(make_pair(tKey, pImg));
}

void CBitmapManager::LoadBackImg()
{
	for (int i = 0; i < NUM_OF_STAGE; ++i) {
		CImage* pImg = new CImage;
		CString tDir;
		CString tKey;
		tKey.Format(L"STAGE%d", i + 1);
		tDir.Format(L"Resources/Image/Map/Stage%d.bmp", i + 1);
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}
	

}

void CBitmapManager::LoadPlayerImg()
{
	CImage* pImg = new CImage;
	CString tDir = L"Resources/Image/Player/PlayerLR.bmp";
	CString tKey = L"PLAYERLR";
	pImg->Load(tDir);
	m_map.insert(make_pair(tKey, pImg));

	CImage* pImg2 = new CImage;
	tDir = L"Resources/Image/Player/PlayerTB.bmp";
	tKey = L"PLAYERTB";
	pImg2->Load(tDir);
	m_map.insert(make_pair(tKey, pImg2));
}

void CBitmapManager::LoadEnemyImg()
{
	CString tDir;
	CString tKey;

	for (int i = 0; i < NUM_OF_ENEMY; ++i) {
		CImage* pImg = new CImage;
		tKey.Format(L"ENEMY%d", i + 1);
		tDir.Format(L"Resources/Image/Enemy/Enemy%d.bmp", i + 1);
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}

	for (int i = 0; i < NUM_OF_BOSS; ++i) {
		CImage* pImg = new CImage;
		tKey.Format(L"BOSS%d", i + 1);
		tDir.Format(L"Resources/Image/Enemy/Boss%d.bmp", i + 1);
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}


}

void CBitmapManager::LoadBulletImg()
{
	CString tDir;
	CString tKey;
	for (int i = 0; i < NUM_OF_BULLET; ++i) {
		CImage* pImg = new CImage;
		tKey.Format(L"NORMAL_BULLET_LV%d", i + 1);
		tDir.Format(L"Resources/Image/Bullet/NormalBulletLv%d.bmp", i + 1);
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}

	for (int i = 0; i < NUM_OF_MISSILE; ++i) {
		CImage* pImg = new CImage;
		tKey.Format(L"MISSILE%d", i + 1);
		tDir.Format(L"Resources/Image/Bullet/Missile%d.bmp", i + 1);
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}



	for (int i = 0; i < NUM_OF_ENEMY_BULLET; ++i) {
		CImage* pImg = new CImage;
		tKey.Format(L"NORMAL_ENEMY_BULLET_LV%d", i + 1);
		tDir.Format(L"Resources/Image/Bullet/NormalEnemyBulletLv%d.bmp", i + 1);
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}

}

void CBitmapManager::LoadItemImg()
{
	CImage* pImg = new CImage;
	CString tDir = L"Resources/Image/Item/Item.bmp";
	CString tKey = L"ITEM";
	pImg->Load(tDir);
	m_map.insert(make_pair(tKey, pImg));

	{
		CImage* pImg = new CImage;
		CString tDir = L"Resources/Image/Shield/Shield.bmp";
		CString tKey = L"SHIELD";
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}
}

void CBitmapManager::LoadEffectImg()
{
}

void CBitmapManager::LoadSkillImg()
{
	CImage* pImg = new CImage;
	CString tDir = L"Resources/Image/Skill/SkillAirplane.bmp";
	CString tKey = L"SKILL_AIR_PLANE";
	pImg->Load(tDir);
	m_map.insert(make_pair(tKey, pImg));
}

void CBitmapManager::LoadEndingImg()
{
	CImage* pImg = new CImage;
	CString tDir = L"Resources/Image/Die/Die.bmp";
	CString tKey = L"DIE";
	pImg->Load(tDir);
	m_map.insert(make_pair(tKey, pImg));
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




std::map<CString, CImage*>& CBitmapManager::GetImage()
{
	return m_map;
}
