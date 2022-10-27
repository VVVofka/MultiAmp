#pragma once
#include <vector>
#include <string>

#include "MDX.h"
#include "MVGpuCpu.h"

class MLayBase{
public:
	int_2 sz;

	MVGpuCpu<int> va;
	MVGpuCpu<float_2> vf;

	void Create(const int_2 xy, const bool is_gpu);
	inline int id(const int x, const int y) const{ return y * sz.x + x; }

	void gpu2cpu();
	void cpu2gpu();

	bool isLoad()const;

protected:
	std::string sDumpA(const int digits)const;
	std::string sDumpF(const int digits)const;

private:
	std::string sDump(const MVGpuCpu<float_2>& v, const int digits)const;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

