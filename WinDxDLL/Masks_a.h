#pragma once
#include <array>
#include <amp_graphics.h>
using namespace Concurrency::graphics;

class Masks_a{
public:
	std::array<int, 16> v;
	const concurrency::array<int, 1>* gv;

	Masks_a();
	~Masks_a();

	bool load(const std::vector<int>& mask_A);	// 16
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
