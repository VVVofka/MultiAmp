#pragma once
#ifdef MODEA
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "Utils.h"
//#include "Options.h"
using namespace concurrency;
using namespace concurrency::fast_math;
using namespace concurrency::direct3d;
class RunA{
	public:
		static void Create(std::vector<std::unique_ptr<array<int, 2>>> ar_areas);
		static void Run(const array<int, 2>& src, array<int, 2>& dst, const array<int, 1>& mask);
		//static void RunConst(const array<int, 2>& src, array<int, 2>& dst, const WraperMask& mask);
		static void RunLast(INT2 shift, const array<int, 2>& src, array<int, 2>& dst, const array<int, 1>& mask);
}; // *********************************************************************************************************
#endif  // MODEA

