#pragma once
#include <vector>
#include <string>
class structDataCfg{
public:
	std::vector<size_t> v;
	size_t fill_v(const std::string& s);
	std::string get_s();
};

