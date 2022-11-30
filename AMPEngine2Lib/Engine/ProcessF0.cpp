#include <amp_math.h>
#include "ProcessF.h"
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
	//const float klayf = up_lay->kF;
	const concurrency::array<float_2, 1>& f_masks = *up_lay->kF.vgpu;	//const concurrency::array<float_2, 1>& f_masks = *fmasks->vgpu;

	LayMid* dn_lay = lays->vMidLays[0];
	const concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay->vf.vgpu;

	Lay0* lay_0 = &lays->lay0;
	concurrency::array<int, 2>& dn_vgpu_a = *lay_0->va.vgpu;
	concurrency::array<Vertex2D, 1>& screen = *lay_0->vgpuScreen;
	const float_2 rSizeDn(lay_0->sz);

	const uint signFor0 = (iter & 1) + 1; // 1 or 2

	parallel_for_each(up_vgpu_a.extent,
		[&dn_vgpu_a, &up_vgpu_a, &dn_vgpu_f, &up_vgpu_f, &screen,
		&f_masks, shift, rSizeDn, signFor0
		](index<2> idUp)restrict(amp) {
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

			const int idmask = up_vgpu_a[idUp] * 16;	// TODO: define?
			float upf = dn_vgpu_f[index<2>(idUp[Y] * 2, idUp[X] * 2)].x;
			const int x0 = idUp[X] * 4;	// TODO: define?
			const int y0 = (idUp[Y] * 4 + shift.y) % SIZEY;
#define DIR_POS1(IDMASK, SHIFT) (((signbitf(f_masks[idmask + IDMASK].x + upf) + signFor0) / 2) << SHIFT)
#define DIR_POS_ALL (DIR_POS1(5, 7) | DIR_POS1(4, 5) | DIR_POS1(1, 3) | DIR_POS1(0, 1))
#define X0_SHIFT (x0 + shift.x)	/* TODO: const int ? */
#define EXIST_POS1(XOFFSET, SHIFT) (sign(dn_vgpu_a[index<2>(y0, (X0_SHIFT + XOFFSET) % SIZEX)] + 1) << SHIFT)
#define EXIST_POS_ALL (EXIST_POS1(3, 6) | EXIST_POS1(2, 4) | EXIST_POS1(1, 2) | EXIST_POS1(0, 0))
			const int idmove = DIR_POS_ALL | EXIST_POS_ALL;
/*				(((signbitf(f_masks[idmask + 5].x + upf) + signFor0) / 2) << 7) |
				(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 3) % SIZEX)] + 1) << 6) |

				(((signbitf(f_masks[idmask + 4].x + upf) + signFor0) / 2) << 5) |
				(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 2) % SIZEX)] + 1) << 4) |

				(((signbitf(f_masks[idmask + 1].x + upf) + signFor0) / 2) << 3) |
				(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 1) % SIZEX)] + 1) << 2) |

				(((signbitf(f_masks[idmask].x + upf) + signFor0) / 2) << 1) |
				(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 0) % SIZEX)] + 1) << 0); */
			const int cnt = (vmaskmov[idmove] >> 4) & 0xb11;
			if(cnt){
				const int posxsrc = (x0 + vmaskmov[idmove] & 0xb11) % SIZEX;
				const int posxdst = (x0 + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
				const auto tmp = dn_vgpu_a[posxsrc];
				dn_vgpu_a[posxsrc] = dn_vgpu_a[posxdst];
				dn_vgpu_a[posxdst] = tmp;
			}
			//uint_2 dn0 = mid0 * 2;
			//uint_2 ofs = iter2;

			//index<2> src = index<2>(dn0.y, dn0.x);
			//index<2> dst = index<2>(dn0.y + ofs.y, dn0.x + ofs.x);
			//float_2 fsrc = curf + f_masks[idmask] * klayf;
			//float_2 fdst = curf + f_masks[idmask + 2 * ofs.y + ofs.x] * klayf;


			//float_2 f0 = curf + f_masks[idmask++] * klayf;
			//float_2 f1 = curf + f_masks[idmask++] * klayf;
			//float_2 f2 = curf + f_masks[idmask++] * klayf;
			//float_2 f3 = curf + f_masks[idmask++] * klayf;
			//idmask += 4;

			//src = index<2>(y += iter2.x, x += iter2.y);
			//dst = index<2>(y + iter2.y, x + iter2.x);

			//src = index<2>(y += iter2.x, x += iter2.y);
			//dst = index<2>(y + iter2.y, x + iter2.x);

			//src = index<2>(y += iter2.x, x += iter2.y);
			//dst = index<2>(y + iter2.y, x + iter2.x);


			//src = index<2>(y = 2, x = 0);
			//dst = index<2>(y + iter2.y, x + iter2.x);

			//src = index<2>(y += iter2.x, x += iter2.y);
			//dst = index<2>(y + iter2.y, x + iter2.x);

			//src = index<2>(y += iter2.x, x += iter2.y);
			//dst = index<2>(y + iter2.y, x + iter2.x);

			//src = index<2>(y += iter2.x, x += iter2.y);
			//dst = index<2>(y + iter2.y, x + iter2.x);

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
//			const int x0 = mad(idx[X], 2, shift.x) % SIZEX;
//			const int y0 = mad(idx[Y], 2, shift.y) % SIZEY;
//			const int x1 = (x0 + 1) % SIZEX;
//			const int y1 = (y0 + 1) % SIZEY;
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

