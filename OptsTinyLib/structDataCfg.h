#pragma once
#include <vector>
#include <string>
class structDataCfg{
public:
	std::vector<size_t> v;
	char sigma[32];
	unsigned seed;

	float fsigma();
	void setSigma(const char* s);
	size_t fill_v(const std::string& s);
	std::string get_s() const;
};

