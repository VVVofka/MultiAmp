#pragma once
#include <cstdint>
class LehmerRng{
	double k = 0;
	uint32_t seed;
public:
	LehmerRng(uint32_t init_seed = 0){
		if(init_seed != 0)
			seed = init_seed;
		else
			do{
				seed = (uint32_t)(time(0) % 0xfffffffb);
			} while(seed == 0);
	} // //////////////////////////////////////////////////////////////////////////////////

	// < 0xfffffffb for 
	// Generate [0 ... setSeed(max)[
	void setUpper(uint32_t max){
		k = max / (double)0xfffffffb;
	} // ////////////////////////////////////////////////////////////////////////////////////

	// < 0xfffffffb
	void setSeed(uint32_t newval){
		seed = newval % 0xfffffffb;
	} // ////////////////////////////////////////////////////////////////////////////////////

	// Generate ]0 ... 0xfffffffb[
	uint32_t rand(){
		return seed = (uint64_t)seed * 279470273u % 0xfffffffb;
	} // ////////////////////////////////////////////////////////////////////////////////////

	// Generate ]0 ... max[
	uint32_t rand(uint32_t max){
		double koef = max / (double)0xfffffffb;
		return uint32_t(rand() * koef);
	} // ////////////////////////////////////////////////////////////////////////////////////

	// Generate [0 ... setSeed(upval)[
	uint32_t randk(){
		return uint32_t(rand() * k);
	} // ////////////////////////////////////////////////////////////////////////////////////

private:

};

