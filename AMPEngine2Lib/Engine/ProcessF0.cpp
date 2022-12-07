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

void setDbg(concurrency::array<float_2, 2>& dn_vgpu_dbg, int_2 shift, const float_2* f_masks, const float_2& curf)restrict(amp){
	dn_vgpu_dbg[shift.y][shift.x] = curf;// +f_masks[0];
	dn_vgpu_dbg[shift.y][(shift.x + 1) % dn_vgpu_dbg.extent[X]] = curf;// +f_masks[1];
	dn_vgpu_dbg[shift.y][(shift.x + 2) % dn_vgpu_dbg.extent[X]] = curf;// +f_masks[4];
	dn_vgpu_dbg[shift.y][(shift.x + 3) % dn_vgpu_dbg.extent[X]] = curf;// +f_masks[5];
} // ///////////////////////////////////////////////////////////////////////////////////////////
int getIdMove(concurrency::array<int, 2>& dn_vgpu_a, int_2 shift, const float_2* f_masks, float curfx, int signFor0)restrict(amp){
	return
		(sign(dn_vgpu_a[shift.y][shift.x] + 1)) |
		(sign(dn_vgpu_a[shift.y][(shift.x + 1) % dn_vgpu_a.extent[X]] + 1) << 2) |
		(sign(dn_vgpu_a[shift.y][(shift.x + 2) % dn_vgpu_a.extent[X]] + 1) << 4) |
		(sign(dn_vgpu_a[shift.y][(shift.x + 3) % dn_vgpu_a.extent[X]] + 1) << 6) |
		(((signbitf(f_masks->x + curfx) + signFor0) / 2) << 1) |
		(((signbitf(f_masks[1].x + curfx) + signFor0) / 2) << 3) |
		(((signbitf(f_masks[4].x + curfx) + signFor0) / 2) << 5) |
		(((signbitf(f_masks[5].x + curfx) + signFor0) / 2) << 7);
} // /////////////////////////////////////////////////////////////////////////////////////

