#include <amp_math.h>
#include "ProcessF.h"
#define X 1
#define Y 0
using namespace concurrency::graphics;
using namespace concurrency::direct3d;

void ProcessF::gpuRun0(const uint_2 shift, const uint iter){
	const LayMid* up_lay = lays->vMidLays[1];
	const concurrency::array<int, 2>& up_vgpu_a = *up_lay->va.vgpu;
	const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay->vf.vgpu;
	const float klayf = up_lay->kF;

	LayMid* dn_lay = lays->vMidLays[0];
	const concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay->vf.vgpu;

	Lay0* lay_0 = &lays->lay0;
	concurrency::array<int, 2>& dn_vgpu_a = *lay_0->va.vgpu;
	concurrency::array<Vertex2D, 1>& screen = *lay_0->vgpuScreen;
	const float_2 rSizeDn(lay_0->sz);

	const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;
	uint_2 iter2 = uint_2(iter, iter ^ 1);

	parallel_for_each(up_vgpu_a.extent,
		[&dn_vgpu_a, &up_vgpu_a, &dn_vgpu_f, &up_vgpu_f, &screen,
		&f_masks, shift, klayf, rSizeDn, iter2
		](index<2> idx)restrict(amp) {
			const uint_2 mid0 = uint_2(idx[Y], idx[X]) * 2;

			// TODO: va lay0 - int;  other uint
			int idmask = up_vgpu_a[idx] * 16;
			float_2 curf = dn_vgpu_f[index<2>(mid0.y, mid0.x)];
			
			uint_2 dn0 = mid0 * 2;
			uint_2 ofs = iter2;

			index<2> src = index<2>(dn0.y, dn0.x);
			index<2> dst = index<2>(dn0.y + ofs.y, dn0.x + ofs.x);
			float_2 fsrc = curf + f_masks[idmask] * klayf;
			float_2 fdst = curf + f_masks[idmask + 2 * ofs.y + ofs.x] * klayf;
			if(fsrc. src[ofs.x] >= 0)

			float_2 f0 = curf + f_masks[idmask++] * klayf;
			float_2 f1 = curf + f_masks[idmask++] * klayf;
			float_2 f2 = curf + f_masks[idmask++] * klayf;
			float_2 f3 = curf + f_masks[idmask++] * klayf;
			idmask += 4;

			src = index<2>(y += iter2.x, x += iter2.y);
			dst = index<2>(y + iter2.y, x + iter2.x);

			src = index<2>(y += iter2.x, x += iter2.y);
			dst = index<2>(y + iter2.y, x + iter2.x);

			src = index<2>(y += iter2.x, x += iter2.y);
			dst = index<2>(y + iter2.y, x + iter2.x);


			src = index<2>(y = 2, x = 0);
			dst = index<2>(y + iter2.y, x + iter2.x);

			src = index<2>(y += iter2.x, x += iter2.y);
			dst = index<2>(y + iter2.y, x + iter2.x);

			src = index<2>(y += iter2.x, x += iter2.y);
			dst = index<2>(y + iter2.y, x + iter2.x);

			src = index<2>(y += iter2.x, x += iter2.y);
			dst = index<2>(y + iter2.y, x + iter2.x);

			//dst_vgpu_f[index<2>(y0, x0)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0, x0 + 1)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 1, x0)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 1, x0 + 1)] = curf + f_masks[idmask++] * klayf;

			//curf = dn_vgpu_f[index<2>(y0, x0 + 1)];
			//dst_vgpu_f[index<2>(y0, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0, x0 + 3)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 1, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 1, x0 + 3)] = curf + f_masks[idmask++] * klayf;

			//curf = dn_vgpu_f[index<2>(y0 + 1, x0)];
			//dst_vgpu_f[index<2>(y0 + 2, x0)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 2, x0 + 1)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 3, x0)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 3, x0 + 1)] = curf + f_masks[idmask++] * klayf;

			//curf = dn_vgpu_f[index<2>(y0 + 1, x0 + 1)];
			//dst_vgpu_f[index<2>(y0 + 2, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 2, x0 + 3)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 3, x0 + 2)] = curf + f_masks[idmask++] * klayf;
			//dst_vgpu_f[index<2>(y0 + 3, x0 + 3)] = curf + f_masks[idmask] * klayf;


			// TODO: optimize!
//			const int x0 = mad(idx[X], 2, shift.x) % dn_vgpu_a.extent[X];
//			const int y0 = mad(idx[Y], 2, shift.y) % dn_vgpu_a.extent[Y];
//			const int x1 = (x0 + 1) % dn_vgpu_a.extent[X];
//			const int y1 = (y0 + 1) % dn_vgpu_a.extent[Y];
//
//#define idc0 (index<2>(y0, x0))
//#define idc1 (index<2>(y0, x1))
//#define idc2 (index<2>(y1, x0))
//#define idc3 (index<2>(y1, x1))
//
//			//dn_vgpu_f[idc0] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][0] * klayf + dn_vgpu_f[idc0] * kinert;
//			//dn_vgpu_f[idc1] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][1] * klayf + dn_vgpu_f[idc1] * kinert;
//			//dn_vgpu_f[idc2] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][2] * klayf + dn_vgpu_f[idc2] * kinert;
//			//dn_vgpu_f[idc3] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][3] * klayf + dn_vgpu_f[idc3] * kinert;
//
//			// TODO: разнести x, y, i (p.203 Greg)
//
//			// move vscreen points
//#define normx0 (mad((float)(2 * x0 + 1), rSizeDn.x, -1.f))
//#define normx1 (mad((float)(2 * x1 + 1), rSizeDn.x, -1.f))
//#define normy0 (mad((float)(2 * y0 + 1), rSizeDn.y, -1.f))
//#define normy1 (mad((float)(2 * y1 + 1), rSizeDn.y, -1.f))
//
//				//	Bottom Horizontal
//			//auto idxsrc = idc0;
//			//auto idxdst = idc1;
//			//if((kf * dn_vgpu_f[idxsrc].x) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to rigth (bottom horizontal)
//			//	screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx1;
//			//	screen[dn_vgpu_a[idxdst]].Pos.y = normy0;
//			//	dn_vgpu_a[idxsrc] = -1;
//			//} else if((kf * dn_vgpu_f[idxdst].x) < 0 && dn_vgpu_a[idxsrc] < 0){ // Move to left (bottom horizontal)
//			//	screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx0;
//			//	screen[dn_vgpu_a[idxsrc]].Pos.y = normy0;
//			//	dn_vgpu_a[idxdst] = -1;
//			//}
//
//			//// Left Vertical
//			//idxdst = idc2;
//			//if((kf * dn_vgpu_f[idxsrc].y) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to up (left vertical)
//			//	screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx0;
//			//	screen[dn_vgpu_a[idxdst]].Pos.y = normy1;
//			//	dn_vgpu_a[idxsrc] = -1;
//			//} else if((kf * dn_vgpu_f[idxdst].y) < 0 && dn_vgpu_a[idxsrc] < 0){	// Move to down (left vertical)
//			//	screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx0;
//			//	screen[dn_vgpu_a[idxsrc]].Pos.y = normy0;
//			//	dn_vgpu_a[idxdst] = -1;
//			//}
//
//			//// Top Horizontal
//			//idxsrc = idc2;
//			//idxdst = idc3;
//			//if((kf * dn_vgpu_f[idxsrc].x) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to right (top horizontal)
//			//	screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx1;
//			//	screen[dn_vgpu_a[idxdst]].Pos.y = normy1;
//			//	dn_vgpu_a[idxsrc] = -1;
//			//} else if((kf * dn_vgpu_f[idxdst].x) < 0 && dn_vgpu_a[idxsrc] < 0){	// Move to left (top horizontal)
//			//	screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx0;
//			//	screen[dn_vgpu_a[idxsrc]].Pos.y = normy1;
//			//	dn_vgpu_a[idxdst] = -1;
//			//}
//
//			//// Right Vertical
//			//idxsrc = idc1;
//			//if((kf * dn_vgpu_f[idxsrc].y) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to up (right vertical)
//			//	screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx1;
//			//	screen[dn_vgpu_a[idxdst]].Pos.y = normy1;
//			//	dn_vgpu_a[idxsrc] = -1;
//			//} else if((kf * dn_vgpu_f[idxdst].y) < 0 && dn_vgpu_a[idxsrc] < 0){	// Move to down (right vertical)
//			//	screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx1;
//			//	screen[dn_vgpu_a[idxsrc]].Pos.y = normy0;
//			//	dn_vgpu_a[idxdst] = -1;
//			//}
		});
} // ////////////////////////////////////////////////////////////////////////////
#undef normx0
#undef normx1
#undef normy0
#undef normy1

#undef idc0
#undef idc1
#undef idc2
#undef idc3

#undef Y
#undef X

