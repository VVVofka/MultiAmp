// adat.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "adat.h"

// TODO: This is an example of a library function
void fnadat()
{
}

std::string adat::CfgMaskA::s() const{
	std::string ret(16, '0');
	_ASSERT(ret.size() == v.size());
	for(size_t j = 0; j < 16; j++)
		if(v[j] != 0)
			ret[j] = '1';
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////////////
void adat::CfgMaskA::set(const char* s){
	for(size_t j = 0; j < 16; j++)
		v[j] = s[j] == '0' ? 0 : 1;
} // //////////////////////////////////////////////////////////////////////////////////////////
bool adat::maska::load(CfgMaskA& mask_a, const char* f_name){
	return false;
} // //////////////////////////////////////////////////////////////////////////////////////////
bool adat::maska::save(const CfgMaskA& mask_a, const char* f_name){
	return false;
} // //////////////////////////////////////////////////////////////////////////////////////////

