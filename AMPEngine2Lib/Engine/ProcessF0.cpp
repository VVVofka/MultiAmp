#include "ProcessF.h"
void ProcessF::gpuRun0(const int_2 shift0, const uint iter){
	gpuRun0Split1(shift0);
	const int signFor0 = (iter & 1) + 1; // 1 or 2
	if(iter & 2){
		gpuRun0Split2x(shift0, signFor0);
		gpuRun0Split2y(shift0, signFor0);
	} else{
		gpuRun0Split2y(shift0, signFor0);
		gpuRun0Split2x(shift0, signFor0);
	}
} // /////////////////////////////////////////////////////////////////////////////////////