void ProcessF::gpuRun0(const uint_2 shift0, const uint iter){

	const LayMid* up_lay = lays->vMidLays[1];
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay->vf.vgpu;
	const concurrency::array<float_2, 1>& f_masks = *up_lay->kF.vgpu;	//const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;

	LayMid* mid_lay = lays->vMidLays[0];
	const concurrency::array<float_2, 2>& mid_vgpu_f = *mid_lay->vf.vgpu;
	VVVDBG_DUMP(mid_lay->sDumpFgpu(2));

	Lay0* dn_lay = &lays->lay0;
	concurrency::array<int, 2>& dn_vgpu_a = *dn_lay->va.vgpu;
	concurrency::array<Vertex2D, 1>& screen = *dn_lay->vgpuScreen;

	const int signFor0 = (iter & 1) + 1; // 1 or 2

	VVVDBG_IF_DBG2(concurrency::array<float_2, 2>&dn_vgpu_dbg = *dn_lay->vgpuDbg);

	//VVVDBG_DUMP(dn_lay->sDumpAgpu());
	parallel_for_each(up_vgpu_a.extent,
		[&dn_vgpu_a, &up_vgpu_a, &mid_vgpu_f, &up_vgpu_f, &screen,
		&f_masks,
		shift0, signFor0
		VVVDBG_IF_DBG2(, &dn_vgpu_dbg)
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
		const float_2 curf = mid_vgpu_f[ymid][xmid];
		int_2 shift = int_2((xdn + shift0.x) % SIZEX, (ydn + shift0.y) % SIZEY);

		int idmove = getIdMove(dn_vgpu_a, shift, &f_masks[idmask], curf.x, signFor0);
		setDbg(dn_vgpu_dbg, shift, &f_masks[idmask], curf);
		//(sign(dn_vgpu_a[yshift][xshift] + 1)) |
		//(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
		//(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
		//(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
		//(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |
		//(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
		//(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
		//(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
		//dn_vgpu_dbg[yshift][xshift] = f_masks[idmask] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 1) % SIZEX] = f_masks[idmask + 1] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 2) % SIZEX] = f_masks[idmask + 4] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 3) % SIZEX] = f_masks[idmask + 5] + curf;
		if(vmaskmov[idmove] & 0xb110000){
			const int posxsrc = (shift.x + vmaskmov[idmove] & 0xb11) % SIZEX;
			const int posxdst = (shift.x + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
			dn_vgpu_a[shift.y][posxdst] = dn_vgpu_a[shift.y][posxsrc];
			dn_vgpu_a[shift.y][posxsrc] = -1;
			//screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);
		}

		shift.y = (shift.y + 1) % SIZEY;
		idmask += 2;	// 2
		idmove = getIdMove(dn_vgpu_a, shift, &f_masks[idmask], curf.x, signFor0);
		setDbg(dn_vgpu_dbg, shift, &f_masks[idmask], curf);
		//(sign(dn_vgpu_a[yshift][xshift] + 1)) |
		//(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
		//(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
		//(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
		//(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |	// TODO: /2 & << - compens
		//(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
		//(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
		//(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
		//dn_vgpu_dbg[yshift][xshift] = f_masks[idmask] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 1) % SIZEX] = f_masks[idmask + 1] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 2) % SIZEX] = f_masks[idmask + 4] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 3) % SIZEX] = f_masks[idmask + 5] + curf;
		if(vmaskmov[idmove] & 0xb110000){
			const int posxsrc = (shift.x + vmaskmov[idmove] & 0xb11) % SIZEX;
			const int posxdst = (shift.x + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
			dn_vgpu_a[shift.y][posxdst] = dn_vgpu_a[shift.y][posxsrc];
			dn_vgpu_a[shift.y][posxsrc] = -1;
			//screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);	// TODO: screen to separate
		}

		idmask += 6;	// 8
		shift.y = (shift.y + 1) % SIZEY;
		idmove = getIdMove(dn_vgpu_a, shift, &f_masks[idmask], curf.x, signFor0);
		setDbg(dn_vgpu_dbg, shift, &f_masks[idmask], curf);
		//(sign(dn_vgpu_a[yshift][xshift] + 1)) |
		//(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
		//(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
		//(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
		//(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |
		//(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
		//(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
		//(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
		//dn_vgpu_dbg[yshift][xshift] = f_masks[idmask] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 1) % SIZEX] = f_masks[idmask + 1] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 2) % SIZEX] = f_masks[idmask + 4] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 3) % SIZEX] = f_masks[idmask + 5] + curf;
		if(vmaskmov[idmove] & 0xb110000){
			const int posxsrc = (shift.x + vmaskmov[idmove] & 0xb11) % SIZEX;
			const int posxdst = (shift.x + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
			dn_vgpu_a[shift.y][posxdst] = dn_vgpu_a[shift.y][posxsrc];
			dn_vgpu_a[shift.y][posxsrc] = -1;
			//screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);
		}

		idmask += 2;	// 10
		shift.y = (shift.y + 1) % SIZEY;
		idmove = getIdMove(dn_vgpu_a, shift, &f_masks[idmask], curf.x, signFor0);
		setDbg(dn_vgpu_dbg, shift, &f_masks[idmask], curf);
		//(sign(dn_vgpu_a[yshift][xshift] + 1)) |
		//(sign(dn_vgpu_a[yshift][(xshift + 1) % SIZEX] + 1) << 2) |
		//(sign(dn_vgpu_a[yshift][(xshift + 2) % SIZEX] + 1) << 4) |
		//(sign(dn_vgpu_a[yshift][(xshift + 3) % SIZEX] + 1) << 6) |
		//(((signbitf(f_masks[idmask].x + curf.x) + signFor0) / 2) << 1) |
		//(((signbitf(f_masks[idmask + 1].x + curf.x) + signFor0) / 2) << 3) |
		//(((signbitf(f_masks[idmask + 4].x + curf.x) + signFor0) / 2) << 5) |
		//(((signbitf(f_masks[idmask + 5].x + curf.x) + signFor0) / 2) << 7);
		//dn_vgpu_dbg[yshift][xshift] = f_masks[idmask] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 1) % SIZEX] = f_masks[idmask + 1] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 2) % SIZEX] = f_masks[idmask + 4] + curf;
		//dn_vgpu_dbg[yshift][(xshift + 3) % SIZEX] = f_masks[idmask + 5] + curf;
		if(vmaskmov[idmove] & 0xb110000){
			const int posxsrc = (shift.x + vmaskmov[idmove] & 0xb11) % SIZEX;
			const int posxdst = (shift.x + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
			dn_vgpu_a[shift.y][posxdst] = dn_vgpu_a[shift.y][posxsrc];
			dn_vgpu_a[shift.y][posxsrc] = -1;
			//screen[dn_vgpu_a[yshift][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);
		}
	});
	//VVVDBG_DUMP(dn_lay->sDumpAgpu());
	//VVVDBG_DUMP(dn_lay->sDumpScreen());
	VVVDBG_DUMP(dn_lay->sDumpDbg(2));
} // ////////////////////////////////////////////////////////////////////////////
#undef Y
#undef X

