#pragma once
#include <vector>
#include <string>
#include "structCfgBase.h"

class structDataCfg : public structCfgBase{
public:
	std::vector<size_t> v;
	std::string sigma;
	std::string seed;

	float fsigma();
	size_t fill_v(const std::string& s);
	size_t fill_v_bak(const std::string& s);
	std::string get_s() const;

	bool isEqual(const structCfgBase* other);
};

