#pragma once
#include <array>
#include <amp_graphics.h>
#include <amprt.h>
#include "..\..\OptsTinyLib\structAll.h"

using namespace Concurrency;
using namespace Concurrency::graphics;
class MaskA{
public:
	std::array<int, 16> vcpu;
	const concurrency::array<int, 1>* vgpu;

	MaskA(const structAll* cfg_all, accelerator_view* m_accl_view);
	~MaskA();

private:
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
