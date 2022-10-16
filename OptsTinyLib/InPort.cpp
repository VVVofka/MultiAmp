#include "InPort.h"
#include "Session.h"
#include "myXML.h"
#include <array>
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
std::string getMaskA(const char* f_name){
	MyXML xml(f_name, "Options;Masks;MaskA");
	std::string ret = xml.getText("0001011101111111");
	//Session ses;
	//ses.loadMasks(fname);
	//auto ret = ses.get_maskA();
	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setMaskA(const char* f_name, const char* s){
	MyXML xml(f_name, "Options;Masks;MaskA");
	xml.setText(s);
	//Session ses(f_name);
	//auto ret = ses.set_maskA(s);
	//ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

std::string getMaskF(const char* f_name){
	MyXML xml(f_name, "Options;Masks;MaskF");
	std::string defval(256, '0');
	std::string ret = xml.getText(defval.c_str());
	//Session ses;
	//ses.loadMasks(f_name);
	//auto ret = ses.get_maskF();
	//return std::string(ret);
	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setMaskF(const char* f_name, const char* s){
	MyXML xml(f_name, "Options;Masks;MaskF");
	xml.setText(s);
	//Session ses(f_name);
	//auto ret = ses.set_maskF(s);
	//ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structLaysCfg getLaysCfg(const char* f_name){
	/*   Session ses;
	   ses.loadLaysCfg(f_name);
	   auto ret = ses.get_LaysCfg();
	   return ret;*/
	MyXML xml(f_name, "Options;LaysCfg");
	structLaysCfg ret;
	ret.topX = size_t(xml.getU64Attribute("topX", 1));
	ret.topY = size_t(xml.getU64Attribute("topY", 1));
	//ret.
	return structLaysCfg();
} // //////////////////////////////////////////////////////////////////////////
void setLaysCfg(const char* f_name, const structLaysCfg& lays_cfg){
	//Session ses(f_name);
	//auto ret = ses.set_LaysCfg(lays_cfg);
	//ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structDataCfg getDataCfg(const char* fname){
	//Session ses;
	//ses.loadDataCgf(fname);
	//auto ret = ses.get_DataCfg();
	//return ret;
	return structDataCfg();
} // //////////////////////////////////////////////////////////////////////////
void setDataCfg(const char* f_name, const structDataCfg& data_cfg){
	//Session ses(f_name);
	//auto ret = ses.set_DataCfg(data_cfg);
	//ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void clearDataCfg(const char* f_name){
	//Session ses(f_name);
	//ses.clear_DataCfg();
	//ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
