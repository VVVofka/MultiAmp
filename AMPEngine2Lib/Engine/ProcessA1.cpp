#include "ProcessA.h"
#include <amp_math.h>
#define X 1
#define Y 0

using namespace concurrency::graphics;
using namespace concurrency::direct3d;

void ProcessA::gpuRun1(const int n_lay){
	_ASSERTE(n_lay > 0);
	LayMid& up_lay = *lays->vMidLays[n_lay];
	const LayMid& dn_lay = *lays->vMidLays[n_lay - 1];
	concurrency::array<int, 2>& up_vgpu_a = *up_lay.va.vgpu;
	const concurrency::array<int, 2>& dn_vgpu_a = *dn_lay.va.vgpu;
	const concurrency::array<int, 1>& maskA = *amask->vgpu;

	parallel_for_each(up_vgpu_a.extent,
		[
			&dn_vgpu_a, 
			&up_vgpu_a,
			&maskA
		]
	(index<2> idUp)restrict(amp) {
			const int x0 = idUp[X] * 2, y0 = idUp[Y] * 2;
			const int x1 = x0 + 1, y1 = y0 + 1;
			up_vgpu_a[idUp] = maskA[0];
			//up_vgpu_a[idUp] = maskA[idxmaska];
			//	(maskA[dn_vgpu_a[index<2>(y0, x0)]]) +
			//	(maskA[dn_vgpu_a[index<2>(y0, x1)]] << 1) +
			//	(maskA[dn_vgpu_a[index<2>(y1, x0)]] << 2) +
			//	(maskA[dn_vgpu_a[index<2>(y1, x1)]] << 3);
		});
} // ///////////////////////////////////////////////////////////////////////////
#undef Y
#undef X
