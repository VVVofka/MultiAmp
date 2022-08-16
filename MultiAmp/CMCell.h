#pragma once
#include <array>
#include <string>
class CMCell :public CStatic{
	DECLARE_DYNAMIC(CMCell)

protected:
	DECLARE_MESSAGE_MAP()

public:
	bool isExist = true;
	int idx = 0;

	int border = 0; // толщина линии границы
	int bound = 0;	// толщина области за border (граница)

	void setDirect(const char* s);
	int rotate(int direct = 1);
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
	std::array<DBL2, 9> varrays = {DBL2(0,0),
		DBL2(0,-1), DBL2(q,-q),
		DBL2(1, 0), DBL2(q, q),
		DBL2(0, 1), DBL2(-q, q),
		DBL2(-1, 0), DBL2(-q,-q)
	};
	//const std::array<std::string, 9> sidx = {"00", 
	//	"0-", "+-",
	//	"+0", "++",
	//	"0+", "-+",
	//	"-0", "--"
	//};
	void setDirect(int X, int Y);
};

