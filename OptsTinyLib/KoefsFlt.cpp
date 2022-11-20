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
	double kNormXold = 1. / (vdold.size() - 1);
	size_t xoldStart = 0, xoldStop = 1;
	double normXold0 = 0, normXold1 = 1;
	for(size_t xnew = 0; xnew < new_size; xnew++){
		double normXnew = xnew * kNormXnew;	// [0...1]
		for(size_t xold0 = xoldStart; xold0 < vdold.size(); xold0++){
			normXold0 = xold0 * kNormXold;
			if(normXold0 == normXnew){
				xoldStart = xold0;
				if(xoldStart > 0)
					normXold0 = --xoldStart * kNormXold;
				break;
			}
			if(normXold0 > normXnew){
				xoldStart = xold0;
				if(xoldStart > 0)
					normXold0 = --xoldStart * kNormXold;
				break;
			}
		}
		for(size_t xold1 = xoldStop; xold1 < vdold.size(); xold1++){
			normXold1 = xold1 * kNormXold;
			if(normXold1 >= normXnew){
				xoldStop = xold1;
				break;
			}
		}
		double kx = (normXnew - normXold0) / (normXold1 - normXold0);
		vd[xnew] = vdold[xoldStart] + kx * (vdold[xoldStop] - vdold[xoldStart]);
	}
	double maxplusold = 0, maxminusold = 0;
	for(size_t j = 0; j < vdold.size(); j++){
		if(vdold[j] < 0){
			if(maxminusold > -vdold[j])
				maxminusold = -vdold[j];
		} else{
			if(maxplusold > vdold[j])
				maxplusold = vdold[j];
		}
	}

	double maxplusnew = 0, maxminusnew = 0;
	for(size_t j = 0; j < vd.size(); j++){
		if(vd[j] < 0){
			if(maxminusnew < -vd[j])
				maxminusnew = -vd[j];
		} else{
			if(maxplusnew < vd[j])
				maxplusnew = vd[j];
		}
	}

	double kminus = maxminusnew == 0 ? 1 : maxminusold / maxminusnew;
	double kplus = maxplusnew == 0 ? 1 : maxplusold / maxplusnew;

	for(size_t j = 0; j < vd.size(); j++){
		if(vd[j] < 0)
			vd[j] *= kminus;
		else
			vd[j] *= kplus;
	}
	//if(vd.size() > vdold.size())
	//	vdold = vd;
} // //////////////////////////////////////////////////////////////////////////////////

