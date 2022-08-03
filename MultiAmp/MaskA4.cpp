#include "pch.h"
#include "MaskA4.h"
//namespace maska{

	bool MaskA4::check(){
		for(int j = 0; j < size; j++){
			if(v[j] == 0 || v[j] == 1)
				continue;
			return false;
		}
		return true;
	} // //////////////////////////////////////////////////////////////////
	int* MaskA4::set(unsigned u){
		for(int j = 0; j < size; j++)
			v[j] = ((u >> j) & 1) == 0 ? 0 : 1;
		return v;
	} // //////////////////////////////////////////////////////////////////
	int* MaskA4::set(const char* ptr_ch){
		for(int j = 0; j < size; j++)
			v[j] = (ptr_ch[j] == '0') ? 0 : 1;
		return v;
	} // /////////////////////////////////////////////////////////////////////////////////
	int* MaskA4::setdef(){
		return set(s_def.c_str());
	} // /////////////////////////////////////////////////////////////////////
	unsigned MaskA4::getu(){
		unsigned ret = 0;
		for(int j = 0; j < size; j++)
			ret |= v[j] << j;
		return ret;
	} // //////////////////////////////////////////////////////////////////////
	std::string MaskA4::gets(){
		char ret[size];
		for(int j = 0; j < size; j++)
			ret[j] = v[j] == 0 ? '0' : '1';
		return std::string(ret, size);
	} // ///////////////////////////////////////////////////////////////////////////////
//}
