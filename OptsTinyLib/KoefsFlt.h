#pragma once
#include <vector>
#include <string>
#include <utility>	// pair
using namespace std;

class KoefsFlt{
public:
	size_t size()const{ return vd.size(); };
	vector<float> v() const;

	size_t create(const vector<float>& v_in);
	void resize(const size_t new_size);
	string sall(const int digits = 2, const char separate = ' ') const;
	vector<string> vs(const int digits = 2) const;
	double& operator[](size_t idx) { return vd[idx]; }
	double operator[](size_t idx) const { return vd[idx]; }
private:
	vector<double> vd;
	static size_t find_dn(const vector<double>& v, const double x);
	static size_t find_up(const vector<double>& v, const double x);
	static pair<double, double> getMinMax(const vector<double>& v);
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

