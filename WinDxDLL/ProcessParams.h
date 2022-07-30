#pragma once
#include <vector>
#include "ProcessParam.h"

class ProcessParams{
public:
	std::vector<ProcessParam> v;
	ProcessParams(){};
	ProcessParams(const int cnt){ v.resize(cnt); }
	ProcessParams(const size_t cnt){ v.resize(cnt); }

	void setKF(const std::vector<float> v_in);
	void setLevelTurbul(const std::vector<float> v_in);
	void setLevelTurbul(const float val_in);
	void setKLaminar(const float val_in);
	void setKTurbul(const float val_in);

};

