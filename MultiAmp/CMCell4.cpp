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
void CMCell4::PreSubclassWindow(){
	CRect rctClient;
	GetClientRect(&rctClient);
	auto w = rctClient.Width() / 2;
	auto h = rctClient.Height() / 2;
	CRect vrct[4] = {
		CRect(0, 0, w,   h),
		CRect(w, 0, w * 2, h),
		CRect(0, h, w,   h * 2),
		CRect(w, h, w * 2, h * 2)
	};
	for(int j = 0; j < (int)v.size(); j++)
		v[j].Create("", WS_CHILD | WS_VISIBLE, vrct[j], this);

	CStatic::PreSubclassWindow();
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
	size_t x = (2 * point.x) / rctClient.Width();
	size_t y = (2 * point.y) / rctClient.Height();
	size_t idx = y * 2 + x;
	if(idx < v.size())
		v[idx].rotate(direct);
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell4::setDirect(size_t idx, const char* s0, const char* s1, const char* s2, const char* s3){
	for(size_t j = 0; j < v.size(); j++)
		v[j].isExist = ((idx & j) != 0);

} // //////////////////////////////////////////////////////////////////////////////////

