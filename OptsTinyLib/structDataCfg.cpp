#include "structDataCfg.h"
#include <algorithm>	// count_if
//#include <regex>

float structDataCfg::fsigma(){
	float flt;
	sscanf_s(sigma.c_str(), "%f", &flt);
	return flt;
} // //////////////////////////////////////////////////////////////////////////////////////
size_t structDataCfg::fill_v(const std::string& s){
	size_t size_inp_str = s.length();
	auto cntSpace = std::count_if(s.begin(), s.end(), [](const char i) { return i == ' '; });
	v.clear();
	v.reserve(cntSpace + 1);
	bool isnum = false;
	size_t bufi = 0;
	for(size_t j = 0; j < size_inp_str; j++){
		char ch = s[j];
		if(ch == ' '){
			if(isnum){
				add2v(bufi);
				bufi = 0;
				isnum = false;
			}
		} else{
			const int ich = ch - '0';
			if(ich >= 0 && ich <= 9){
				bufi = bufi * 10 + ich;
				isnum = true;
			}
		}
	}
	if(isnum)
		add2v(bufi);
	return v.size();
} // //////////////////////////////////////////////////////////////////////////////////////
//size_t structDataCfg::fill_v_bak(const std::string& s){
//	std::regex regex{R"([\s]+)"}; // split on space
//	std::sregex_token_iterator it{s.begin(), s.end(), regex, -1};
//	std::vector<std::string> words{it, {}};
//	size_t newsize = words.size();
//	v.resize(words.size());
//	for(size_t j = 0; j < newsize; j++)
//		v[j] = size_t(_atoi64(words[j].c_str()));
//	return newsize;
//} // //////////////////////////////////////////////////////////////////////////////////////
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
void structDataCfg::add2v(const size_t bufi){
	for(size_t j = 0; j < v.size(); j++)
		if(v[j] == bufi) return;	// not add duplicate
	v.push_back(bufi);
} // ///////////////////////////////////////////////////////////////////////////////////
