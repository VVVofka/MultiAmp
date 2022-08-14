#include "pch.h"
#include "CMCell.h"
BEGIN_MESSAGE_MAP(CMCell, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMCell, CObject)

void CMCell::OnPaint(){
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
	// CStatic::OnPaint();

	// прямоугольник клиентской области
	CRect r_CL;
	GetClientRect(&r_CL);

	// определение высоты и ширины клиентской области
	int Hig = r_CL.Height();
	int Wid = r_CL.Width();

	// демонстрация системных цветов
	COLORREF colorGrey = ::GetSysColor(COLOR_BTNFACE);
	COLORREF colorLihg = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF colorShad = ::GetSysColor(COLOR_BTNSHADOW);
	COLORREF colorDeepShad = ::GetSysColor(COLOR_3DDKSHADOW);

	int f = 1; // толщина линии
	dc.FillSolidRect(0, 0, Wid, Hig, colorDeepShad);
	dc.FillSolidRect(0, 0, Wid - f, Hig - f, colorLihg);
	dc.FillSolidRect(f, f, Wid - f * 2, Hig - f * 2, colorShad);
	dc.FillSolidRect(f, f, Wid - f * 3, Hig - f * 3, colorGrey);

} // /////////////////////////////////////////////////////////////////////////////////
