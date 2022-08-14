#pragma once
class CMCell :public CStatic{
	//	CMCell(CWnd* pParent = nullptr);	// standard constructor
	CRect room;

	DECLARE_DYNAMIC(CMCell)
public:
	bool isExist = true;
	int x = 0, y = 0;	//direct -1,0,+1
	void setDirect(int X, int Y);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
	void drawO(CPaintDC* pdc);
	void drawUp(CPaintDC* pdc);
	COLORREF clrSolid();
	CRect rctArrow;

};

