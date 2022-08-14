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
	if(idx == 0)		drawO(&dc);
	else if(idx == 1)	drawUp(&dc);
	else if(idx == 2)	drawUpRight(&dc);
	else if(idx == 3)	drawRight(&dc);
	else if(idx == 4)	drawDnRight(&dc);
	else if(idx == 5)	drawDn(&dc);
	else if(idx == 6)	drawDnLeft(&dc);
	else if(idx == 7)	drawLeft(&dc);
	else if(idx == 8)	drawUpLeft(&dc);
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
//void CMCell::setDirect(int X, int Y){
//	x = normDirect(X);
//	y = normDirect(Y);
//	InvalidateRect(room, TRUE);
//} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawO(CPaintDC* pdc){	//+
	CBrush brush(clrSolid());
	CBrush* olpBrush = pdc->SelectObject(&brush);		// ���������� ������� ����
	double kw = room.Width() * kTipLenght;
	double kh = room.Height() * 0.3;
	CRect eli((int)(room.left + kw), (int)(room.top + kh), (int)(room.right - kw), (int)(room.bottom - kh));
	auto err = pdc->Ellipse(eli);
	pdc->SelectObject(brush);	// ������� ������� ����
} // ///////////////////////////////////////////////////////////////////////////////////

void CMCell::drawUp(CPaintDC* pdc){	//+
	pdc->MoveTo(rctArrow.CenterPoint().x, rctArrow.bottom);	//	 - border / 2
	CPoint nip(rctArrow.CenterPoint().x, rctArrow.top);
	pdc->LineTo(nip);
	int dx = (int)(rctArrow.Height() * kTipWidth + 0.5);
	int dy = (int)(rctArrow.Width() * kTipLenght + 0.5);
	pdc->LineTo(nip.x - dx, nip.y + dy);
	pdc->MoveTo(nip);
	pdc->LineTo(nip.x + dx, nip.y + dy);
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawUpRight(CPaintDC* pdc){
	DBL2 C(rctArrow.CenterPoint());
	double R = ((C.x - (double)rctArrow.left) + (C.y - (double)rctArrow.top)) * 0.5;
	double dg = 0.5 * R * q * (1 - kTipLenght);
	DBL2 drain(C.x - 1.2 * R * q, C.y + 1.2 * R * q);
	DBL2 nip(C.x + 1.2 * R * q, C.y - 1.2 * R * q);
	DBL2 Gnip(C.x + 1.4 * dg, C.y - 1.4 * dg);
	double dwidth = rctArrow.Height() * kTipWidth * q;
	pdc->MoveTo(drain.point());
	pdc->LineTo(nip.point());
	pdc->LineTo((int)(Gnip.x - dwidth), (int)(Gnip.y - dwidth));
	pdc->MoveTo(nip.point());
	pdc->LineTo((int)(Gnip.x + dwidth), (int)(Gnip.y + dwidth));
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawRight(CPaintDC* pdc){	//+
	pdc->MoveTo(rctArrow.left, rctArrow.CenterPoint().y);
	CPoint nip(rctArrow.right, rctArrow.CenterPoint().y);
	pdc->LineTo(nip);
	int dx = (int)(rctArrow.Height() * kTipLenght + 0.5);
	int dy = (int)(rctArrow.Width() * kTipWidth + 0.5);
	pdc->LineTo(nip.x - dx, nip.y + dy);
	pdc->MoveTo(nip);
	pdc->LineTo(nip.x - dx, nip.y - dy);
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawDnRight(CPaintDC* pdc){
	DBL2 C(rctArrow.CenterPoint());
	double R = ((C.x - (double)rctArrow.left) + (C.y - (double)rctArrow.top)) * 0.5;
	double dg = 0.5 * R * q * (1 - kTipLenght);
	DBL2 drain(C.x - 1.2 * R * q, C.y - 1.2 * R * q);
	DBL2 nip(C.x + 1.2 * R * q, C.y + 1.2 * R * q);
	DBL2 Gnip(C.x + 1.4 * dg, C.y + 1.4 * dg);
	double dwidth = rctArrow.Height() * kTipWidth * q;
	pdc->MoveTo(drain.point());
	pdc->LineTo(nip.point());
	CPoint a1((int)(Gnip.x + dwidth), (int)(Gnip.y - dwidth));
	pdc->LineTo(a1);
	pdc->MoveTo(nip.point());
	CPoint a2((int)(Gnip.x - dwidth), (int)(Gnip.y + dwidth));
	pdc->LineTo(a2);
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawDn(CPaintDC* pdc){	//+
	pdc->MoveTo(rctArrow.CenterPoint().x, rctArrow.top);
	CPoint nip(rctArrow.CenterPoint().x, rctArrow.bottom);
	pdc->LineTo(nip);
	int dx = (int)(rctArrow.Height() * kTipWidth + 0.5);
	int dy = (int)(rctArrow.Width() * kTipLenght + 0.5);
	pdc->LineTo(nip.x - dx, nip.y - dy);
	pdc->MoveTo(nip);
	pdc->LineTo(nip.x + dx, nip.y - dy);
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawDnLeft(CPaintDC* pdc){
	DBL2 C(rctArrow.CenterPoint());
	double R = ((C.x - (double)rctArrow.left) + (C.y - (double)rctArrow.top)) * 0.5;
	double dg = 0.5 * R * q * (1 - kTipLenght);
	DBL2 drain(C.x + 1.2 * R * q, C.y - 1.2 * R * q);
	DBL2 nip(C.x - 1.2 * R * q, C.y + 1.2 * R * q);
	DBL2 Gnip(C.x - 1.4 * dg, C.y + 1.4 * dg);
	double dwidth = rctArrow.Height() * kTipWidth * q;
	pdc->MoveTo(drain.point());
	pdc->LineTo(nip.point());
	pdc->LineTo((int)(Gnip.x + dwidth), (int)(Gnip.y + dwidth));
	pdc->MoveTo(nip.point());
	pdc->LineTo((int)(Gnip.x - dwidth), (int)(Gnip.y - dwidth));
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawLeft(CPaintDC* pdc){	//+
	pdc->MoveTo(rctArrow.right, rctArrow.CenterPoint().y);
	CPoint nip(rctArrow.left, rctArrow.CenterPoint().y);
	pdc->LineTo(nip);
	int dx = (int)(rctArrow.Height() * kTipLenght + 0.5);
	int dy = (int)(rctArrow.Width() * kTipWidth + 0.5);
	pdc->LineTo(nip.x + dx, nip.y + dy);
	pdc->MoveTo(nip);
	pdc->LineTo(nip.x + dx, nip.y - dy);
} // ///////////////////////////////////////////////////////////////////////////////////
void CMCell::drawUpLeft(CPaintDC* pdc){
	DBL2 C(rctArrow.CenterPoint());
	double R = ((C.x - (double)rctArrow.left) + (C.y - (double)rctArrow.top)) * 0.5;
	double dg = 0.5 * R * q * (1 - kTipLenght);
	DBL2 drain(C.x + 1.2 * R * q, C.y + 1.2 * R * q);
	DBL2 nip(C.x - 1.2 * R * q, C.y - 1.2 * R * q);
	DBL2 Gnip(C.x - 1.4 * dg, C.y - 1.4 * dg);
	double dwidth = rctArrow.Height() * kTipWidth * q;
	pdc->MoveTo(drain.point());
	pdc->LineTo(nip.point());
	CPoint a1((int)(Gnip.x + dwidth), (int)(Gnip.y - dwidth));
	pdc->LineTo(a1);
	pdc->MoveTo(nip.point());
	CPoint a2((int)(Gnip.x - dwidth), (int)(Gnip.y + dwidth));
	pdc->LineTo(a2);
} // ///////////////////////////////////////////////////////////////////////////////////
//double CMCell::normDirect(double val){
//	if(val < -0.8535533905932738)		return -1;
//	if(val < -0.3535533905932738)		return -q;
//	if(val > +0.8535533905932738)		return +1;
//	if(val > +0.3535533905932738)		return +q;
//	return 0.0;
//} // ///////////////////////////////////////////////////////////////////////////////////
int CMCell::nextIdx(int direct){
	idx = (idx + direct + varrays.size()) % varrays.size();
	InvalidateRect(room, TRUE);
	return idx;
} // ///////////////////////////////////////////////////////////////////////////////////
