#include "ProcessA.h"
#include <amp_math.h>
#define X 1
#define Y 0
	using namespace concurrency::graphics;
	using namespace concurrency::direct3d;

	void ProcessA::gpuRun0(const int_2 shift){
		LayMid& up_lay = *lays->vMidLays[0];
		concurrency::array<int, 2>& up_vgpu_a = *up_lay.va.vgpu;		//

		const Lay0& dn_lay = lays->lay0;
		const concurrency::array<int, 2>& dn_vgpu_a = *dn_lay.va.vgpu; // -1:no point, >=0: id point in vscreen

		parallel_for_each(
			up_vgpu_a.extent,
			[shift, &dn_vgpu_a,		// &dn_vgpu_f,
			&up_vgpu_a]				//, &up_vgpu_f
		(index<2> idUp)restrict(amp) {
				const uint x0 = (idUp[X] * 2 + shift.x) % dn_vgpu_a.extent[X];
				const uint x1 = (x0 + 1) % dn_vgpu_a.extent[X];
				const uint y0 = (idUp[Y] * 2 + shift.y) % dn_vgpu_a.extent[Y];
				const uint y1 = (y0 + 1) % dn_vgpu_a.extent[Y];
				up_vgpu_a[idUp] =
					(sign(1 + dn_vgpu_a[index<2>(y0, x0)])) +
					(sign(1 + dn_vgpu_a[index<2>(y0, x1)]) << 1) +
					(sign(1 + dn_vgpu_a[index<2>(y1, x0)]) << 2) +
					(sign(1 + dn_vgpu_a[index<2>(y1, x1)]) << 3);
			});
	} // ///////////////////////////////////////////////////////////////////////////////////
#undef Y
#undef X
