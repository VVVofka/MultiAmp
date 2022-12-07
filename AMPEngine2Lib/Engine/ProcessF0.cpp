#include <amp_math.h>
#include "ProcessF.h"
#include "..\myUtil.h"	// NORMAL_TO_AREA
#include "EngineDbg.h"	// VVVDBG_DUMP

#define X 1
#define Y 0
#define SIZEX dn_vgpu_a.extent[X]
#define SIZEY dn_vgpu_a.extent[Y]
using namespace concurrency::graphics;
using namespace concurrency::direct3d;
using namespace Concurrency::fast_math;

void ProcessF::gpuRun0(const uint_2 shift, const uint iter){
	const LayMid* up_lay = lays->vMidLays[1];
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay->vf.vgpu;
	const concurrency::array<float_2, 1>& f_masks = *up_lay->kF.vgpu;	//const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;

	LayMid* mid_lay = lays->vMidLays[0];
	const concurrency::array<float_2, 2>& mid_vgpu_f = *mid_lay->vf.vgpu;

	Lay0* dn_lay = &lays->lay0;
	concurrency::array<int, 2>& dn_vgpu_a = *dn_lay->va.vgpu;
	concurrency::array<Vertex2D, 1>& screen = *dn_lay->vgpuScreen;

	const uint signFor0 = (iter & 1) + 1; // 1 or 2

	VVVDBG_DUMP(dn_lay->sDumpAgpu());
	parallel_for_each(up_vgpu_a.extent,
		[&dn_vgpu_a, &up_vgpu_a, &mid_vgpu_f, &up_vgpu_f, &screen,
		&f_masks, shift, signFor0
		](index<2> idx)restrict(amp) {
			// TODO: #define?
			const int xmid = idx[X] * 2;
			const int ymid = idx[Y] * 2;
			const int xdn = idx[X] * 4;
			const int ydn = idx[Y] * 4;
			//index: 0(2,4,6) digit: 0:point absent or f=0; 
			//						 1:point present;
			//		 1(3,5,7) digit: 0:left  (f<0)
			//						 1:right (f>0)
			//value: 0,1 digits: index src (0xb00-right; 0xb11-left) 
			//		 1,2 digits: index dst (0xb00-right; 0xb11-left) 
			//		 3,4 digits: abs cnt move (0..3)
			const int vmaskmov[256] = {
			 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  30,60,30,30,45,60,45,45,30,30,30,30,30,30, 0,30,
			 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  22,20,22,22, 0, 0, 0, 0,22,22,22,22,34, 0,34, 0,
			 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,   0,20, 0, 0, 0, 0, 0, 0, 0,20, 0, 0,17, 0,17, 0,
			 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  22,20,22,22, 0, 0, 0, 0,22,22,22,22,34, 0,34, 0,

			 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  30,20,30,30,45,60,45,45,30,20,30,30, 0,30,17,30,
			 0,20, 0, 0,25,40,25,25, 0,20, 0, 0,17, 0,17, 0,  22,20,22,22, 0, 0, 0, 0,22,22,22,22,34, 0,34, 0,
			27,20,27,27,25,40,25,25,27, 0,27,27,27,27,17,27,   0,20, 0, 0, 0, 0, 0, 0, 0,20, 0, 0,17, 0,17, 0,
			27, 0,27,27,27,27,27,27,27,27,27,27,27,27,51,27,  39,20,39,39, 0, 0, 0, 0,39,39,39,39,51, 0,51, 0
			};

			int idmask = up_vgpu_a[idx] * 16;	// TODO: define?
			float_2 curf = mid_vgpu_f[index<2>(ymid, xmid)];
			const int xshift = (xdn + shift.x) % SIZEX;	// TODO: define?
			int yshift = (ydn + shift.y) % SIZEY;

			int idmove =
				(sign(dn_vgpu_a[yshift][xshift] + 1)) |
				(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
				(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
				(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
				(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |
				(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
				(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
				(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
			if(vmaskmov[idmove] & 0xb110000){
				const int posxsrc = (xshift + vmaskmov[idmove] & 0xb11) % SIZEX;
				const int posxdst = (xshift + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
				dn_vgpu_a[yshift][posxdst] = dn_vgpu_a[yshift][posxsrc];
				dn_vgpu_a[yshift][posxsrc] = -1;
				screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);
			}

			yshift = (yshift + 1) % SIZEY;
			idmask += 2;	// 2
			idmove =
				(sign(dn_vgpu_a[yshift][xshift] + 1)) |
				(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
				(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
				(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
				(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |	// TODO: /2 & << - compens
				(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
				(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
				(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
			if(vmaskmov[idmove] & 0xb110000){
				const int posxsrc = (xshift + vmaskmov[idmove] & 0xb11) % SIZEX;
				const int posxdst = (xshift + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
				dn_vgpu_a[yshift][posxdst] = dn_vgpu_a[yshift][posxsrc];
				dn_vgpu_a[yshift][posxsrc] = -1;
				screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);	// TODO: screen to separate
			}

			idmask += 6;	// 8
			yshift = (yshift + 1) % SIZEY;
			idmove =
				(sign(dn_vgpu_a[yshift][xshift] + 1)) |
				(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
				(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
				(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
				(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |
				(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
				(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
				(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
			if(vmaskmov[idmove] & 0xb110000){
				const int posxsrc = (xshift + vmaskmov[idmove] & 0xb11) % SIZEX;
				const int posxdst = (xshift + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
				dn_vgpu_a[yshift][posxdst] = dn_vgpu_a[yshift][posxsrc];
				dn_vgpu_a[yshift][posxsrc] = -1;
				screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);
			}

			idmask += 2;	// 10
			yshift = (yshift + 1) % SIZEY;
			idmove =
				(sign(dn_vgpu_a[yshift][xshift] + 1)) |
				(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
				(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
				(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
				(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |
				(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
				(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
				(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
			if(vmaskmov[idmove] & 0xb110000){
				const int posxsrc = (xshift + vmaskmov[idmove] & 0xb11) % SIZEX;
				const int posxdst = (xshift + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
				dn_vgpu_a[yshift][posxdst] = dn_vgpu_a[yshift][posxsrc];
				dn_vgpu_a[yshift][posxsrc] = -1;
				screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);
			}
		});
		VVVDBG_DUMP(dn_lay->sDumpAgpu());
		VVVDBG_DUMP(dn_lay->sDumpScreen());
} // ////////////////////////////////////////////////////////////////////////////
#undef Y
#undef X

