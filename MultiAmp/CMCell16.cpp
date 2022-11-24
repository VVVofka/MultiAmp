#include "pch.h"
#include "MultiAmp.h"
#include "CMCell16.h"

BEGIN_MESSAGE_MAP(CMCell16, CStatic)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMCell16, CStatic)

void CMCell16::OnLButtonUp(UINT nFlags, CPoint point){
	CStatic::OnLButtonUp(nFlags, point);
	rotate(-1, point);
	if(isSymmetryMode)
		rotateSymmetry();
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell16::OnRButtonUp(UINT nFlags, CPoint point){
	CStatic::OnRButtonUp(nFlags, point);
	rotate(1, point);
	if(isSymmetryMode)
		rotateSymmetry();
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell16::rotate(int direct, CPoint point){
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
std::array<CRect, 4> CMCell16::DevideRect4(const CRect& rect_base, int border){
	CRect noBorder = CRect(rect_base.left + border, rect_base.top + border, rect_base.right - border, rect_base.bottom - border);
	CPoint c = rect_base.CenterPoint();
	std::array<CRect, 4> ret;
	ret[0] = CRect(noBorder.TopLeft().x, noBorder.TopLeft().y, c.x, c.y);
	ret[1] = CRect(c.x - 1, noBorder.top, noBorder.right, c.y);
	ret[2] = CRect(noBorder.left, c.y - 1, c.x, noBorder.bottom);
	ret[3] = CRect(c.x - 1, c.y - 1, noBorder.BottomRight().x, noBorder.BottomRight().y);
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////
void CMCell16::create(size_t mask, const char* id_rotate){
	setIdMaskF(mask);
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
	setRotates(id_rotate);
} // //////////////////////////////////////////////////////////////////////////////////////
size_t CMCell16::getIdx4byPoint(const CRect& rct, const CPoint& point){
	size_t x = (2 * (point.x - rct.left)) / rct.Width();
	size_t y = (2 * (point.y - rct.top)) / rct.Height();
	size_t idx = y * 2 + x;
	return idx;
} // //////////////////////////////////////////////////////////////////////////////////////
void CMCell16::setIdMaskF(size_t i){
	for(size_t j = 0; j < v.size(); j++){
		size_t nq = j / 4;
		v[j].isExist = (((i >> nq) & 1) == 1);
	}
} // //////////////////////////////////////////////////////////////////////////////////////
void CMCell16::setRotates(const char* id_rotate){
	//const size_t vidx[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
	char buf[] = "\0";
	for(size_t j = 0; j < v.size(); j++){
		//	const size_t conv_j = vidx[j];
		buf[0] = id_rotate[j];
		v[j].idRotate = (size_t)atol(buf);
	}
} // //////////////////////////////////////////////////////////////////////////////////////
void CMCell16::setEnabled(size_t idx_cell, bool isEnabled){
	v[idx_cell].setEnabled(isEnabled);
} // //////////////////////////////////////////////////////////////////////////////////////
void CMCell16::setEnabled(bool isEnabled){
	for(size_t j = 0; j < v.size(); j++)
		v[j].setEnabled(isEnabled);
} // //////////////////////////////////////////////////////////////////////////////////////
void CMCell16::rotateSymmetry(){
	size_t mask = (v[12].isExist ? 0b1000 : 0) + (v[8].isExist ? 0b0100 : 0) + (v[4].isExist ? 0b0010 : 0) + (v[0].isExist ? 0b0001 : 0);
	std::array< size_t, 16> vr;
	for(size_t j = 0; j < v.size(); j++)
		vr[j] = v[j].idRotate;
	fills.fill(mask, vr);
	for(size_t j = 0; j < v.size(); j++)	//	16
		v[j].setRotateNonEnabled(fills.vout[j].i);

	CMCell16* src = this;
	for(size_t j = 0; j < vretsym.size(); j++){	//	4
		CMCell16* dst = vretsym[j];
		rotate16(src, dst);
		src = dst;
	}
} // //////////////////////////////////////////////////////////////////////////////////////
void CMCell16::rotate16(const CMCell16* src, CMCell16* dst){
	const size_t vrot[16] = {5,7,4,6,13,15,12,14,1,3,0,2,9,11,8,10};
	const std::array<CMCell, 16>& v_src = src->v;
	std::array<CMCell, 16>& v_dst = dst->v;
	for(size_t idx_src = 0; idx_src < 16; idx_src++){
		const CMCell& cell_src = v_src[idx_src];
		size_t idx_dst = vrot[idx_src];
		CMCell& cell_dst = v_dst[idx_dst];
		if(cell_src.idRotate > 6)
			cell_dst.idRotate = cell_src.idRotate - 6;
		else if(cell_src.idRotate != 0)
			cell_dst.idRotate = cell_src.idRotate + 2;
		else
			cell_dst.idRotate = 0;
		cell_dst.invalidateRect();
	}
} // //////////////////////////////////////////////////////////////////////////////////////
