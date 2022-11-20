#pragma once
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "Vertex.h"
#include "Utils.h"

using namespace concurrency::fast_math;
using namespace concurrency::direct3d;

class RunDlast{
public:
	static void Run(const INT2 shift,
		const Concurrency::array<DrQuadro, 2>& srcd,
		Concurrency::array<Vertex2D, 1>& dstpos,
		Concurrency::array<int, 2>& dsta,
		Concurrency::array<FLT2, 2>& dstd,
		const INT2 sz,
		bool normdir);
}; // ***************************************************************************************************
