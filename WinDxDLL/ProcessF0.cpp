#include <amp_math.h>
#include "ProcessF.h"
#include "ProcessParam.h"

namespace executor{
	using namespace concurrency;
	using namespace concurrency::graphics;
	using namespace concurrency::direct3d;
#define X 1
#define Y 0

	void ProcessF::gpuRun0(const int_2 shift){
		const LayMid& up_lay = lays->vMidLays[0];
		Lay0& lay_0 = lays->lay0;
		const ProcessParam* param = up_lay.param;
		const float klayf = param->klayf;
		const float kLaminar = param->kLaminar;
		const float kTurbul = param->kTurbul;
		const float levelTurbul = param->levelTurbul;

		const concurrency::array<int, 2>& up_vgpu_a = *up_lay.va.vgpu;
		const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay.vf.vgpu;

		concurrency::array<int, 2>& dn_vgpu_a = *lay_0.va.vgpu;
		concurrency::array<float_2, 2>& dn_vgpu_f = *lay_0.vf.vgpu;

		concurrency::array<Vertex2D, 1>& screen = *lay_0.vgpuScreen;
		const concurrency::array<float_2, 2>& f_masks = *fmasks->gv;
		const float_2 rSizeDn(lay_0.sz);
		const float kDecAfterMove = lay_0.kDecAfterMove;

		parallel_for_each(up_vgpu_a.extent,
			[&dn_vgpu_a, &dn_vgpu_f, 
			&up_vgpu_a, &up_vgpu_f, 
			&f_masks, &screen,
			shift, klayf, kLaminar, kTurbul, levelTurbul, kDecAfterMove, rSizeDn, kf
			](index<2> idx)restrict(amp) {
				// TODO: optimize!
				const int x0 = mad(idx[X], 2, shift.x) % dn_vgpu_a.extent[X];
				const int y0 = mad(idx[Y], 2, shift.y) % dn_vgpu_a.extent[Y];
				const int x1 = (x0 + 1) % dn_vgpu_a.extent[X];
				const int y1 = (y0 + 1) % dn_vgpu_a.extent[Y];

#define idc0 (index<2>(y0, x0))
#define idc1 (index<2>(y0, x1))
#define idc2 (index<2>(y1, x0))
#define idc3 (index<2>(y1, x1))

				dn_vgpu_f[idc0] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][0] * klayf + dn_vgpu_f[idc0] * kinert;
				dn_vgpu_f[idc1] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][1] * klayf + dn_vgpu_f[idc1] * kinert;
				dn_vgpu_f[idc2] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][2] * klayf + dn_vgpu_f[idc2] * kinert;
				dn_vgpu_f[idc3] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][3] * klayf + dn_vgpu_f[idc3] * kinert;

				float_2 avgv = (dn_vgpu_v[idc0] += up_vgpu_v[idx] * klayv);
				avgv += (dn_vgpu_v[idc1] += up_vgpu_v[idx] * klayv);
				avgv += (dn_vgpu_v[idc2] += up_vgpu_v[idx] * klayv);
				avgv += (dn_vgpu_v[idc3] += up_vgpu_v[idx] * klayv);

				float hypo = fast_math::sqrtf(avgv.x * avgv.x + avgv.y * avgv.y);

				if(hypo < levelTurbul){
					avgv *= kLaminar;
					dn_vgpu_v[idc0] += avgv;
					dn_vgpu_v[idc1] += avgv;
					dn_vgpu_v[idc2] += avgv;
					dn_vgpu_v[idc3] += avgv;
				} else{
					hypo *= kTurbul;
					dn_vgpu_v[idc0] -= hypo;
					dn_vgpu_v[idc1] += float_2(hypo, -hypo);
					dn_vgpu_v[idc2] += float_2(-hypo, hypo);
					dn_vgpu_v[idc3] += hypo;
				}

				// TODO: Blocks (p.207 Greg) or Textures (p.212 Greg)
				// TODO: разнести x, y, i (p.203 Greg)

				// move vscreen points
