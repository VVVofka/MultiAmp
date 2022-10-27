#pragma once
enum class MCPUtype{ GPU = 0, MT = 1, CPU = 2 };

class MLaysCPUCfg{
public:
	int gpu;	// lays count for parallel on gpu, include lay0
	int mt;		// lays count for parallel on cpu
	int cpu;	// lays count for cpu

	MLaysCPUCfg(){ gpu = mt = cpu = 0; };
	MLaysCPUCfg(int gpu, int mt, int cpu){
		this->gpu = gpu;
		this->mt = mt;
		this->cpu = cpu;
	};

	int cnt() const{ return gpu + mt + cpu; }
	int cntmid() const{ return gpu + mt + cpu - 1; }
	bool check() const{ return gpu >= 1 && mt >= 0 && cpu >= 0; }
	bool check(int cnt_lays) const{ return check() && cnt() == cnt_lays && cnt_lays >= 2; }

	MCPUtype getType(int idx) const{
		if(idx < gpu)	// = used both lays (up & dn) in parallel_for_each()
			return MCPUtype::GPU;
		if(idx < gpu + mt)
			return MCPUtype::MT;
		return MCPUtype::CPU;
	} // //////////////////////////////////////////////////////////////////////
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
