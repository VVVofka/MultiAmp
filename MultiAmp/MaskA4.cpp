#include "pch.h"
#include "MaskA4.h"

bool options::maska::MaskA4::check(){
	for(int j = 0; j < size; j++){
		if(v[j] == 0 || v[j] == 1)
			continue;
		return false;
	}
	return true;
} // //////////////////////////////////////////////////////////////////
int* options::maska::MaskA4::set(unsigned u){
	for(int j = 0; j < size; j++)
		v[j] = ((u >> j) & 1) == 0 ? 0 : 1;
	return v;
} // //////////////////////////////////////////////////////////////////
int* options::maska::MaskA4::set(const char* ptr_ch){
	for(int j = 0; j < size; j++)
		v[j] = (ptr_ch[j] == '0') ? 0 : 1;
	return v;
} // /////////////////////////////////////////////////////////////////////////////////
int* options::maska::MaskA4::setdef(){
	return set(s_def.c_str());
} // /////////////////////////////////////////////////////////////////////
unsigned options::maska::MaskA4::getu(){
	unsigned ret = 0;
	for(int j = 0; j < size; j++)
		ret |= v[j] << j;
	return ret;
} // //////////////////////////////////////////////////////////////////////
std::string options::maska::MaskA4::gets(){
	char ret[size];
	for(int j = 0; j < size; j++)
		ret[j] = v[j] == 0 ? '0' : '1';
	return std::string(ret, size);
} // ///////////////////////////////////////////////////////////////////////////////
