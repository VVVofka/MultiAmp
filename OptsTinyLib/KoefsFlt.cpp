#include "KoefsFlt.h"
//#include <algorithm>
size_t KoefsFlt::create(const vector<float>& v_in){
	v = v_in;
	size = v.size();
	vd.resize(size);
	for(size_t j = 0; j < size; j++)
		vd[j] = v[j];
	vdmax = vd;
	return size;
} // //////////////////////////////////////////////////////////////////////////////////
string KoefsFlt::sall(const int digits, const char separate){
	string ret;
	string sformat = "%f." + to_string(digits);
	const char* pformat = sformat.c_str();
	for(size_t j = 0;;){
		char buf[16];
		sprintf_s(buf, 16, pformat, vd[j]);
		ret += buf;
		if(j++ >= size)
			return ret;
		ret += separate;
	}
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////
vector<string> KoefsFlt::vs(int digits){
	vector<string> ret(size);
	string sformat = "%f." + to_string(digits);
	const char* pformat = sformat.c_str();
	for(size_t j = 0; j < size; j++){
		char buf[16];
		sprintf_s(buf, 16, pformat, vd[j]);
		ret[j] = buf;
	}
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////

