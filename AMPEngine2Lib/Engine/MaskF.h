#pragma once
#include <array>
#include <vector>
#include <amp_graphics.h>
#include "..\..\OptsTinyLib\structAll.h"

using namespace Concurrency::graphics;
class MaskF{
public:
	std::array<float_2, 16 * 4> vcpu;
	const concurrency::array<float_2, 2>* vgpu = NULL;	// amp maskF 16 * 4 float_2

	MaskF(structAll* cfg_all);
	~MaskF();

	void dump();

private:
	void create(const std::vector<float>& val);
	void create(const std::vector<float_2>& val);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
