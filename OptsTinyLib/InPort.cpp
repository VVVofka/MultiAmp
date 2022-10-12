#include "InPort.h"
#include "Session.h"

 // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
std::string getMaskA(const char* fname){
    Session ses;
    ses.loadMasks(fname);
    auto ret = ses.get_maskA();
    return std::string(ret);
} // //////////////////////////////////////////////////////////////////////////
void setMaskA(const char* f_name, const char* s){
    Session ses(f_name);
    auto ret = ses.set_maskA(s);
    ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

std::string getMaskF(const char* fname){
    Session ses;
    ses.loadMasks(fname);
    auto ret = ses.get_maskF();
    return std::string(ret);
} // //////////////////////////////////////////////////////////////////////////
void setMaskF(const char* f_name, const char* s){
    Session ses(f_name);
    auto ret = ses.set_maskF(s);
    ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structLaysCfg getLaysCfg(const char* fname){
    Session ses;
    ses.loadLaysCfg(fname);
    auto ret = ses.get_LaysCfg();
    return ret;
} // //////////////////////////////////////////////////////////////////////////
void setLaysCfg(const char* f_name, const structLaysCfg& lays_cfg){
    Session ses(f_name);
    auto ret = ses.set_LaysCfg(lays_cfg);
    ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structDataCfg getDataCfg(const char* fname){
    Session ses;
    ses.loadDataCgf(fname);
    auto ret = ses.get_DataCfg();
    return ret;
} // //////////////////////////////////////////////////////////////////////////
void setDataCfg(const char* f_name, const structDataCfg& data_cfg){
    Session ses(f_name);
    auto ret = ses.set_DataCfg(data_cfg);
    ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void clearDataCfg(const char* f_name){
    Session ses(f_name);
    ses.clear_DataCfg();
    ses.save(f_name);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
