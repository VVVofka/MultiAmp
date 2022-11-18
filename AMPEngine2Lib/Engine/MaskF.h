#pragma once
#include <array>
#include <amp_graphics.h>
#include <amprt.h>
#include "..\..\OptsTinyLib\structAll.h"

using namespace Concurrency;
using namespace Concurrency::graphics;
class MaskF{
public:
	std::array<float_2, 256> vcpu;
	const concurrency::array<float_2, 1>* vgpu;	

	MaskF(structAll* cfg_all, accelerator_view* m_accl_view);
	~MaskF();

	void dump();
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
