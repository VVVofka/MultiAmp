#pragma once
#include <amprt.h>
#include "..\..\OptsTinyLib\structAll.h"
#include "MaskA.h"
#include "MaskF.h"

class MasksAll{
public:
	MasksAll(structAll* p_cfg_all, Concurrency::accelerator_view* m_accl_view);
	MaskA a;
	MaskF f;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

