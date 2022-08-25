#pragma once
#include <array>
#include <vector>
#include "CMCell.h"
#include "CellsFillSym.h"

class CMCell16 : public CStatic{
	DECLARE_DYNAMIC(CMCell16)
protected:
	DECLARE_MESSAGE_MAP()

public:
	CMCell16(){};
	virtual ~CMCell16(){};
	std::array<CMCell, 16> v;
	CellsFillSym fills;
	std::vector<CMCell16*> vretsym;
	bool isSymmetryMode = true;

	//cnt=16, 0-none; 1-up; 2-up,right .. 8-up,left
	void create(size_t mask, const char* id_rotate);
	void setEnabled(size_t idx_cell, bool isEnabled);
	void setEnabled(bool isEnabled);
	void rotate16(const CMCell16* src, CMCell16* dst);

	int borderOut = 0;
	int borderInt = 1;

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:
	void setRotates(const char* id_rotate);
	void setIdMaskF(size_t idx);
	void rotate(int direct, CPoint point); // for OnLButtonUp OnRButtonUp
	std::array<CRect, 4> DevideRect4(const CRect& rect_base, int border = 0);
	size_t getIdx4byPoint(const CRect& rct, const CPoint& point);
	void rotateSymmetry();
};


