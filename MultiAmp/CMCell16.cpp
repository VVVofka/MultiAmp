#include "pch.h"
#include "CMCell16.h"

BEGIN_MESSAGE_MAP(CMCell16, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMCell16, CStatic)


void CMCell16::setId(size_t id){
	this->id = id;
	for(size_t j = 0; j < v.size(); j++){
		bool isexist = (((id >> j) & 1) == 1);
		//v[j].ise
	}
} // ////////////////////////////////////////////////////////////////
void CMCell16::PreSubclassWindow(){
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
	for(int c4 = 0; c4 < 4; c4++){

	}
	for(int j = 0; j < (int)v.size(); j++)
		v[j].Create("", WS_CHILD | WS_VISIBLE, vrct[j], this);

	CStatic::PreSubclassWindow();
} // //////////////////////////////////////////////////////////////////////////////////
