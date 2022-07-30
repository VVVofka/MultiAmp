#include "pch.h"
#include "ProcessParams.h"

void ProcessParams::setKF(const std::vector<float> v_in){
	_ASSERTE(v_in.size() == v.size());
	for(int j = 0; j < (int)v.size(); j++)
		v[j].klayf = v_in[j];
} // /////////////////////////////////////////////////////////////////
void ProcessParams::setLevelTurbul(const std::vector<float> v_in){
	_ASSERTE(v_in.size() == v.size());
	for(int j = 0; j < (int)v.size(); j++)
		v[j].levelTurbul = v_in[j];
} // ////////////////////////////////////////////////////////////////
void ProcessParams::setLevelTurbul(const float val_in){
	for(int j = 0; j < (int)v.size(); j++)
		v[j].levelTurbul = val_in;
} // ////////////////////////////////////////////////////////////////
void ProcessParams::setKLaminar(const float val_in){
	for(int j = 0; j < (int)v.size(); j++)
		v[j].kLaminar = val_in;
} // ////////////////////////////////////////////////////////////////
void ProcessParams::setKTurbul(const float val_in){
	for(int j = 0; j < (int)v.size(); j++)
		v[j].kTurbul = val_in;
} // ////////////////////////////////////////////////////////////////
