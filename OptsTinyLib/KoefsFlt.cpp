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
	//vdold = vd;
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
	auto vdold = vd;
	vd.resize(new_size);
	double kNormXnew = 1. / (new_size - 1);

	vector<double> vNormXOld(vdold.size());
	for(size_t j = 0; j < vNormXOld.size(); j++)
		vNormXOld[j] = double(j) / double(vdold.size() - 1);

	for(size_t xnew = 0; xnew < new_size; xnew++){
		double normXnew = xnew * kNormXnew;	// [0...1]
		size_t idxXoldDn = find_dn(vNormXOld, normXnew);
		size_t idxXoldUp = find_up(vNormXOld, normXnew);
		double kx = (normXnew - vNormXOld[idxXoldDn]) / (vNormXOld[idxXoldUp] - vNormXOld[idxXoldDn]);
		vd[xnew] = vdold[idxXoldDn] + kx * (vdold[idxXoldUp] - vdold[idxXoldDn]);
	}
	pair<double, double> minmaxold = getMinMax(vdold);
	pair<double, double> minmaxnew = getMinMax(vd);
	double kdn = minmaxnew.first == 0 ? 1.0 : minmaxold.first / minmaxnew.first;
	double kup = minmaxnew.second == 0 ? 1.0 : minmaxold.second / minmaxnew.second;

	for(size_t j = 0; j < vd.size(); j++)
		vd[j] *= ((vd[j] < 0) ? kdn : kup);
} // //////////////////////////////////////////////////////////////////////////////////
size_t KoefsFlt::find_dn(const vector<double>& v, const double x){
	int j = int(v.size());
	while(--j >= 0)
		if(v[j] < x)
			return v[j] < 0.0 ? 0 : size_t(j);
	return 0;
} // /////////////////////////////////////////////////////////////////////////////////
size_t KoefsFlt::find_up(const vector<double>& v, const double x){
	int j = -1;
	int last = v.size() - 1;
	while(++j < last)
		if(v[j] > x)
			return size_t(v[j] > 1.0 ? last : j);
	return size_t(last);
} // //////////////////////////////////////////////////////////////////////////////////
pair<double, double> KoefsFlt::getMinMax(const vector<double>& v){
	double maxplus = 0, maxminus = 0;
	for(size_t j = 0; j < v.size(); j++){
		if(v[j] < 0){
			if(maxminus < -v[j])
				maxminus = -v[j];
		} else{
			if(maxplus < v[j])
				maxplus = v[j];
		}
	}
	return make_pair(maxminus, maxplus);
} // //////////////////////////////////////////////////////////////////////////////////

