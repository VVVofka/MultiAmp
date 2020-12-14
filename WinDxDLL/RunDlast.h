#pragma once
#ifdef MODEA
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "Vertex.h"
#include "Utils.h"

using namespace concurrency;
using namespace concurrency::fast_math;
using namespace concurrency::direct3d;

class RunDlast{
public:
	static void Run(const INT2 shift,
                    const array<DrQuadro, 2>& srcd,
				    array<Vertex2D, 1>& dstpos,
				    array<int, 2>& dsta,
				    array<FLT2, 2>& dstd,
				    const INT2 sz,
					bool normdir);

}; // ***************************************************************************************************
#endif  // MODEA