#define normx0 (mad((float)(2 * x0 + 1), rSizeDn.x, -1.f))
#define normx1 (mad((float)(2 * x1 + 1), rSizeDn.x, -1.f))
#define normy0 (mad((float)(2 * y0 + 1), rSizeDn.y, -1.f))
#define normy1 (mad((float)(2 * y1 + 1), rSizeDn.y, -1.f))

				//	Bottom Horizontal
				auto idxsrc = idc0;
				auto idxdst = idc1;
				if((kf * dn_vgpu_f[idxsrc].x + kv * dn_vgpu_v[idxsrc].x) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to rigth (bottom horizontal)
					dn_vgpu_f[idxsrc].x *= kDecAfterMove;
					screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx1;
					screen[dn_vgpu_a[idxdst]].Pos.y = normy0;
					dn_vgpu_a[idxsrc] = -1;
				} else if((kf * dn_vgpu_f[idxdst].x + kv * dn_vgpu_v[idxdst].x) < 0 && dn_vgpu_a[idxsrc] < 0){ // Move to left (bottom horizontal)
					dn_vgpu_f[idxdst].x *= kDecAfterMove;
					screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx0;
					screen[dn_vgpu_a[idxsrc]].Pos.y = normy0;
					dn_vgpu_a[idxdst] = -1;
				}

				// Left Vertical
				idxdst = idc2;
				if((kf * dn_vgpu_f[idxsrc].y + kv * dn_vgpu_v[idxsrc].y) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to up (left vertical)
					dn_vgpu_f[idxsrc].y *= kDecAfterMove;
					screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx0;
					screen[dn_vgpu_a[idxdst]].Pos.y = normy1;
					dn_vgpu_a[idxsrc] = -1;
				} else if((kf * dn_vgpu_f[idxdst].y + kv * dn_vgpu_v[idxdst].y) < 0 && dn_vgpu_a[idxsrc] < 0){	// Move to down (left vertical)
					dn_vgpu_f[idxdst].y *= kDecAfterMove;
					screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx0;
					screen[dn_vgpu_a[idxsrc]].Pos.y = normy0;
					dn_vgpu_a[idxdst] = -1;
				}

				// Top Horizontal
				idxsrc = idc2;
				idxdst = idc3;
				if((kf * dn_vgpu_f[idxsrc].x + kv * dn_vgpu_v[idxsrc].x) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to right (top horizontal)
					dn_vgpu_f[idxsrc].x *= kDecAfterMove;
					screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx1;
					screen[dn_vgpu_a[idxdst]].Pos.y = normy1;
					dn_vgpu_a[idxsrc] = -1;
				} else if((kf * dn_vgpu_f[idxdst].x + kv * dn_vgpu_v[idxdst].x) < 0 && dn_vgpu_a[idxsrc] < 0){	// Move to left (top horizontal)
					dn_vgpu_f[idxdst].x *= kDecAfterMove;
					screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx0;
					screen[dn_vgpu_a[idxsrc]].Pos.y = normy1;
					dn_vgpu_a[idxdst] = -1;
				}

				// Right Vertical
				idxsrc = idc1;
				if((kf * dn_vgpu_f[idxsrc].y + kv * dn_vgpu_v[idxsrc].y) > 0 && dn_vgpu_a[idxdst] < 0){	// Move to up (right vertical)
					dn_vgpu_f[idxsrc].y *= kDecAfterMove;
					screen[dn_vgpu_a[idxdst] = dn_vgpu_a[idxsrc]].Pos.x = normx1;
					screen[dn_vgpu_a[idxdst]].Pos.y = normy1;
					dn_vgpu_a[idxsrc] = -1;
				} else if((kf * dn_vgpu_f[idxdst].y + kv * dn_vgpu_v[idxdst].y) < 0 && dn_vgpu_a[idxsrc] < 0){	// Move to down (right vertical)
					dn_vgpu_f[idxdst].y *= kDecAfterMove;
					screen[dn_vgpu_a[idxsrc] = dn_vgpu_a[idxdst]].Pos.x = normx1;
					screen[dn_vgpu_a[idxsrc]].Pos.y = normy0;
					dn_vgpu_a[idxdst] = -1;
				}
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
}

