#pragma once
#include "CMCell.h"
#include <array>

class CMCell4 : public CStatic{
	DECLARE_DYNAMIC(CMCell4)
protected:
	DECLARE_MESSAGE_MAP()

public:
	CMCell4(){};
	virtual ~CMCell4(){};
	std::array<CMCell, 16> v;
	void create();

	void setIdMaskF(size_t idx);
	//cnt=16, 0-none; 1-up; 2-up,right .. 8-up,left
	void setRotates(const int* id_rotate);
	void setRotates(const char* id_rotate);

	int borderOut = 1;
	int borderInt = 2;

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:
	void rotate(int direct, CPoint point); // for OnLButtonUp OnRButtonUp
	std::array<CRect,4> DevideRect4(const CRect& rect_base, int border = 0);
	size_t getIdx4byPoint(const CRect& rct, const CPoint& point);
};


