#include <amp_math.h>
#include "ProcessF.h"
//#include "ProcessParam.h"

#define X 1
#define Y 0

using namespace concurrency::graphics;

void ProcessF::gpuRun1(const int ncurlay){
	_ASSERTE(ncurlay > 0);
	const LayMid& up_lay = *lays->vMidLays[ncurlay];
	LayMid& dn_lay = *lays->vMidLays[ncurlay - 1];
	const ProcessParam* param = &up_lay.param;
	const float klayf = param->klayf;
	const float kLaminar = param->kLaminar;
	const float kTurbul = param->kTurbul;
	const float levelTurbul = param->levelTurbul;

	const concurrency::array<int, 2>& up_vgpu_a = *up_lay.va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay.vf.vgpu;

	concurrency::array<int, 2>& dn_vgpu_a = *dn_lay.va.vgpu;
	concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay.vf.vgpu;

	const concurrency::array<float_2, 2>& f_masks = *fmasks->vgpu;

	parallel_for_each(up_vgpu_a.extent,
		[&dn_vgpu_a, &dn_vgpu_f,
		&up_vgpu_a, &up_vgpu_f,
		&f_masks, klayf, kLaminar, kTurbul, levelTurbul
		](index<2> idx)restrict(amp) {
			const int x0 = idx[X] * 2;
			const int y0 = idx[Y] * 2;

#define idc0 (index<2>(y0, x0))
#define idc1 (index<2>(y0, x0 + 1))
#define idc2 (index<2>(y0 + 1, x0))
#define idc3 (index<2>(y0 + 1, x0 + 1))

			dn_vgpu_f[idc0] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][0] * klayf;
			dn_vgpu_f[idc1] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][1] * klayf;
			dn_vgpu_f[idc2] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][2] * klayf;
			dn_vgpu_f[idc3] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][3] * klayf;
		});
} // ///////////////////////////////////////////////////////////////////////////
#undef idc0
#undef idc1
#undef idc2
#undef idc3
#undef Y
#undef X
