#pragma once
#include "ProcessA.h"
#include "ProcessF.h"
#include "..\OptsTinyLib\structAll.h"
#include "Lays.h"

class Processes{
public:
	Processes(structAll* p_cfg_all, Lays* p_lays);
	ProcessA processA;
	ProcessF processF;
	Lays* lays;
	structAll* cfg_all;

	void Create(Lays* p_lays, MaskA* p_Mask_a, MaskF* p_Masks_f);
	void RunAll(const int_2 shift);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
