#pragma once
#include <array>
#include "CMCell4.h"
using namespace std;
class CMCell16 : public CStatic{
	DECLARE_DYNAMIC(CMCell16)

public:
	CMCell16(){};
	virtual ~CMCell16(){};

	array<CMCell, 4 * 4> v;
	size_t id = 0;

	void setId(size_t id);

	virtual void PreSubclassWindow();

protected:
	DECLARE_MESSAGE_MAP()
};

