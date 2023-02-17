#include "ProcessA.h"
//#include <amp_math.h>

#define X 1
#define Y 0

//using namespace concurrency::graphics;
//using namespace concurrency::direct3d;

void ProcessA::gpuRunMid(LayMid* up_lay){
	concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;

	const LayMid* dn_lay = up_lay - 1;
	const concurrency::array<int, 2>& dn_vgpu_a = *dn_lay->va.vgpu;

	const concurrency::array<int, 1>& maskA = *amask->vgpu;

	parallel_for_each(up_vgpu_a.extent, [&dn_vgpu_a, &up_vgpu_a, &maskA](index<2> idUp)restrict(amp) {
		const int x = idUp[X] * 2, y = idUp[Y] * 2;
		up_vgpu_a[idUp] =
			(maskA[dn_vgpu_a[index<2>(y, x)]]) +
			(maskA[dn_vgpu_a[index<2>(y, x + 1)]] << 1) +
			(maskA[dn_vgpu_a[index<2>(y + 1, x)]] << 2) +
			(maskA[dn_vgpu_a[index<2>(y + 1, x + 1)]] << 3);
		});
} // ///////////////////////////////////////////////////////////////////////////
#undef Y
#undef X
