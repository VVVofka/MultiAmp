#include "InPort.h"
#include "myXML.h"
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
	ret.topX = xml.getSizetAttribute("topX", 1);
	ret.topY = xml.getSizetAttribute("topY", 1);
	ret.digits = xml.getSizetAttribute("digits", 2);

	xml.setOrCreateNode("kF");
	std::string s = xml.getText();
	ret.vkf = myconv::strToVInt(s);
	
	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setLaysCfg(const char* f_name, const structLaysCfg& lays_cfg){
	MyXML xml(f_name, "Options;LaysCfg");
	xml.setAttribute("topX", lays_cfg.topX);
	xml.setAttribute("topY", lays_cfg.topY);
	xml.setAttribute("digits", lays_cfg.digits);

	xml.setOrCreateNode("kF");
	std::string s = myconv::vIntToStr(lays_cfg.vkf);
	xml.setText(s);
	
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structDataCfg getDataCfg(const char* f_name){
	MyXML xml(f_name, "DataCfg");
	structDataCfg ret;
	ret.seed = xml.getAttribute("seed", "123456");
	ret.sigma = xml.getAttribute("sigma", "0.2");
	ret.v = myconv::strToVSizet(xml.getText());
	//Session ses;
	//ses.loadDataCgf(fname);
	//auto ret = ses.get_DataCfg();
	//return ret;
	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setDataCfg(const char* f_name, const structDataCfg& data_cfg){
	MyXML xml(f_name, "DataCfg");
	xml.setAttribute("seed", data_cfg.seed.c_str());
	xml.setAttribute("sigma", data_cfg.sigma.c_str());
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
	ret.curIteration = xml.getSizetAttribute("curIteration", 0);
	ret.curRndSeed = xml.getU32Attribute("curRndSeed", 1234567);
	ret.dtCreate = xml.getTimetAttribute("dtCreate", 0);
	ret.dtLastStop = xml.getTimetAttribute("dtLastStop", 0);

	xml.setOrCreateNode("sComments");
	ret.sComments = xml.getText("");

	return ret;
} // //////////////////////////////////////////////////////////////////////////
void setMiscCfg(const char* f_name, const structMiscCfg& lays_cfg){
	MyXML xml(f_name, "Misc");
	xml.setAttribute("curIteration", lays_cfg.curIteration);
	xml.setAttribute("curRndSeed", lays_cfg.curRndSeed);
	xml.setAttribute("dtCreate", lays_cfg.dtCreate);
	xml.setAttribute("dtLastStop", lays_cfg.dtLastStop);

	xml.setOrCreateNode("sComments");
	xml.setText(lays_cfg.sComments.c_str());
	
	xml.Save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
