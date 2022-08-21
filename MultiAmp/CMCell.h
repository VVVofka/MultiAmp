#pragma once
#include <array>
#include <string>
class CMCell :public CStatic{
	DECLARE_DYNAMIC(CMCell)

protected:
	DECLARE_MESSAGE_MAP()

public:
	bool isExist = true;
	size_t idRotate = 0;

	int border = 0; // толщина линии границы
	int bound = 0;	// толщина области за border (граница)
	int arrowWidth = 1;

	bool isSymetryEnabled = false;
	bool isSymetry = true;

	int rotate(int direct = 1);
	//void invalidate();
	afx_msg void OnPaint();

	struct DBL2{
		double x=0, y=0;
		DBL2(double X, double Y){ x = X; y = Y; }
		DBL2(const CPoint& point){ x = point.x; y = point.y; }
		CPoint point(){ return CPoint((int)x, (int)y); }
	};

private:
	CRect room;
	COLORREF clrSolid();
	CRect rctArrow;
	const double kTipLenght = 0.4;	// 0.4
	const double kTipWidth = 0.12;	// 0.12

	void drawO(CPaintDC* pdc);
	void drawUp(CPaintDC* pdc);
	void drawUpRight(CPaintDC* pdc);
	void drawRight(CPaintDC* pdc);
	void drawDnRight(CPaintDC* pdc);
	void drawDn(CPaintDC* pdc);
	void drawDnLeft(CPaintDC* pdc);
	void drawLeft(CPaintDC* pdc);
	void drawUpLeft(CPaintDC* pdc);

	const double q = 0.7071067811865475;
	const size_t cntRotates = 9;
};

