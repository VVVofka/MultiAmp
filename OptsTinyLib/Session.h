#pragma once
#include "Data.h"
#include "Options.h"
#include "tinyxml2.h"
#include "structLaysCfg.h"
#include "structDataCfg.h"

using namespace tinyxml2;

class Session{
public:
	Data data;
	Options options;

	void create(const char* f_name = "");
	void load(const char* f_name = "");
	void loadMasks(const char* f_name = "");
	void loadLaysCfg(const char* f_name = "");
	void loadDataCgf(const char* f_name = "");
	void save(const char* f_name = "");
	std::string fname;
	void tstcrt();

	XMLError loadDoc(const char* f_name);

	const char* get_maskA() const;
	XMLNode* set_maskA(const char* s);

	const char* get_maskF() const;
	XMLNode* set_maskF(const char* s);

	structLaysCfg get_LaysCfg() const;
	XMLNode* set_LaysCfg(const structLaysCfg& lays_cfg);

	structDataCfg get_DataCfg() const;
	XMLNode* set_DataCfg(const structDataCfg& data_cfg);
	void saveDataCfg(const structDataCfg& data_cfg);

protected:
	XMLDocument doc;
};

