#pragma once
#include "CMCell.h"
#include <array>

class CMCell4 : public CStatic{
	DECLARE_DYNAMIC(CMCell4)

public:
	CMCell4();
	virtual ~CMCell4();
	std::array<CMCell, 4> v;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


