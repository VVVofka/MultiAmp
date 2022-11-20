#pragma once
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "Utils.h"

using namespace concurrency::fast_math;
using namespace concurrency::direct3d;
class RunA{
	public:
		static void Create(std::vector<std::unique_ptr<Concurrency::array<int, 2>>> vgpu_a);
		static void Run(const Concurrency::array<int, 2>& src, Concurrency::array<int, 2>& dst, const Concurrency::array<int, 1>& mask);
		static void RunLast(INT2 shift, const Concurrency::array<int, 2>& src, Concurrency::array<int, 2>& dst, const Concurrency::array<int, 1>& mask);
}; // *********************************************************************************************************

