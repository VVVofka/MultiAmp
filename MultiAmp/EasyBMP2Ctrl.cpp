#include "pch.h"
#include "EasyBMP2Ctrl.h"
#include <gdiplusgraphics.h>
using namespace Graphics;

void EasyBMP2Ctrl::load(CWnd* wnd, COLORREF* data){
	CRect r_CL;	// пр€моугольник клиентской области
	wnd->GetClientRect(&r_CL);		//	m_screen.GetClientRect(&r_CL);

	// определение высоты и ширины клиентской области
	int bmpWidth = r_CL.Width();
	int bmpHeight = r_CL.Height();
	int bmpSize = bmpWidth * bmpHeight;

	BMP bmp;
	bmp.SetSize(bmpWidth, bmpHeight);
	bmp.SetBitDepth(8);

	COLORREF* curdata = data;
	for(size_t ypos = 0; ypos < (size_t)bmpHeight; ypos++){
		for(size_t xpos = 0; xpos < (size_t)bmpWidth; xpos++){
			auto pix = bmp(xpos, ypos);
			pix->Red = GetRValue(*curdata);
			pix->Green = GetGValue(*curdata);
			pix->Blue = GetBValue(*curdata);
			curdata++;
		}
	}
	char szTempDir[MAX_PATH];
	GetTempPathA(MAX_PATH, szTempDir);
	char szTempName[MAX_PATH];
	GetTempFileName(szTempDir, "eb", 0, szTempName);
	bmp.WriteToFile(szTempName);
	CImage img;
	auto result = img.Load(szTempName);

	CPaintDC clientDC(wnd);
	CDC memDC; //  онтекст пам€ти
	// —оздать совместимый контекст пам€ти 
	memDC.CreateCompatibleDC(&clientDC);
	// ¬ыбрать битовый образ в контекст устройства
	memDC.SelectObject(HBITMAP(img));
	// ѕолучить характеристики битового образа в структуру BITMAP
	BITMAP bmp;
	backgroundBitmap.GetBitmap(&bmp);
	((CStatic*)wnd)->SetBitmap(HBITMAP(img));
	// —копировать битовый образ из контекста пам€ти в контекст 
	// клиентской области окна
	clientDC.BitBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &memDC,
		0, 0, SRCCOPY);
	 
	CPoint
	wnd->GetDC()->DrawState()
	Gdiplus::Graphics graphics(hdc);
	((CStatic*)wnd)->Draw
	((CStatic*)wnd)->SetBitmap(HBITMAP(img));
} // ////////////////////////////////////////////////////////////////////////////////////////////////
