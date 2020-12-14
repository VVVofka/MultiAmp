#pragma once
#ifdef MODEA
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "Utils.h"
using namespace concurrency;
using namespace concurrency::fast_math;
using namespace concurrency::direct3d;
class RunA{
	public:
		static void Run(const array<int, 2>& src, array<int, 2>& dst, const array<int, 1>& mask);
		static void RunLast(INT2 shift, const array<int, 2>& src, array<int, 2>& dst, const array<int, 1>& mask);
}; // *********************************************************************************************************
#endif  // MODEA

