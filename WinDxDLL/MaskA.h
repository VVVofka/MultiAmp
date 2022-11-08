#pragma once
#include <array>
#include <amp_graphics.h>
#include "..\OptsTinyLib\structAll.h"

using namespace Concurrency::graphics;

class MaskA{
public:
	std::array<int, 16> vcpu;
	const concurrency::array<int, 1>* vgpu;

	MaskA(structAll* cfg_all);
	~MaskA();

	bool load(const std::vector<int>& mask_A);	// 16
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
