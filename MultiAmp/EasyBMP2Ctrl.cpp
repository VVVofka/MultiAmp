#include "pch.h"
#include "EasyBMP2Ctrl.h"

void EasyBMP2Ctrl::load(CWnd* wnd, size_t data_size_x, size_t data_size_y, COLORREF* data){
	size_t data_size = data_size_x * data_size_y;
	CPaintDC dc(wnd);
	CRect r_CL;	// прямоугольник клиентской области
	wnd->GetClientRect(&r_CL);		//	m_screen.GetClientRect(&r_CL);

	// определение высоты и ширины клиентской области
	int rclWidth = r_CL.Width();
	int rclHeight = r_CL.Height();
	double kx = (double)rclWidth / data_size_x;
	double ky = (double)rclHeight/ data_size_y;

	BMP bmp;
	bmp.SetSize(rclWidth, rclHeight);
	bmp.SetBitDepth(24);

	COLORREF* curdata = data;
	for(size_t ypos = 0; ypos < data_size_y; ypos++){
		int y = int(ky * ypos);
		for(size_t xpos = 0; xpos < data_size_x; xpos++){
			int x = int(kx * xpos);
			auto pix = bmp(x, y);
			pix->Red = GetRValue(*curdata);
			pix->Green = GetRValue(*curdata);
			pix->Blue = GetRValue(*curdata);
			curdata++;
		}
	}
	char szTempName[MAX_PATH];
	GetTempFileName("", "eb", 0, szTempName);
	bmp.WriteToFile(szTempName);
	CImage img;
	img.Load(szTempName);
	((CStatic*)wnd)->SetBitmap(HBITMAP(img));
} // ////////////////////////////////////////////////////////////////////////////////////////////////
