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

	// ������������� ���������� �������
	CRect r_CL;
	GetClientRect(&r_CL);

	// ����������� ������ � ������ ���������� �������
	int Hig = r_CL.Height();
	int Wid = r_CL.Width();
	CRect wndClient = CRect(0, 0, Wid - 1, Hig - 1);

	// ������������ ��������� ������
	COLORREF colorGrey = ::GetSysColor(COLOR_BTNFACE);	// back
	COLORREF colorLihg = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF colorShad = ::GetSysColor(COLOR_BTNSHADOW);
	COLORREF colorDeepShad = ::GetSysColor(COLOR_3DDKSHADOW);

	int border = 1; // ������� �����
	int bound = 1;
	int brdline = bound + border / 2;
	CRect rctLine(wndClient.left + brdline, wndClient.top + brdline, wndClient.right - brdline, wndClient.bottom - brdline);

	// fill background
	CRect rctSolid(rctLine.left + 1, rctLine.top + 1, rctLine.right, rctLine.bottom);
	dc.FillSolidRect(rctSolid, clrSolid());	//	colorShad

	// Draw border
	CPen m_ShadPen(PS_SOLID, border, GREY(155));	// colorShad
	CPen* olpPen = dc.SelectObject(&m_ShadPen);		// ���������� ������� ����
	dc.MoveTo(rctLine.left, rctLine.top);	//	 - border / 2
	dc.LineTo(rctLine.right, rctLine.top);
	dc.LineTo(rctLine.right, rctLine.bottom);
	dc.LineTo(rctLine.left, rctLine.bottom);
	dc.LineTo(rctLine.left, rctLine.top);	//	 - border / 2
	dc.SelectObject(olpPen);	// ������� ������� ����

	int d = (int)(border * 0.5 + 0.5);
	room.left = rctLine.left + d;
	room.right = rctLine.right - border / 2 - 1;
	room.top = rctLine.top + d;
	room.bottom = rctLine.bottom - border / 2 - 1;	// - border / 2 - 1

	double karrow = 0.9 * 0.5;
	rctArrow = CRect(
		room.CenterPoint().x - (int)(room.Width() * karrow + 0.5),
		room.CenterPoint().y - (int)(room.Height() * karrow + 0.5),
		room.CenterPoint().x + (int)(room.Width() * karrow + 0.5),
		room.CenterPoint().y + (int)(room.Height() * karrow + 0.5)
		);

	CPen penArrow(PS_SOLID, 3, GREY(100));	// colorShad
	CPen* oldPenArrow = dc.SelectObject(&penArrow);		// ���������� ������� ����
	if(x == 0 && y == 0)
		drawO(&dc);
	else if(x == 0 && y == -1)
		drawUp(&dc);
	dc.SelectObject(oldPenArrow);	// ������� ������� ����

	//CPen mShadPen(PS_SOLID, 1, RGB(0, 0, 0));	// colorShad
	//CPen* olpPen1 = dc.SelectObject(&mShadPen);		// ���������� ������� ����
	//dc.MoveTo(room.left, room.top);
	//dc.LineTo(room.right, room.top);
	//dc.LineTo(room.right, room.bottom);
	//dc.LineTo(room.left, room.bottom);
	//dc.LineTo(room.left, room.top);
	//dc.SelectObject(olpPen1);	// ������� ������� ����
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
	CBrush* olpBrush = pdc->SelectObject(&brush);		// ���������� ������� ����
	double kw = room.Width() * 0.3;
	double kh = room.Height() * 0.3;
	CRect eli((room.left + kw), (int)(room.top + kh), (int)(room.right - kw), (int)(room.bottom - kh));
	auto err = pdc->Ellipse(eli);
	pdc->SelectObject(brush);	// ������� ������� ����
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawUp(CPaintDC* pdc){
	pdc->MoveTo(rctArrow.CenterPoint().x, rctArrow.bottom);	//	 - border / 2
	CPoint nip(rctArrow.CenterPoint().x, rctArrow.top);
	pdc->LineTo(nip);
	int dx = (int)(rctArrow.Height() * 0.05 + 0.5);
	int dy = (int)(rctArrow.Width() * 0.35 + 0.5);
	pdc->LineTo(nip.x - dx, nip.y + dy);
	pdc->MoveTo(nip);	
	pdc->LineTo(nip.x + dx, nip.y + dy);
} // ///////////////////////////////////////////////////////////////////////////////////
