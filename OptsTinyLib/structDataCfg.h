#pragma once
#include <vector>
#include <string>

class structDataCfg{
public:
	std::vector<size_t> v;
	std::string sigma;
	std::string seed;

	float fsigma();
	size_t fill_v(const std::string& s);
	//size_t fill_v_bak(const std::string& s);
	std::string get_s() const;

private:
	void add2v(size_t& vpos, const char* bufword);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

