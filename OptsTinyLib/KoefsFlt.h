#pragma once
#include <vector>
#include <string>
using namespace std;

class KoefsFlt{
public:
	size_t size;
	vector<float> v;

	size_t create(const vector<float>& v_in);
	//size_t create(const char* s_in);
	//void resize(size_t new_size);
	string sall(const int digits = 2, const char separate = ' ') const;
	vector<string> vs(int digits = 2);

private:
	vector<double> vd;
	vector<double> vdmax;
}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

