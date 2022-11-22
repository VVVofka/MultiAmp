#pragma once
#include <Windows.h>
#include "..\OptsTinyLib\structAll.h"
#include "MDX/MDX2.h"

namespace eng2{
		extern MDX2 mdx;
		int runEngine2Lib(structAll* cfg_all, HINSTANCE hInstance = NULL, int nCmdShow = SW_SHOWDEFAULT);
} // namespace eng2 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@