#include <amp_math.h>
#include "ProcessF.h"
#include "EngineDbg.h"	// VVVDBG_DUMP

#define X 1
#define Y 0
using namespace concurrency::graphics;

void ProcessF::gpuRunMid(LayMid* up_lay){
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay->vf.vgpu;
	const concurrency::array<float_2, 1>& f_masks = *up_lay->kF.vgpu;

	LayMid* dn_lay = up_lay - 1;
	concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay->vf.vgpu;

	parallel_for_each(up_vgpu_a.extent,
		[&up_vgpu_a, &up_vgpu_f, &dn_vgpu_f, &f_masks](index<2> idx) restrict(amp) {
			// TODO: #define?
			const int xdn = idx[X] * 2;
			const int ydn = idx[Y] * 2;

			int idmask = up_vgpu_a[idx] * 4;		// TODO: ptr?

			dn_vgpu_f[ydn][xdn] = up_vgpu_f[idx] + f_masks[idmask++];
			dn_vgpu_f[ydn][xdn + 1] = up_vgpu_f[idx] + f_masks[idmask++];
			dn_vgpu_f[ydn + 1][xdn] = up_vgpu_f[idx] + f_masks[idmask++];
			dn_vgpu_f[ydn + 1][xdn + 1] = up_vgpu_f[idx] + f_masks[idmask];
		});
	//VVVDBG_SET_F(ncurlay - 1, dn_vgpu_f);
	//VVVDBG_DUMP(dn_lay->sDumpFgpu());
} // ///////////////////////////////////////////////////////////////////////////
#undef Y
#undef X
