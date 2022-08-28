#include "InPort.h"
#include "Session.h"
std::string getMaskA(const char* fname){
    Session ses;
    ses.load(fname);
    auto ret = ses.get_maskA();
    return std::string(ret);
} // //////////////////////////////////////////////////////////////////////////
void setMaskA(const char* fname, const char* s){
    Session ses;
    ses.load(fname);
    auto ret = ses.set_maskA(s);
    ses.save(fname);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

std::string getMaskF(const char* fname){
    Session ses;
    ses.load(fname);
    auto ret = ses.get_maskF();
    return std::string(ret);
} // //////////////////////////////////////////////////////////////////////////
void setMaskF(const char* fname, const char* s){
    Session ses;
    ses.load(fname);
    auto ret = ses.set_maskF(s);
    ses.save(fname);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structLaysCfg getLaysCfg(const char* fname){
    Session ses;
    ses.load(fname);
    auto ret = ses.get_LaysCfg();
    return ret;
} // //////////////////////////////////////////////////////////////////////////
void setLaysCfg(const char* fname, const structLaysCfg& lays_cfg){
    Session ses;
    ses.load(fname);
    auto ret = ses.set_LaysCfg(lays_cfg);
    ses.save(fname);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
