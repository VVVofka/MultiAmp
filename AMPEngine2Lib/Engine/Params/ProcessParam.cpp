#include "ProcessParam.h"

std::string ProcessParam::sDump() const{
	char buf[256];
	sprintf_s(buf, "klayf=%f levelTurbul=%f kLaminar=%f kTurbul=%f",
		klayf, levelTurbul, kLaminar, kTurbul);
	return std::string(buf);
} // /////////////////////////////////////////////////////////////////////////
