#include "structDataCfg.h"
#include <regex>

float structDataCfg::fsigma(){
	float flt;
	sscanf_s(sigma, "%f", &flt);
	return flt;
} // //////////////////////////////////////////////////////////////////////////////////////
void structDataCfg::setSigma(const char* s){
	strcpy_s(sigma, s);
} // //////////////////////////////////////////////////////////////////////////////////////
size_t structDataCfg::fill_v(const std::string& s){
	std::regex regex{R"([\s]+)"}; // split on space
	std::sregex_token_iterator it{s.begin(), s.end(), regex, -1};
	std::vector<std::string> words{it, {}};
	size_t newsize = words.size();
	v.resize(words.size());
	for(size_t j = 0; j < newsize; j++)
		v[j] = size_t(_atoi64(words[j].c_str()));
	return newsize;
} // //////////////////////////////////////////////////////////////////////////////////////
std::string structDataCfg::get_s() const{
	std::string sret;
	size_t size = v.size();
	if(size){
		for(size_t j = 0; j < size - 1; j++)
			sret += std::to_string(v[j]) + ' ';
		sret += std::to_string(v[size - 1]);
	}
	return sret;
} // ///////////////////////////////////////////////////////////////////////////////////
//void tst(){
//	std::string s{"String to   split here, and here, and here,..."};
//	std::regex regex{R"([\s,]+)"}; // split on space and comma
//	std::sregex_token_iterator it{s.begin(), s.end(), regex, -1};
//	std::vector<std::string> words{it, {}};
//} // /////////////////////////////////////////////////////////////////////////////
