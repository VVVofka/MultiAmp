#include <amp_math.h>
#include "ProcessF.h"

#define X 1
#define Y 0

using namespace concurrency::graphics;

void ProcessF::gpuRun1(const int ncurlay){
	_ASSERTE(ncurlay > 1);
	const LayMid& up_lay = *lays->vMidLays[ncurlay];
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay.va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay.vf.vgpu;
	const float klayf = up_lay.kF;

	LayMid& dn_lay = *lays->vMidLays[ncurlay - 1];
	const concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay.vf.vgpu;

	LayMid& dst_lay = *lays->vMidLays[ncurlay - 2];
	concurrency::array<float_2, 2>& dst_vgpu_f = *dn_lay.vf.vgpu;

	const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;

	parallel_for_each(up_vgpu_a.extent,
		[&dn_vgpu_f, &up_vgpu_a, &up_vgpu_f, &dst_vgpu_f,
		&f_masks, klayf
		](index<2> idx) restrict(amp) {
			const int x0 = idx[X] * 2;
			const int y0 = idx[Y] * 2;

			int idmask = up_vgpu_a[idx] * 16;

			float_2 curf = dn_vgpu_f[index<2>(y0, x0)];
			dst_vgpu_f[index<2>(y0, x0)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0, x0 + 1)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 1, x0)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 1, x0 + 1)] = curf + f_masks[idmask++] * klayf;
			
			curf = dn_vgpu_f[index<2>(y0, x0 + 1)];
			dst_vgpu_f[index<2>(y0, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0, x0 + 3)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 1, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 1, x0 + 3)] = curf + f_masks[idmask++] * klayf;

			curf = dn_vgpu_f[index<2>(y0 + 1, x0)];
			dst_vgpu_f[index<2>(y0 + 2, x0)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 2, x0 + 1)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 3, x0)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 3, x0 + 1)] = curf + f_masks[idmask++] * klayf;

			curf = dn_vgpu_f[index<2>(y0 + 1, x0 + 1)];
			dst_vgpu_f[index<2>(y0 + 2, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 2, x0 + 3)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 3, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			dst_vgpu_f[index<2>(y0 + 3, x0 + 3)] = curf + f_masks[idmask] * klayf;
		});
} // ///////////////////////////////////////////////////////////////////////////
#undef Y
#undef X
