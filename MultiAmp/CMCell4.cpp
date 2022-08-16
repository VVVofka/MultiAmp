#include "pch.h"
#include "MultiAmp.h"
#include "CMCell4.h"

BEGIN_MESSAGE_MAP(CMCell4, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMCell4, CStatic)

CMCell4::CMCell4(){} // //////////////////////////////////////////////////////////////////////////////////
CMCell4::~CMCell4(){} // //////////////////////////////////////////////////////////////////////////////////

// CMCell4 message handlers

void CMCell4::OnPaint(){
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell4::OnLButtonUp(UINT nFlags, CPoint point){
	CStatic::OnLButtonUp(nFlags, point);
	rotate(1, point);
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell4::OnRButtonUp(UINT nFlags, CPoint point){
	CStatic::OnRButtonUp(nFlags, point);
	rotate(-1, point);
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell4::rotate(int direct, CPoint point){
	CRect rctClient;
	GetClientRect(&rctClient);
	auto v1 = DevideRect4(rctClient);
	size_t i1 = getIdx4byPoint(rctClient, point);
	auto v4 = DevideRect4(v1[i1]);
	size_t i4 = getIdx4byPoint(v1[i1], point);
	size_t idx = i1 * 4 + i4;
	if(idx < v.size())
		v[idx].rotate(direct);
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell4::setDirect(size_t idx, const char* s0, const char* s1, const char* s2, const char* s3){
	for(size_t j = 0; j < v.size(); j++)
		v[j].isExist = ((idx & j) != 0);

} // //////////////////////////////////////////////////////////////////////////////////
std::array<CRect, 4> CMCell4::DevideRect4(const CRect& rect_base, int border){
	CRect noBorder = CRect(rect_base.left + border, rect_base.top + border, rect_base.right - border, rect_base.bottom - border);
	CPoint c = rect_base.CenterPoint(); 
	std::array<CRect, 4> ret;
	ret[0] = CRect(noBorder.TopLeft().x, noBorder.TopLeft().y, c.x,c.y);
	ret[1] = CRect(c.x-1, noBorder.top, noBorder.right, c.y);
	ret[2] = CRect(noBorder.left, c.y-1, c.x, noBorder.bottom);
	ret[3] = CRect(c.x-1, c.y-1, noBorder.BottomRight().x, noBorder.BottomRight().y);
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell4::create(){
	CRect rctClient;
	GetClientRect(&rctClient);
	//_RPT4(0, "rctClient: %d %d    %d %d\n", rctClient.left, rctClient.top, rctClient.right, rctClient.bottom);
	auto vrct4 = DevideRect4(rctClient, borderOut);
	for(size_t c4 = 0; c4 < 4; c4++){
		//_RPT5(0, "\tvrct4[%u]: %d x %d    %d x %d\n",c4, vrct4[c4].left, vrct4[c4].top, vrct4[c4].right, vrct4[c4].bottom);
		auto vrct1 = DevideRect4(vrct4[c4], borderInt);
		for(size_t c1 = 0; c1 < 4; c1++){
			size_t idx = c4 * 4 + c1;
			v[idx].Create("", WS_CHILD | WS_VISIBLE, vrct1[c1], this);
			//_RPT5(0, "\t\tvrct4[%u]: %d x %d    %d x %d\n", c1, vrct1[c1].left, vrct1[c1].top, vrct1[c1].right, vrct1[c1].bottom);
		}
	}
} // //////////////////////////////////////////////////////////////////////////////////////
size_t CMCell4::getIdx4byPoint(const CRect& rct, const CPoint& point){
	size_t x = (2 * (point.x - rct.left)) / rct.Width();
	size_t y = (2 * (point.y - rct.top)) / rct.Height();
	size_t idx = y * 2 + x;
	return idx;
} // //////////////////////////////////////////////////////////////////////////////////////
