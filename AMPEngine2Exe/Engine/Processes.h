#pragma once
#include "ProcessA.h"
#include "ProcessF.h"
#include "Lays.h"
//#include "MasksAll.h"
#include "..\myRnd.h"
#include "..\..\OptsTinyLib\structAll.h"

class Processes{
public:
	Processes(structAll* p_cfg_all, Lays* p_lays);
	~Processes();

	ProcessA processA;
	ProcessF processF;
	//MasksAll masks;
	structAll* cfg_all;

	void RunAll();

private:
	LehmerRng rnd;
	uint64_t curIteration;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
