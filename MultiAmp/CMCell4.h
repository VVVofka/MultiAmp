#pragma once
#include "CMCell.h"
#include <array>

class CMCell4 : public CStatic{
	DECLARE_DYNAMIC(CMCell4)

public:
	CMCell4();
	virtual ~CMCell4();
	std::array<CMCell, 4> v;
	void setDirect(size_t idx, const char* s0, const char* s1, const char* s2, const char* s3);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual void PreSubclassWindow();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
private:
	void rotate(int direct, CPoint point);
};


