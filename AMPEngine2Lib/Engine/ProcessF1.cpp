#include <amp_math.h>
#include "ProcessF.h"
#include "EngineDbg.h"

#define X 1
#define Y 0
using namespace concurrency::graphics;

void ProcessF::gpuRun1(const int ncurlay){
	// TODO: Move to class
	_ASSERTE(ncurlay > 1);
	const LayMid* up_lay = lays->vMidLays[ncurlay];
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay->vf.vgpu;
	//const float klayf = up_lay.kF;
	const concurrency::array<float_2, 1>& f_masks = *up_lay->kF.vgpu; // const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;

	const LayMid* mid_lay = lays->vMidLays[ncurlay - 1];
	const concurrency::array<float_2, 2>& mid_vgpu_f = *mid_lay->vf.vgpu;

	LayMid* dn_lay = lays->vMidLays[ncurlay - 2];
	concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay->vf.vgpu;

	parallel_for_each(up_vgpu_a.extent,
		[&mid_vgpu_f, &up_vgpu_a, &up_vgpu_f, &dn_vgpu_f,
		&f_masks
		](index<2> idx) restrict(amp) {
			// TODO: #define?
			const int xmid = idx[X] * 2;
			const int ymid = idx[Y] * 2;
			const int xdn = idx[X] * 4;
			const int ydn = idx[Y] * 4;

			// TODO: ptr?
			int idmask = up_vgpu_a[idx] * 16;

			float_2 curf = mid_vgpu_f[index<2>(ymid, xmid)];
			dn_vgpu_f[index<2>(ydn, xdn)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn, xdn + 1)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 1, xdn)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 1, xdn + 1)] = curf + f_masks[idmask++];
			
			curf = mid_vgpu_f[index<2>(ymid, xmid + 1)];
			dn_vgpu_f[index<2>(ydn, xdn + 2)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn, xdn + 3)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 1, xdn + 2)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 1, xdn + 3)] = curf + f_masks[idmask++];

			curf = mid_vgpu_f[index<2>(ymid + 1, xmid)];
			dn_vgpu_f[index<2>(ydn + 2, xdn)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 2, xdn + 1)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 3, xdn)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 3, xdn + 1)] = curf + f_masks[idmask++];

			curf = mid_vgpu_f[index<2>(ymid + 1, xmid + 1)];
			dn_vgpu_f[index<2>(ydn + 2, xdn + 2)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 2, xdn + 3)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 3, xdn + 2)] = curf + f_masks[idmask++];
			dn_vgpu_f[index<2>(ydn + 3, xdn + 3)] = curf + f_masks[idmask];

			//dn_vgpu_f[index<2>(0, 0)] = f_masks[38];	// float_2(5, 6);
			//dn_vgpu_f[index<2>(0, 1)] = f_masks[1];	// float_2(5, 6);
			//dn_vgpu_f[index<2>(0, 2)] = f_masks[2];	// float_2(5, 6);
			//dn_vgpu_f[index<2>(0, 2)] = float_2(idmask, idmask - 16);
		});
	//VVVDBG_SET_F(ncurlay - 1, dn_vgpu_f);
	VVVDBG_DUMP(dn_lay->sDumpFgpu());
} // ///////////////////////////////////////////////////////////////////////////
#undef Y
#undef X
