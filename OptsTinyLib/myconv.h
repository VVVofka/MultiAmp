#pragma once
#include <string>
#include <vector>
namespace myconv{
	size_t strToSize_t(const char* s);
	std::string size_tToStr(size_t val);

	std::vector<int> strToVInt(const std::string& s, const char delimiter = ';');
	std::vector<size_t> strToVSizet(const std::string& s);
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

