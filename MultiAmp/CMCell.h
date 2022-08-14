#pragma once
#include <array>
class CMCell :public CStatic{
	//	CMCell(CWnd* pParent = nullptr);	// standard constructor
	CRect room;

	DECLARE_DYNAMIC(CMCell)
public:
	bool isExist = true;
	int idx = 0;
	//void setDirect(int X, int Y);
	int nextIdx(int direct = 1);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	struct DBL2{
		double x=0, y=0;
		DBL2(double X, double Y){ x = X; y = Y; }
		DBL2(const CPoint& point){ x = point.x; y = point.y; }
		CPoint point(){ return CPoint((int)x, (int)y); }
	};

private:
	COLORREF clrSolid();
	CRect rctArrow;
	const double kTipLenght = 0.35;	// 0.35
	const double kTipWidth = 0.05;	// 0.05

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
	std::array<DBL2, 9> varrays = {DBL2(0,0),
		DBL2(0,-1), DBL2(q,-q),
		DBL2(1, 0), DBL2(q, q),
		DBL2(0, 1), DBL2(-q, q),
		DBL2(-1, 0), DBL2(-q,-q)
	};
	//double normDirect(double X);
};

