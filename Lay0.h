#pragma once
#include <vector>
#include "LayBase.h"
#include "Vertex2D.h"

namespace executor{
	using namespace std;
	class Lay0 : public LayBase{
	public:
		concurrency::array<Vertex2D, 1>* vgpuScreen = NULL;		//[pointsCnt] for render [-1...+1]

		void Create(
			const int_2 sz_0,
			const vector<int>& vi_inp,			// xy.x * xy.y
			const vector<float_2>& vf_inp,		// (szx_0 * szy_0)
			const vector<float_2>& vv_inp,		// (szx_0 * szy_0)
			const float k_decAfterMove
		);
		~Lay0();

		int countPoint = 0;
		float kDecAfterMove = 0.f;
		float kinert = 0.f;

		int SetRndScreenPoints(const int count, const int seed = -1);
		void SetScreenPoints(const int count, const int_2* ptr);

		bool isLoad()const;
		string sDumpA(const int digits)const;
		string sDumpF(const int digits)const;
		string sDumpV(const int digits)const;
		string DumpA(const int digits = 2)const;
		string DumpF(const int digits = 2)const;
		string DumpV(const int digits = 3)const;
		void cpuPoint2gpuPoint(const int count_point);
	private:
			//inline int va_at(const int x, const int y) const;
		//inline int& va_at(const int_2 xy) { return vcpu[xy.y * (size_t)sz.x + xy.x].idx_a; }
			//inline float_2 vf_at(const int x, const int y) const;
		//inline float_2& vf_at(const int_2 xy) { return vcpu[xy.y * (size_t)sz.x + xy.x].f; }
		//size_t getCntPoint(const std::vector<int>& v_inp);

		static int defPointsCnt(const std::vector<int>& vi_inp);
	};
}
