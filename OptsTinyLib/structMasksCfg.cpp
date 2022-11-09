#include "structMasksCfg.h"

void structMasksCfg::seta(const std::string& s){
	_ASSERTE(s.size() == va.size());
	for(size_t j = 0; j < va.size(); j++)
		va[j] = (s[j] == '0') ? 0 : 1;
} // ///////////////////////////////////////////////////////////////////////////////////

void structMasksCfg::setf(const std::string& s){
	_ASSERTE(s.size() == vf.size());
	for(size_t j = 0; j < vf.size(); j++)
		vf[j] = char2float_2(s[j]);
} // ///////////////////////////////////////////////////////////////////////////////////
float_2 structMasksCfg::char2float_2(const char ch){
	const float d = 0.7071067811865475f;
	switch(ch){
	case '0':
		return float_2(0, 0);
	case '1':
		return float_2(0, 1.f);
	case '2':
		return float_2(d, d);
	case '3':
		return float_2(1.f, 0);
	case '4':
		return float_2(d, -d);
	case '5':
		return float_2(0, -1.f);
	case '6':
		return float_2(-d, -d);
	case '7':
		return float_2(-1.f, 0);
	case '8':
		return float_2(-d, d);
	default:
		_ASSERTE(FALSE);
	}
	return float_2();
} // ///////////////////////////////////////////////////////////////////////////////////
