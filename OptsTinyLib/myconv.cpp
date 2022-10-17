#include "myconv.h"

size_t myconv::strToSize_t(const char* s){
#ifndef WIN32
	auto ret = std::stoull(s);
#else
	auto ret = std::stoul(s);
#endif // WIN32
	return size_t(ret);
} // ////////////////////////////////////////////////////////////////////////////////////
std::string myconv::size_tToStr(size_t val){
	return std::to_string(val);
} // ////////////////////////////////////////////////////////////////////////////////////

std::vector<int> myconv::strToVInt(const std::string& s, const char delimiter){
	std::vector<int> ret;
	size_t size_inp_str = s.length();
	if(size_inp_str == 0) return ret;
	ret.reserve(size_inp_str / 2);

	const int BUFWORDLEN = 12;
	char bufword[BUFWORDLEN];
	int bufpos = 0;
	char ch;
	size_t vpos = 0;
	bool isnum = false;
	for(size_t j = 0; j < size_inp_str; j++){
		ch = s[j];
		if(ch == delimiter){
			if(bufpos != 0){
				bufword[bufpos] = 0;
				bufpos = 0;
				if(isnum){
					ret.push_back(atoi(bufword));	//	v[vpos++] = size_t(_atoi64(bufword));
					isnum = false;
				}
			}
		} else if(ch >= '0' && ch <= '9'){
			bufword[bufpos++] = ch;
			isnum = true;
		} else if(ch == '-'){
			if(bufpos != 0){
				bufword[bufpos] = 0;
				bufpos = 0;
				if(isnum){
					ret.push_back(atoi(bufword));
					isnum = false;
				}
			}
			bufword[bufpos++] = ch;
		} else if(ch == '+'){
			if(bufpos != 0){
				bufword[bufpos] = 0;
				bufpos = 0;
				if(isnum){
					ret.push_back(atoi(bufword));
					isnum = false;
				}
			}
		}
	}
	if(isnum){
		bufword[bufpos] = 0;
		ret.push_back(atoi(bufword));	//	v[vpos] = size_t(_atoi64(bufword));
	}
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<size_t> myconv::strToVSizet(const std::string& s){
	std::vector<size_t> ret;
	size_t size_inp_str = s.length();
	if(size_inp_str == 0) return ret;
	ret.reserve(size_inp_str / 2);

	const int BUFWORDLEN = 24;
	char bufword[BUFWORDLEN];
	int bufpos = 0;
	char ch;
	size_t vpos = 0;
	bool isnum = false;
	for(size_t j = 0; j < size_inp_str; j++){
		ch = s[j];
		if(ch >= '0' && ch <= '9'){
			bufword[bufpos++] = ch;
			isnum = true;
		} else{
			if(bufpos != 0){
				bufword[bufpos] = 0;
				bufpos = 0;
				if(isnum){
					ret.push_back(strToSize_t(bufword));	//	v[vpos++] = size_t(_atoi64(bufword));
					isnum = false;
				}
			}
		}
	}
	if(isnum){
		bufword[bufpos] = 0;
		ret.push_back(atoi(bufword));	//	v[vpos] = size_t(_atoi64(bufword));
	}
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////


