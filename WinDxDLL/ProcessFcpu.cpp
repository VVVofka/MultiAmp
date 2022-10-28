#include "ProcessF.h"
#include<float.h>
namespace executor{
	using namespace concurrency;

	void ProcessF::cpuRun(const int ncurlay){
		_ASSERTE(ncurlay > 0);
		const LayMid* up_lay = &lays->vMidLays[ncurlay];
		LayMid* dn_lay = &lays->vMidLays[ncurlay - 1];

		const std::vector<int>& up_vcpu_a = up_lay->va.vcpu;
		const std::vector<float_2>& up_vcpu_f = up_lay->vf.vcpu;
		const std::vector<float_2>& up_vcpu_v = up_lay->vv.vcpu;

		const std::vector<int>& dn_vcpu_a = dn_lay->va.vcpu;	// const
		std::vector<float_2>& dn_vcpu_f = dn_lay->vf.vcpu;
		std::vector<float_2>& dn_vcpu_v = dn_lay->vv.vcpu;

		const size_t szUpY = (size_t)up_lay->sz.y;
		const size_t szUpX = (size_t)up_lay->sz.x;
		const size_t szDnX = szUpX * 2;
		const std::array<float_2, 16 * 4>& f_masks = fmasks->v;

		for(size_t y = 0, idUp = 0; y < szUpY; y++){
			for(size_t x = 0; x < szUpX; x++, idUp++){
				size_t idxDn0 = 2 * (y * szDnX + x);
				const size_t idcDn[4] = {idxDn0, idxDn0 + 1, idxDn0 + szDnX, idxDn0 + szDnX + 1};	// szDnX
				//const float_2 vdis[4] = {float_2(-1,-1), float_2(1,-1), float_2(-1,1), float_2(1,1)};

				const int a4 = up_vcpu_a[idUp] * 4;
				const float_2 up_f = up_vcpu_f[idUp];
				const float_2 up_v = up_vcpu_v[idUp];

				float hypo = hypotf(up_vcpu_v[idUp].x, up_vcpu_v[idUp].y);
				float turbul = hypo * up_lay->param->kTurbul;
				for(int j = 3; j >= 0; j--){
					const size_t idDn = idcDn[j];
					dn_vcpu_f[idDn] = up_f + f_masks[a4 + j] * up_lay->param->klayf;
					if(hypo < up_lay->param->levelTurbul){
						dn_vcpu_v[idDn] += up_v * up_lay->param->kLaminar;
					} else{
						dn_vcpu_v[idDn].x += turbul * ((j & 1) * 2 - 1);
						dn_vcpu_v[idDn].y += turbul * (((j >> 1) & 1) * 2 - 1);
					}
				}
			}	// x
		}	//	y
	} // ///////////////////////////////////////////////////////////////////////////
	void ProcessF::mtRun(const int ncurlay){
		_ASSERTE(ncurlay > 0);
		const LayMid* up_lay = &lays->vMidLays[ncurlay];
		LayMid* dn_lay = &lays->vMidLays[ncurlay - 1];

		const std::vector<int>& up_vcpu_a = up_lay->va.vcpu;
		const std::vector<float_2>& up_vcpu_f = up_lay->vf.vcpu;
		const std::vector<float_2>& up_vcpu_v = up_lay->vv.vcpu;

		std::vector<int>& dn_vcpu_a = dn_lay->va.vcpu;
		std::vector<float_2>& dn_vcpu_f = dn_lay->vf.vcpu;
		std::vector<float_2>& dn_vcpu_v = dn_lay->vv.vcpu;

		const size_t szUpY = (size_t)up_lay->sz.y;
		const size_t szUpX = (size_t)up_lay->sz.x;
		const size_t szDnX = szUpX * 2;
		const std::array<float_2, 16 * 4>& f_masks = fmasks->v;

		parallel_for(size_t(0), szUpY, [&](size_t y){
			for(size_t x = 0; x < szUpX; x++){
				size_t idxDn0 = 2 * (y * szDnX + x);
				size_t idcDn[4] = {idxDn0, idxDn0 + 1, idxDn0 + szDnX, idxDn0 + szDnX + 1};

				size_t idUp = y * szUpX + x;
				const int a4 = up_vcpu_a[idUp] * 4;
				const float_2 up_v = up_vcpu_v[idUp];
				const float_2 up_f = up_vcpu_f[idUp];
				float hypo = hypotf(up_vcpu_v[idUp].x, up_vcpu_v[idUp].y);
				float turbul = hypo * up_lay->param->kTurbul;
				for(int j = 3; j >= 0; j--){
					const size_t idDn = idcDn[j];
					dn_vcpu_f[idDn] = up_f + f_masks[a4 + j] * up_lay->param->klayf;
					if(hypo < up_lay->param->levelTurbul){
						dn_vcpu_v[idDn] += up_v * up_lay->param->kLaminar;
					} else{
						dn_vcpu_v[idDn].x += turbul * ((j & 1) * 2 - 1);
						dn_vcpu_v[idDn].y += turbul * (((j >> 1) & 1) * 2 - 1);
					}
				}
			}		//for(size_t x = 0; x < szUpX; x++)
			});	// parallel_for(size_t(0), szUpY, [&](size_t y)
	} // ///////////////////////////////////////////////////////////////////////////
}