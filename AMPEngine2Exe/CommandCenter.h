#pragma once
#include "..\OptsTinyLib\structAll.h"
#include "MDX/MDX2.h"
//#include "..\MultiAmp\MultiAmpDlg.h"

class CommandCenter{
public:
	structAll structall;
	INT64 tick_cnt = -1;
	MDX2 mdx;
	//CMultiAmpDlg dlgOptions;
	void OptDlg();
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

