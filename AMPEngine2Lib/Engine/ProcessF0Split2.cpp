#include <amp.h>		// sign
#include <amp_math.h>	// signbitf
#include "ProcessF.h"
//#include "..\myUtil.h"	// NORMAL_TO_AREA
#include "EngineDbg.h"	// VVVDBG_DUMP

#define X 1
#define Y 0
#define SIZEX dn_vgpu_a.extent[X]
#define SIZEY dn_vgpu_a.extent[Y]

using namespace concurrency::graphics;
using namespace concurrency::direct3d;
using namespace Concurrency::fast_math;

void ProcessF::gpuRun0Split2(const int_2 shift0, const uint iter){
	const LayMid* up_lay = lays->vMidLays[1];
	const Concurrency::extent<2> up_extent = up_lay->va.vgpu->get_extent();

	Lay0* dn_lay = &lays->lay0;
	concurrency::array<int, 2>& dn_vgpu_a = *dn_lay->va.vgpu;
	concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay->vf.vgpu;
	const concurrency::array<uint, 1>& mask_move = *dn_lay->vgpuMaskMove;

	const int signFor0 = (iter & 1) + 1; // 1 or 2

	parallel_for_each(up_extent, [&dn_vgpu_a, &dn_vgpu_f, &mask_move, shift0, signFor0](index<2> idx)restrict(amp) {
		const int x0 = (idx[X] * 4 + shift0.x) % SIZEX;
		const int x1 = (x0 + 1) % SIZEX;
		const int x2 = (x1 + 1) % SIZEX;
		const int x3 = (x2 + 1) % SIZEX;
		int y = (idx[Y] * 4 + shift0.y) % SIZEY;

		for(int j = 0; j < 4; j++){	// gluke in expand for!
			const int idxmaskm =
				(sign(dn_vgpu_a[y][x0] + 1)) | (((signbitf(dn_vgpu_f[y][x0].x) + signFor0) / 2) << 1) |
				(sign(dn_vgpu_a[y][x1] + 1) << 2) | (((signbitf(dn_vgpu_f[y][x1].x) + signFor0) / 2) << 3) |
				(sign(dn_vgpu_a[y][x2] + 1) << 4) | (((signbitf(dn_vgpu_f[y][x2].x) + signFor0) / 2) << 5) |
				(sign(dn_vgpu_a[y][x3] + 1) << 6) | (((signbitf(dn_vgpu_f[y][x3].x) + signFor0) / 2) << 7);
			const uint maskm = mask_move[idxmaskm];
			if(maskm & 0xb110000){
				const int posxsrc = (x0 + (maskm & 0xb11)) % SIZEX;
				const int posxdst = (x0 + ((maskm >> 2) & 0xb11)) % SIZEX;
				dn_vgpu_a[y][posxdst] = dn_vgpu_a[y][posxsrc];
				dn_vgpu_a[y][posxsrc] = -1;
				dn_vgpu_f[y][posxdst].x = 0.f;
			}
			y = (y + 1) % SIZEY;
		}
		});
} // ///////////////////////////////////////////////////////////////////////////