#pragma once
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "Utils.h"

using namespace concurrency::fast_math;
using namespace concurrency::direct3d;

class RunD{
public:
	static void Run(const Concurrency::array<DrQuadro, 2>& srcd,
		Concurrency::array<DrQuadro, 2>& dstd,
		const Concurrency::array<int, 2>& dsta,
		const Concurrency::array<FLT2, 1>& masksD
	);
}; // **************************************************************************************************************
