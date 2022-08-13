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
} // //////////////////////////////////////////////////////////////////////////
