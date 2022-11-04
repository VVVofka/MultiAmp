#pragma once
#include<string>
#include "VGpuCpu.h"

#ifdef _DEBUG
#define MYDBG
#endif _DEBUG

namespace executor{
	using namespace std;
	class LayBase{
	public:
		VGpuCpu<int> va;
		VGpuCpu<float_2> vf;
		VGpuCpu<float_2> vv;

		void Create(const int_2 xy, const bool is_gpu);

		int_2 sz;
		inline int sz1() const { return sz.x * sz.y; }
		inline int id(const int x, const int y) const { return y * sz.x + x; }

		void gpu2cpu();
		void cpu2gpu();

		bool isLoad()const;

	protected:
		string sDumpA(const int digits)const;
		string sDumpF(const int digits)const;
		string sDumpV(const int digits)const;

	private:
		string sDump(const VGpuCpu<float_2>& v, const int digits)const;
	};
}
