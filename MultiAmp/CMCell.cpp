#include "pch.h"
#include "CMCell.h"
#define GREY(A) (RGB((A), (A), (A)))
BEGIN_MESSAGE_MAP(CMCell, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMCell, CObject)

COLORREF CMCell::clrSolid(){
	return isExist ? GREY(222) : GREY(255); 
} // //////////////////////////////////////////////////////////////////////
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
	CRect wndClient = CRect(0, 0, Wid - 1, Hig - 1);

	// демонстрация системных цветов
	COLORREF colorGrey = ::GetSysColor(COLOR_BTNFACE);	// back
	COLORREF colorLihg = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF colorShad = ::GetSysColor(COLOR_BTNSHADOW);
	COLORREF colorDeepShad = ::GetSysColor(COLOR_3DDKSHADOW);

	int border = 1; // толщина линии
	int bound = 1;
	int brdline = bound + border / 2;
	CRect rctLine(wndClient.left + brdline, wndClient.top + brdline, wndClient.right - brdline, wndClient.bottom - brdline);

	// fill background
	CRect rctSolid(rctLine.left + 1, rctLine.top + 1, rctLine.right, rctLine.bottom);
	dc.FillSolidRect(rctSolid, clrSolid());	//	colorShad

	// Draw border
	CPen m_ShadPen(PS_SOLID, border, GREY(155));	// colorShad
	CPen* olpPen = dc.SelectObject(&m_ShadPen);		// сохранение старого пера
	dc.MoveTo(rctLine.left, rctLine.top);	//	 - border / 2
	dc.LineTo(rctLine.right, rctLine.top);
	dc.LineTo(rctLine.right, rctLine.bottom);
	dc.LineTo(rctLine.left, rctLine.bottom);
	dc.LineTo(rctLine.left, rctLine.top);	//	 - border / 2
	dc.SelectObject(olpPen);	// возврат старого пера

	int d = (int)(border * 0.5 + 0.5);
	room.left = rctLine.left + d;
	room.right = rctLine.right - border / 2 - 1;
	room.top = rctLine.top + d;
	room.bottom = rctLine.bottom - border / 2 - 1;	// - border / 2 - 1

	CPen penArrow(PS_SOLID, 1, GREY(100));	// colorShad
	CPen* oldPenArrow = dc.SelectObject(&penArrow);		// сохранение старого пера
	if(x == 0 && y == 0)
		drawO(&dc);
	else if(x == 0 && y == -1)
		drawUp(&dc);
	dc.SelectObject(oldPenArrow);	// возврат старого пера

	//CPen mShadPen(PS_SOLID, 1, RGB(0, 0, 0));	// colorShad
	//CPen* olpPen1 = dc.SelectObject(&mShadPen);		// сохранение старого пера
	//dc.MoveTo(room.left, room.top);
	//dc.LineTo(room.right, room.top);
	//dc.LineTo(room.right, room.bottom);
	//dc.LineTo(room.left, room.bottom);
	//dc.LineTo(room.left, room.top);
	//dc.SelectObject(olpPen1);	// возврат старого пера
} // /////////////////////////////////////////////////////////////////////////////////
// +->
// |
// V
void CMCell::setDirect(int X, int Y){
	x = X < 0 ? -1 : X > 0 ? 1 : 0;
	y = Y < 0 ? -1 : Y > 0 ? 1 : 0;
	InvalidateRect(room, TRUE);
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawO(CPaintDC* pdc){
	CBrush brush(clrSolid());
	CBrush* olpBrush = pdc->SelectObject(&brush);		// сохранение старого пера
	double kw = room.Width() * 0.3;
	double kh = room.Height() * 0.3;
	CRect eli(room.left + kw, room.top + kh, room.right - kw, room.bottom - kh);
	auto err = pdc->Ellipse(eli);
	pdc->SelectObject(brush);	// возврат старого пера
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawUp(CPaintDC* pdc){
	CBrush m_Brush(clrSolid());
	CBrush* olpBrush = pdc->SelectObject(&m_Brush);		// сохранение старого пера
	double kw = room.Width() * 0.4;
	double kh = room.Height() * 0.4;
	CRect eli(room.left + kw, room.top + kh, room.right - kw, room.bottom - kh);
	auto err = pdc->Ellipse(eli);
	pdc->SelectObject(m_Brush);	// возврат старого пера
} // ///////////////////////////////////////////////////////////////////////////////////
