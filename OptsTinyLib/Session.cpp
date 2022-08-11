#include "Session.h"
using namespace tinyxml2;

void Session::load(const char* fname){
	XMLError err;
	if(strlen(fname) == 0)
		err = doc.LoadFile("session.xml");
	else
		err = doc.LoadFile(fname);
	doc.SaveFile("session.xml");

} // //////////////////////////////////////////////////////
