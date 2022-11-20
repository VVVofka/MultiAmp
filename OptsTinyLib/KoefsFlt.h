#pragma once
#include <vector>
#include <string>
using namespace std;

class KoefsFlt{
public:
	size_t size()const{ return vd.size(); };
	vector<float> v() const;

	size_t create(const vector<float>& v_in);
	void resize(const size_t new_size);
	string sall(const int digits = 2, const char separate = ' ') const;
	vector<string> vs(const int digits = 2) const;

private:
	vector<double> vd;
	vector<double> vdmax;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

