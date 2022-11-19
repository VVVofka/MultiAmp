#include "myconv.h"
#include <iomanip>
#include <sstream>

size_t myconv::strToSize_t(const char* s){
#ifndef WIN32
	auto ret = std::stoull(s);
#else
	auto ret = std::stoul(s);
#endif // WIN32
	return size_t(ret);
} // ////////////////////////////////////////////////////////////////////////////////////
//std::string myconv::size_tToStr(size_t val){
//	return std::to_string(val);
//} // ////////////////////////////////////////////////////////////////////////////////////
//std::string myconv::time_tToStr(time_t val){
//	return std::to_string(val);
//} // ////////////////////////////////////////////////////////////////////////////////////

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

std::string myconv::vIntToStr(const std::vector<int>& v, const char delimiter){
	std::string ret;
	size_t size = v.size();
	for(size_t j = 0; j < size; j++){
		ret += std::to_string(v[j]);
		if(j != size - 1)
			ret += delimiter;
	}
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
std::string myconv::vSizetToStr(const std::vector<size_t>& v, const char delimiter){
	std::string ret;
	size_t size = v.size();
	for(size_t j = 0; j < size; j++){
		ret += std::to_string(v[j]);
		if(j != size - 1)
			ret += delimiter;
	}
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
std::string myconv::fltToStr(float pi, int digits){
	std::stringstream stream;
	stream << std::fixed << std::setprecision(digits) << pi;
	std::string ret = stream.str();
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
#include <time.h>
tm myconv::getTMstruct(__time64_t long_time){
	struct tm structtime;
	if(long_time == 0)
		_time64(&long_time);	// Get time as 64-bit integer.
	_localtime64_s(&structtime, &long_time);	// Convert to local time.
	return structtime;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<float> myconv::strToVFloat(const std::string& s, const char delimiter){
	std::vector<float> ret;
	size_t size_inp_str = s.length();
	if(size_inp_str == 0) return ret;
	ret.reserve(size_inp_str / 4);

	std::string bufword;
	int sign = 1;
	//int bufpos = 0;
	//size_t vpos = 0;
	//bool isnum = false;
	enum curState{
		IntegerPart,
		FractionalPart,
		Delimiter,
		Sign,
		Comma
	};
	curState state = curState::Delimiter;
	for(size_t j = 0; j < size_inp_str; j++){
		const char ch = s[j];
		if(ch == delimiter){
			switch(state){
			case IntegerPart:
			case FractionalPart:
			case Comma:
				ret.push_back(sign * atof(bufword.c_str()));
				sign = 1;
				bufword.clear();
				state = curState::Delimiter;
				continue;
			case Delimiter:
			case Sign:
			default:
				continue;
			}
		}
		if(ch >= '0' && ch <= '9'){
			switch(state){
			case IntegerPart:
			case FractionalPart:
				bufword.push_back(ch);
				continue;
			case Delimiter:
			case Sign:
				bufword.push_back(ch);
				state = curState::IntegerPart;
				continue;
			case Comma:
				bufword.push_back(ch);
				state = curState::FractionalPart;
				continue;
			default:
				continue;
			}
		}
		if(ch == '-' || ch == '+'){
			switch(state){
			case IntegerPart:
			case FractionalPart:
			case Comma:
				ret.push_back(sign * atof(bufword.c_str()));
				sign = ch == '-' ? -1 : 1;
				bufword.clear();
				state = curState::Sign;
				continue;
			case Delimiter:
				sign = ch == '-' ? -1 : 1;
				bufword.clear();
				state = curState::Sign;
				continue;
			case Sign:
				if(ch == '-') sign = -sign;
				continue;
			default:
				continue;
			}
		}
		if(ch == '.' || ch == ','){
			switch(state){
			case IntegerPart:
			case Delimiter:
			case Sign:
				bufword.push_back('.');
				state = curState::FractionalPart;
				continue;
			case FractionalPart:
				ret.push_back(sign * atof(bufword.c_str()));
				sign = 1;
				bufword.clear();
				state = curState::Delimiter;
				continue;
			case Comma:
			default:
				continue;
			}
		}
		return ret;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
