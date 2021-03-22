#pragma once
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "Utils.h"

using namespace concurrency;
using namespace concurrency::fast_math;
using namespace concurrency::direct3d;

class RunD{
public:
	static void Run(const array<DrQuadro, 2>& srcd,
                    array<DrQuadro, 2>& dstd,
                    const array<int, 2>& dsta, 
                    const array<FLT2, 1>& masksD
                    );
}; // **************************************************************************************************************
