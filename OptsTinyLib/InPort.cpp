#include "InPort.h"
#include "myXML.h"
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
std::string getMaskA(const char* f_name){
	MyXML xml(f_name, "Options;Masks;MaskA");
	return xml.getText("0001011101111111");
} // //////////////////////////////////////////////////////////////////////////
void setMaskA(const char* f_name, const char* s){
	MyXML xml(f_name, "Options;Masks;MaskA");
	xml.setText(s);
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

std::string getMaskF(const char* f_name){
	MyXML xml(f_name, "Options;Masks;MaskF");
	std::string defval(256, '0');
	std::string ret = xml.getText(defval.c_str());
	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setMaskF(const char* f_name, const char* s){
	MyXML xml(f_name, "Options;Masks;MaskF");
	xml.setText(s);
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structLaysCfg getLaysCfg(const char* f_name){
	MyXML xml(f_name, "Options;LaysCfg");
	structLaysCfg ret;
	ret.topX = xml.getAttributeT<size_t>("topX", 1);
	ret.topY = xml.getAttributeT<size_t>("topY", 1);
	ret.digits = xml.getAttributeT<size_t>("digits", 2);
	ret.cpuSingle = xml.getAttributeT<size_t>("singleCPU", 0);
	ret.cpuMultiThreaded = xml.getAttributeT<size_t>("multithreadedCPU", 0);

	xml.setOrCreateNode("kF");
	std::string s = xml.getText();
	ret.vkf = myconv::strToVInt(s);
	
	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setLaysCfg(const char* f_name, const structLaysCfg& lays_cfg){
	MyXML xml(f_name, "Options;LaysCfg");
	xml.setAttributeT<size_t>("topX", lays_cfg.topX);
	xml.setAttributeT<size_t>("topY", lays_cfg.topY);
	xml.setAttributeT<size_t>("digits", lays_cfg.digits);
	xml.setAttributeT<size_t>("singleCPU", lays_cfg.cpuSingle);
	xml.setAttributeT<size_t>("multithreadedCPU", lays_cfg.cpuMultiThreaded);

	xml.setOrCreateNode("kF");
	std::string s = myconv::vIntToStr(lays_cfg.vkf);
	xml.setText(s);
	
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structDataCfg getDataCfg(const char* f_name){
	MyXML xml(f_name, "DataCfg");
	structDataCfg ret;
	ret.seed = xml.getAttributeS("seed", "123456");
	ret.sigma = xml.getAttributeS("sigma", "0.2");
	ret.v = myconv::strToVSizet(xml.getText());
	//Session ses;
	//ses.loadDataCgf(fname);
	//auto ret = ses.get_DataCfg();
	//return ret;
	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setDataCfg(const char* f_name, const structDataCfg& data_cfg){
	MyXML xml(f_name, "DataCfg");
	xml.setAttributeS("seed", data_cfg.seed);
	xml.setAttributeS("sigma", data_cfg.sigma);
	std::string s = myconv::vSizetToStr(data_cfg.v);
	xml.setText(s);
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void clearDataCfg(const char* f_name){
	MyXML xml(f_name, "DataCfg");
	xml.setText("");
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structMiscCfg getMiscCfg(const char* f_name){
	MyXML xml(f_name, "Misc");
	structMiscCfg ret;
	ret.curIteration = xml.getAttributeT<uint64_t>("curIteration", 0);
	ret.curRndSeed = xml.getAttributeT<uint32_t>("curRndSeed", 1234567);
	ret.dtCreate = xml.getAttributeT<time_t>("dtCreate", 0);
	ret.dtLastStop = xml.getAttributeT<time_t>("dtLastStop", 0);

	xml.setOrCreateNode("sComments");
	ret.sComments = xml.getText("No comments.");

	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setMiscCfg(const char* f_name, const structMiscCfg& lays_cfg){
	MyXML xml(f_name, "Misc");
	xml.setAttributeT<uint64_t>("curIteration", lays_cfg.curIteration);
	xml.setAttributeT<uint32_t>("curRndSeed", lays_cfg.curRndSeed);
	xml.setAttributeT<time_t>("dtCreate", lays_cfg.dtCreate);
	xml.setAttributeT<time_t>("dtLastStop", lays_cfg.dtLastStop);

	xml.setOrCreateNode("sComments");
	xml.setText(lays_cfg.sComments.c_str());
	
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
