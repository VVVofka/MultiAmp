#include "KoefsFlt.h"
vector<float> KoefsFlt::v() const{
	vector<float> ret(vd.size());
	for(size_t j = 0; j < vd.size(); j++)
		ret[j] = float(vd[j]);
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////
size_t KoefsFlt::create(const vector<float>& v_in){
	vd.resize(v_in.size());
	for(size_t j = 0; j < vd.size(); j++)
		vd[j] = v_in[j];
	vdmax = vd;
	return vd.size();
} // //////////////////////////////////////////////////////////////////////////////////
string KoefsFlt::sall(const int digits, const char separate) const{
	string ret;
	string sformat = "%." + to_string(digits) + "f";
	const char* pformat = sformat.c_str();
	for(size_t j = 0;;){
		char buf[16];
		sprintf_s(buf, 16, pformat, vd[j]);
		ret += buf;
		if(++j >= vd.size())
			return ret;
		ret += separate;
	}
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////
vector<string> KoefsFlt::vs(const int digits) const{
	vector<string> ret(vd.size());
	string sformat = "%f." + to_string(digits);
	const char* pformat = sformat.c_str();
	for(size_t j = 0; j < vd.size(); j++){
		char buf[16];
		sprintf_s(buf, 16, pformat, vd[j]);
		ret[j] = buf;
	}
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////
void KoefsFlt::resize(const size_t new_size){
	_ASSERTE(new_size > 1);
	vector<double> tmp = vd;
	vd.resize(new_size);
	double kNormXnew = 1. / (new_size - 1);
	_ASSERTE(vdmax.size() > 1);
	double kNormXold = 1. / (vdmax.size() - 1);
	size_t xoldStart = 0, xoldStop = 1;
	double normXold0 = 0, normXold1 = 1;
	for(size_t xnew = 0; xnew < new_size; xnew++){
		double normXnew = xnew * kNormXnew;	// [0...1]
		for(size_t xold0 = xoldStart; xold0 < vdmax.size(); xold0++){
			normXold0 = xold0 * kNormXold;
			if(normXold0 <= normXnew){
				xoldStart = xold0;
				break;
			}
		}
		for(size_t xold1 = xoldStop; xold1 < vdmax.size(); xold1++){
			normXold1 = xold1 * kNormXold;
			if(normXold1 >= normXnew){
				xoldStop = xold1;
				break;
			}
		}
		double kx = (normXnew - normXold0) / (normXold1 - normXold0);
		vd[xnew] = vdmax[xoldStart] + kx * (vdmax[xoldStop] - vdmax[xoldStart]);
	}
	if(vd.size() > vdmax.size())
		vdmax = vd;
} // //////////////////////////////////////////////////////////////////////////////////

