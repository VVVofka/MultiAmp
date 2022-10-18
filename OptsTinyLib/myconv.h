#pragma once
#include <string>
#include <vector>
namespace myconv{
	size_t strToSize_t(const char* s);
	std::string size_tToStr(size_t val);

	std::vector<int> strToVInt(const std::string& s, const char delimiter = ' ');
	std::vector<size_t> strToVSizet(const std::string& s);

	std::string vIntToStr(const std::vector<int>& v, const char delimiter = ' ');
	std::string vSizetToStr(const std::vector<size_t>& v, const char delimiter = ' ');

	std::string fltToStr(float val, int digits = 2);

	tm getTMstruct(__time64_t long_time = 0);


} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

