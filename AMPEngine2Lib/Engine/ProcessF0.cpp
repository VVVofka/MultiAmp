#include "ProcessF.h"
void ProcessF::gpuRun0(const int_2 shift0, const uint iter){
	gpuRun0Split1(shift0);
	gpuRun0Split2(shift0, iter);
} // /////////////////////////////////////////////////////////////////////////////////////

