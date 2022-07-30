#pragma once
enum class CPUtype{ GPU = 0, MT = 1, CPU = 2 };

class LaysCPUCfg{
public:
	int gpu;	// lays count for parralel on gpu, include lay0
	int mt;		// lays count for parralel on cpu
	int cpu;	// lays count for cpu

	LaysCPUCfg(){ gpu = mt = cpu = 0; };
	LaysCPUCfg(int gpu, int mt, int cpu){
		this->gpu = gpu;
		this->mt = mt;
		this->cpu = cpu;
	};

	int cnt() const{ return gpu + mt + cpu; }
	int cntmid() const{ return gpu + mt + cpu - 1; }
	bool check() const{ return gpu >= 1 && mt >= 0 && cpu >= 0; }
	bool check(int cnt_lays) const{ return check() && cnt() == cnt_lays && cnt_lays >= 2; }

	CPUtype getType(int idx) const{
		if(idx < gpu)	// = used both lays (up & dn) in parallel_for_each()
			return CPUtype::GPU;
		if(idx < gpu + mt)
			return CPUtype::MT;
		return CPUtype::CPU;
	}
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
