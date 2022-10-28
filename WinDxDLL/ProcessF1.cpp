#include "ProcessF.h"
#include <amp_math.h>
#define X 1
#define Y 0
namespace executor{
	using namespace concurrency;
	using namespace concurrency::graphics;
	void ProcessF::gpuRun1(const int ncurlay){
		_ASSERTE(ncurlay > 0);
		const LayMid& up_lay = lays->vMidLays[ncurlay];
		LayMid& dn_lay = lays->vMidLays[ncurlay - 1];
		const ProcessParam* param = up_lay.param;
		const float klayf = param->klayf;
		const float klayv = param->klayv;
		const float kLaminar = param->kLaminar;
		const float kTurbul = param->kTurbul;
		const float levelTurbul = param->levelTurbul;

		const concurrency::array<int, 2>& up_vgpu_a = *up_lay.va.vgpu;
		const concurrency::array<float_2, 2>& up_vgpu_f = *up_lay.vf.vgpu;
		concurrency::array<float_2, 2>& up_vgpu_v = *up_lay.vv.vgpu;

		concurrency::array<int, 2>& dn_vgpu_a = *dn_lay.va.vgpu;
		concurrency::array<float_2, 2>& dn_vgpu_f = *dn_lay.vf.vgpu;
		concurrency::array<float_2, 2>& dn_vgpu_v = *dn_lay.vv.vgpu;

		const concurrency::array<float_2, 2>& f_masks = *fmasks->gv;

		parallel_for_each(up_vgpu_a.extent,
			[&dn_vgpu_a, &dn_vgpu_f, &dn_vgpu_v,
			&up_vgpu_a, &up_vgpu_f, &up_vgpu_v,
			&f_masks, klayf, klayv, kLaminar, kTurbul, levelTurbul
			](index<2> idx)restrict(amp) {
				const int x0 = idx[X] * 2;
				const int y0 = idx[Y] * 2;

#define idc0 (index<2>(y0, x0))
#define idc1 (index<2>(y0, x0 + 1))
#define idc2 (index<2>(y0 + 1, x0))
#define idc3 (index<2>(y0 + 1, x0 + 1))

				dn_vgpu_f[idc0] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][0] * klayf;
				dn_vgpu_f[idc1] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][1] * klayf;
				dn_vgpu_f[idc2] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][2] * klayf;
				dn_vgpu_f[idc3] = up_vgpu_f[idx] + f_masks[up_vgpu_a[idx]][3] * klayf;

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
				 
				
				//float_2 avg4 = 
				//	dn_vgpu_v[idc0] + 
				//	dn_vgpu_v[idc1] + 
				//	dn_vgpu_v[idc2] + 
				//	dn_vgpu_v[idc3];

				//avg4 *= 0.5f;	// 4 * [0...1]

				//float x2 = avg4.x * avg4.x;
				//float y2 = avg.y * avg.y;
				//float hypot2 = x2 + y2;
				//float hypot = concurrency::precise_math::hypotf(1.f, 1.f);
				//if(hypot > levelv){	// high speed
				//	dn_vgpu_v[idc0] += float_2(-kDissipation, -kDissipation);
				//	dn_vgpu_v[idc1] += float_2(kDissipation, -kDissipation);
				//	dn_vgpu_v[idc2] += float_2(-kDissipation, kDissipation);
				//	dn_vgpu_v[idc3] += float_2(kDissipation, kDissipation);
				//} else{
				//	// TODO: kAvgv*avg pick out?
				//	dn_vgpu_v[idc0] += float_2(kConcentration, kConcentration) + kAvgv * avg;
				//	dn_vgpu_v[idc1] += float_2(-kConcentration, kConcentration) + kAvgv * avg;
				//	dn_vgpu_v[idc2] += float_2(kConcentration, -kConcentration) + kAvgv * avg;
				//	dn_vgpu_v[idc3] += float_2(-kConcentration, -kConcentration) + kAvgv * avg;
				//}
			});
	} // ///////////////////////////////////////////////////////////////////////////
}
#undef idc0
#undef idc1
#undef idc2
#undef idc3
#undef Y
#undef X
