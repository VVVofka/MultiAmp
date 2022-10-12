#pragma once
#include <vector>
#include <string>
using namespace std;
class structDataCfg{
public:
	vector<size_t> v;
	string sigma;
	string seed;

	float fsigma();
	size_t fill_v(const string& s);
	size_t fill_v_bak(const string& s);
	string get_s() const;
};

