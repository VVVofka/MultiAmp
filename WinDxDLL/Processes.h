#pragma once
#include "ProcessA.h"
#include "ProcessF.h"
#include "..\OptsTinyLib\structAll.h"
#include "Lays.h"
#include "MasksAll.h"

class Processes{
public:
	Processes(structAll* p_cfg_all, Lays* p_lays);
	ProcessA processA;
	ProcessF processF;
	Lays* lays;
	MasksAll masks;
	structAll* cfg_all;

	void RunAll(const int_2 shift);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
