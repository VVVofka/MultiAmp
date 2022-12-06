#include <amp_math.h>
#include "ProcessF.h"
#include "..\myUtil.h"	// NORMAL_TO_AREA
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

	parallel_for_each(up_vgpu_a.extent,
		[&dn_vgpu_a, &up_vgpu_a, &mid_vgpu_f, &up_vgpu_f, &screen,
		&f_masks, shift, signFor0
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
			float curf = mid_vgpu_f[index<2>(idUp[Y] * 2, idUp[X] * 2)].x;
			const int x0 = (idUp[X] * 4 + shift.x) % SIZEX;	// TODO: define?

#define EXIST_POS1(IDX_Y_A_CLAMP, IDX_X_A, SHIFT) (sign(dn_vgpu_a[index<2>((IDX_Y_A_CLAMP), (IDX_X_A) % SIZEX)] + 1) << (SHIFT))
#define EXIST_POS_ALL(IDX_Y_A_CLAMP, IDX_X0_A) (EXIST_POS1(IDX_Y_A_CLAMP, IDX_X0_A + 3, 6) | EXIST_POS1(IDX_Y_A_CLAMP, IDX_X0_A + 2, 4) | EXIST_POS1(IDX_Y_A_CLAMP, IDX_X0_A + 1, 2) | EXIST_POS1(IDX_Y_A_CLAMP,IDX_X0_A, 0))

#define DIR_POS1(IDMASK, SHIFT) (((signbitf(f_masks[idmask + IDMASK].x + curf) + signFor0) / 2) << SHIFT)
#define DIR_POS_ALL(IDMASK0) (DIR_POS1(IDMASK0 + 5, 7) | DIR_POS1(IDMASK0 + 4, 5) | DIR_POS1(IDMASK0 + 1, 3) | DIR_POS1(IDMASK0, 1))

#define CHANGE \
if(vmaskmov[idmove] & 0xb110000){ \
	const int posxsrc = (x0 + vmaskmov[idmove] & 0xb11) % SIZEX; \
	const int posxdst = (x0 + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX; \
	dn_vgpu_a[y0][posxdst] = dn_vgpu_a[y0][posxsrc]; \
	dn_vgpu_a[y0][posxsrc] = -1; \
	screen[dn_vgpu_a[y0][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX); }

			int y0 = (idUp[Y] * 4 + shift.y) % SIZEY;
			int idmove = DIR_POS_ALL(0) | EXIST_POS_ALL(y0, x0);
			CHANGE
				//if(vmaskmov[idmove] & 0xb110000){
				//	const int posxsrc = (x0 + vmaskmov[idmove] & 0xb11) % SIZEX;
				//	const int posxdst = (x0 + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
				//	dn_vgpu_a[y0][posxdst] = dn_vgpu_a[y0][posxsrc];
				//	dn_vgpu_a[y0][posxsrc] = -1;
				//	screen[dn_vgpu_a[y0][posxdst]].Pos.x = NORMAL_TO_AREA(posxdst, SIZEX);
				//}

				y0 = (y0 + 1) % SIZEY;
			idmove = DIR_POS_ALL(2) | EXIST_POS_ALL(y0, x0);
			CHANGE

				y0 = (y0 + 1) % SIZEY;
			idmove = DIR_POS_ALL(8) | EXIST_POS_ALL(y0, x0);
			CHANGE

				y0 = (y0 + 1) % SIZEY;
			idmove = DIR_POS_ALL(10) | EXIST_POS_ALL(y0, x0);
			CHANGE

				/*				(((signbitf(f_masks[idmask + 5].x + curf) + signFor0) / 2) << 7) |
								(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 3) % SIZEX)] + 1) << 6) |

								(((signbitf(f_masks[idmask + 4].x + curf) + signFor0) / 2) << 5) |
								(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 2) % SIZEX)] + 1) << 4) |

								(((signbitf(f_masks[idmask + 1].x + curf) + signFor0) / 2) << 3) |
								(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 1) % SIZEX)] + 1) << 2) |

								(((signbitf(f_masks[idmask].x + curf) + signFor0) / 2) << 1) |
								(sign(dn_vgpu_a[index<2>(y0, (x0 + shift.x + 0) % SIZEX)] + 1) << 0); */
								//if(vmaskmov[idmove] & 0xb110000){
									//const int posxsrc = (x0 + vmaskmov[idmove] & 0xb11) % SIZEX;
									//const int posxdst = (x0 + (vmaskmov[idmove] >> 2) & 0xb11) % SIZEX;
									//dn_vgpu_a[posxdst][X] = dn_vgpu_a[posxsrc][X];
									//dn_vgpu_a[posxsrc][X] = -1;
									//screen[dn_vgpu_a[index<2>(y0, (X0_SHIFT + XOFFSET) % SIZEX)]] = mad(y0, SIZEX, 0);
								//}

		});
} // ////////////////////////////////////////////////////////////////////////////
#undef Y
#undef X

