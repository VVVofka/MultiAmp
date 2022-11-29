#pragma once
#include "Lay0.h"
#include "LayMid.h"
#include "LaysCPUCfg.h"

class Lays{	//  : public Lay0
public:
	Lays(structAll* cfg_all, accelerator_view* m_accl_view);
	~Lays();

	Lay0 lay0;
	std::vector<LayMid*> vMidLays;
	int cntMidLays = 0;

	//bool isLoad();

	std::string sDumpAcpu(int idx = -1, const int digits = 2)const;
	std::string sDumpAgpu(int idx = -1, const int digits = 2)const;
	std::string sDumpA(int idx = -1, const int digits = 2)const;

	std::string sDumpFcpu(int idx = -1, const int digits = 2)const;
	std::string sDumpFgpu(int idx = -1, const int digits = 2)const;
	std::string sDumpF(int idx = -1, const int digits = 2)const;

	std::string DumpAcpu(int idx = -1, const int digits = 2)const;
	std::string DumpAgpu(int idx = -1, const int digits = 2)const;
	std::string DumpA(int idx = -1, const int digits = 2)const;

	std::string DumpFcpu(int idx = -1, const int digits = 2)const;
	std::string DumpFgpu(int idx = -1, const int digits = 2)const;
	std::string DumpF(int idx = -1, const int digits = 2)const;

private:
	static bool correctMtCpu(structAll* cfg_all);

}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

