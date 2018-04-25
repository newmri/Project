#include "stdafx.h"

CBitmapManager* CBitmapManager::m_pInstance = nullptr;

void CBitmapManager::Init()
{
	LoadMenuImg();
	LoadBackImg();
	LoadPlayerImg();
	LoadEnemyImg();
	LoadItemImg();
	LoadEffectImg();
	LoadEndingImg();
}

void CBitmapManager::Release()
{
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
	for (int i = 0; i < ANIM_END; ++i) {
		CImage* pImg = new CImage;
		CString tDir = L"Resources/Image/Player/";
		CString tKey = PLAYER_IMG_STR[i];
		CString tExtention = L".bmp";
		tDir.Append(tKey);
		tDir.Append(tExtention);
		pImg->Load(tDir);
		m_map.insert(make_pair(tKey, pImg));
	}
}

void CBitmapManager::LoadEnemyImg()
{
	CString tDir;
	CString tKey;

	//for (int i = 0; i < NUM_OF_ENEMY; ++i) {
	//	CImage* pImg = new CImage;
	//	tKey.Format(L"ENEMY%d", i + 1);
	//	tDir.Format(L"Resources/Image/Enemy/Enemy%d.bmp", i + 1);
	//	pImg->Load(tDir);
	//	m_map.insert(make_pair(tKey, pImg));
	//}


}

void CBitmapManager::LoadItemImg()
{
	//CImage* pImg = new CImage;
	//CString tDir = L"Resources/Image/Item/Item.bmp";
	//CString tKey = L"ITEM";
	//pImg->Load(tDir);
	//m_map.insert(make_pair(tKey, pImg));

	//{
	//	CImage* pImg = new CImage;
	//	CString tDir = L"Resources/Image/Shield/Shield.bmp";
	//	CString tKey = L"SHIELD";
	//	pImg->Load(tDir);
	//	m_map.insert(make_pair(tKey, pImg));
	//}
}

void CBitmapManager::LoadEffectImg()
{
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
	double ixRotate = (int)((double)ixRotateAxis*dblSizeRatio); // ũ�Ⱑ ���ϴ� �� ���
	double iyRotate = (int)((double)iyRotateAxis*dblSizeRatio);
	const double pi = 3.14159265358979323846;


	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * pi / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. ȸ������ �������� �����ǥ�� ���ϰ�
	// 2. ȸ���� ��ġ��ǥ(�����ǥ)�� ���� ��
	// 3. ���� ���� ������ ��ǥ�� ����.
	for (i = 0; i<3; i++) {
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  ������ �κ�
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up ������ �κ�
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low ������ �κ�
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
	// ����� ���� ���� ������� ��ȫ������ �����Ǿ� �ֽ��ϴٸ�,
	// ����̳� ���������� �Ͻ÷��� RGB(255, 255, 255) �Ǵ� RGB(0, 0, 0) ���� �����Ͻø� �˴ϴ�.
	COLORREF oldBackColor = SetBkColor(hdcBitmap, RGB(255, 255, 255));

	// ����ũ ��Ʈ���� ����ϴ�. (���� DC�� ���� ����ϴ�.)
	// ���� ����ũ ��Ʈ���� 1BPP ¥�� ��� ��Ʈ������ ����ϴ�.
	HDC hdcMask = CreateCompatibleDC(NULL);
	HBITMAP hBitmapMask = CreateBitmap(width, height, 1, 1, NULL); // ����ũ ��Ʈ�� ����
	SelectObject(hdcMask, hBitmapMask);

	// hdcMask�� hBitmapMask�� hdcBitmap(����� ��������Ʈ)�� ����ũ�� ����ϴ�.
	BitBlt(
		hdcMask,
		0, 0,
		width, height,
		hdcBitmap,
		0, 0,
		NOTSRCCOPY);

	// ������ ���� ������ ���������ϴ�.    
	SetBkColor(hdcBitmap, oldBackColor);

	// ������ ����ũ��Ʈ���� ����
	return hBitmapMask;
}




std::map<CString, CImage*>& CBitmapManager::GetImage()
{
	return m_map;
}
