#include <amp_math.h>
#include "ProcessF.h"
#include "..\myUtil.h"	// NORMAL_TO_AREA
#include "EngineDbg.h"	// VVVDBG_DUMP

#define X 1
#define Y 0
#define SIZEX dn_vgpu_f.extent[X]
#define SIZEY dn_vgpu_f.extent[Y]

using namespace concurrency::graphics;

void ProcessF::gpuRun0Split1(const int_2 shift0){
	const LayMid* up_lay = lays->vMidLays[0];
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay->vf.vgpu;
	const concurrency::array<float_2, 1>& f_masks = *up_lay->kF.vgpu;	//const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;
	const float kfup = up_lay->kf;

	Lay0* dn_lay = &lays->lay0;
	concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay->vf.vgpu;

	parallel_for_each(up_vgpu_a.extent,
		[&up_vgpu_a, &up_vgpu_f, &dn_vgpu_f, &f_masks, shift0, kfup](index<2> idx)restrict(amp) {
			int y_dn = (idx[Y] * 2 + shift0.y) % SIZEY;
			const int x0_dn = (idx[X] * 2 + shift0.x) % SIZEX;
			const int x1_dn = (x0_dn + 1) % SIZEX;
			const float_2* pmask = &f_masks[up_vgpu_a[idx] * 4];

			dn_vgpu_f[y_dn][x0_dn] = up_vgpu_f[idx] + pmask[0] * kfup;
			dn_vgpu_f[y_dn][x1_dn] = up_vgpu_f[idx] + pmask[1] * kfup;
			y_dn = (y_dn + 1) % SIZEY;
			dn_vgpu_f[y_dn][x0_dn] = up_vgpu_f[idx] + pmask[2] * kfup;
			dn_vgpu_f[y_dn][x1_dn] = up_vgpu_f[idx] + pmask[3] * kfup;
		});
	VVVDBG_DUMP(dn_lay->sDumpFgpu());
} // ///////////////////////////////////////////////////////////////////////////