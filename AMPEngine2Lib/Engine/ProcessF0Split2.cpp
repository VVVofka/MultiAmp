#include <amp_math.h>
#include "ProcessF.h"
#include "..\myUtil.h"	// NORMAL_TO_AREA
#include "EngineDbg.h"	// VVVDBG_DUMP

#define X 1
#define Y 0
#define SIZEX dn_vgpu_f.extent[X]
#define SIZEY dn_vgpu_f.extent[Y]

using namespace concurrency::graphics;
using namespace concurrency::direct3d;
using namespace Concurrency::fast_math;

void ProcessF::gpuRun0Split2(const int_2 shift0){
	const LayMid* up_lay = lays->vMidLays[1];
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;
	const concurrency::array<float_2, 1>& f_masks = *up_lay->kF.vgpu;	//const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;

	LayMid* mid_lay = lays->vMidLays[0];
	const concurrency::array<float_2, 2>& mid_vgpu_f = *mid_lay->vf.vgpu;

	Lay0* dn_lay = &lays->lay0;
	concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay->vf.vgpu;
	concurrency::array<uint_2, 2>& up_vgpu_m = *dn_lay->vmaskmove.vgpu;

	parallel_for_each(up_vgpu_a.extent,
		[&up_vgpu_a,&mid_vgpu_f, &dn_vgpu_f,
		&f_masks, shift0](index<2> idx)restrict(amp) {
			const int_2 pos0 = int_2((idx[X] * 4 + shift0.x) % SIZEX, (idx[Y] * 4 + shift0.y) % SIZEY);
			const int_2 pos1 = int_2((pos0.x + 1) % SIZEX, (pos0.y + 1) % SIZEY);
			const int_2 pos2 = int_2((pos1.x + 1) % SIZEX, (pos1.y + 1) % SIZEY);
			const int_2 pos3 = int_2((pos2.x + 1) % SIZEX, (pos2.y + 1) % SIZEY);


		});
} // ///////////////////////////////////////////////////////////////////////////