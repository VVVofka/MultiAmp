#include "structDataCfg.h"
#include <regex>

float structDataCfg::fsigma(){
	float flt;
	sscanf_s(sigma.c_str(), "%f", &flt);
	return flt;
} // //////////////////////////////////////////////////////////////////////////////////////
size_t structDataCfg::fill_v(const std::string& s){
	size_t size_inp_str = s.length();
	if(size_inp_str == 0) return 0;

	size_t newsize = 0;
	for(size_t j = 0; j < size_inp_str; j++)
		if(s[j] == ' ')
			newsize++;
	v.resize(++newsize);

	const int BUFWORDLEN = 12;
	char bufword[BUFWORDLEN];
	int bufpos = 0;
	char ch;
	size_t vpos = 0;
	for(size_t j = 0; j < size_inp_str; j++){
		ch = s[j];
		if(ch == ' '){
			if(bufpos != 0){
				bufword[bufpos] = 0;
				bufpos = 0;
				v[vpos++] = size_t(_atoi64(bufword));
			}
		} else if(ch >= '0' && ch <= '9')
			bufword[bufpos++] = ch;
	}
	bufword[bufpos] = 0;
	v[vpos] = size_t(_atoi64(bufword));
	return newsize;
} // //////////////////////////////////////////////////////////////////////////////////////
size_t structDataCfg::fill_v_bak(const std::string& s){
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
bool structDataCfg::isEqual(const structCfgBase* other){
	structDataCfg* p = (structDataCfg*)other;
	if(sigma != p->sigma || seed != p->seed) return false;
	return v != p->v;
} // /////////////////////////////////////////////////////////////////////////////
