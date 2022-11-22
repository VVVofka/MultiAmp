#pragma once
#include <cstdint>
class LehmerRng{
public:
	const unsigned int UBASE = 0xfffffffb;
	const double FBASE = double(0xfffffffb);

private:
	double k = 1;
	uint32_t seed;

public:
	LehmerRng(uint32_t init_seed = 0){
		if(init_seed != 0)
			seed = init_seed;
		else
			do{
				seed = (uint32_t)(time(0) % UBASE);
			} while(seed == 0);
	} // //////////////////////////////////////////////////////////////////////////////////
	uint32_t getSeed(){ return seed; }
	// < 0xfffffffb for 
	// Generate [0 ... setSeed(max)[
	void setUpper(uint32_t max){
		k = max / FBASE;
	} // ////////////////////////////////////////////////////////////////////////////////////

	// newval < UBASE(0xfffffffb)
	void setSeed(uint32_t newval){
		seed = newval % UBASE;
	} // ////////////////////////////////////////////////////////////////////////////////////

	// Generate ]0 ... 0xfffffffb(UBASE)[
	uint32_t rand(){
		return seed = (uint64_t)seed * 279470273u % UBASE;
	} // ////////////////////////////////////////////////////////////////////////////////////

	// Generate [0 ... max[
	uint32_t rand(uint32_t max){
		double koef = max / FBASE;
		return uint32_t(rand() * koef);
	} // ////////////////////////////////////////////////////////////////////////////////////

	// Generate [0 ... setUpper(upval)[
	uint32_t randk(){
		return uint32_t(rand() * k);
	} // ////////////////////////////////////////////////////////////////////////////////////

private:

};

