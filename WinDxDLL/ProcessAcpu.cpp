#include "ProcessA.h"
#include <ppl.h>				//	parallel_for
using namespace concurrency;
using namespace concurrency::graphics;

void ProcessA::cpuRun(const int n_lay){
	_ASSERTE(n_lay > 0);
	const std::array<int, 16>& a_masks = amask->vcpu;
	LayMid* up_lay = lays->vMidLays[n_lay];
	LayMid* dn_lay = lays->vMidLays[n_lay - 1];

	std::vector<int>& dn_vcpu_a = dn_lay->va.vcpu;
	std::vector<float_2>& dn_vcpu_f = dn_lay->vf.vcpu;

	const size_t maxy = (size_t)up_lay->sz.y;
	const size_t maxx = (size_t)up_lay->sz.x;
	const size_t szx_bottom = maxx * 2;

	for(size_t y = 0; y < maxy; y++){
		const auto basex = y * maxx;
		const auto baseidx = y * szx_bottom;
		for(size_t x = 0; x < maxx; x++){				// same in mtRun(int n_lay)
			const size_t idDn1 = 2 * (baseidx + x);
			const size_t idDn2 = idDn1 + szx_bottom;
			const auto idUp = basex + x;
			up_lay->va.vcpu[idUp] =
				(a_masks[dn_vcpu_a[idDn1]]) +				// << 0
				(a_masks[dn_vcpu_a[idDn1 + 1]] << 1) +		// << 1
				(a_masks[dn_vcpu_a[idDn2]] << 2) +			// << 2
				(a_masks[dn_vcpu_a[idDn2 + 1]] << 3);		// << 3;

			up_lay->vf.vcpu[idUp] =
				dn_vcpu_f[idDn1] + dn_vcpu_f[idDn1 + 1] +
				dn_vcpu_f[idDn2] + dn_vcpu_f[idDn2 + 1];
		}
	}
} // ///////////////////////////////////////////////////////////////////////////
void ProcessA::mtRun(const int n_lay){
	_ASSERTE(n_lay > 0);
	const std::array<int, 16>& a_masks = amask->v;
	LayMid* up_lay = &lays->vMidLays[n_lay];
	LayMid* dn_lay = &lays->vMidLays[n_lay - 1];

	std::vector<int>& dn_vcpu_a = dn_lay->va.vcpu;
	std::vector<float_2>& dn_vcpu_f = dn_lay->vf.vcpu;

	const size_t maxy = (size_t)up_lay->sz.y;
	const size_t maxx = (size_t)up_lay->sz.x;
	const size_t szx_bottom = maxx * 2;

	parallel_for(size_t(0), maxy, [&](size_t y) {
		const auto basex = y * maxx;
		const auto baseidx = y * szx_bottom;
		for(size_t x = 0; x < maxx; x++){				// same in cpuRun(int n_lay)
			const size_t idDn1 = 2 * (baseidx + x);
			const size_t idDn2 = idDn1 + szx_bottom;
			const auto idUp = basex + x;
			up_lay->va.vcpu[idUp] =
				(a_masks[dn_vcpu_a[idDn1]]) +				// << 0
				(a_masks[dn_vcpu_a[idDn1 + 1]] << 1) +		// << 1
				(a_masks[dn_vcpu_a[idDn2]] << 2) +			// << 2
				(a_masks[dn_vcpu_a[idDn2 + 1]] << 3);		// << 3;

			up_lay->vf.vcpu[idUp] =
				dn_vcpu_f[idDn1] + dn_vcpu_f[idDn1 + 1] +
				dn_vcpu_f[idDn2] + dn_vcpu_f[idDn2 + 1];
		}
		});
} // ///////////////////////////////////////////////////////////////////////////
