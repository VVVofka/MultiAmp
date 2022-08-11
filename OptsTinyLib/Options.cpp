#include "Options.h"
using namespace tinyxml2;

void Options::create(XMLDocument& doc){
	//lays.create();
	masks.create(doc);
} // ///////////////////////////////////////////////////////////
void Options::load(XMLDocument& doc){
	//lays.load();
	masks.load(doc);
} // ///////////////////////////////////////////////////////////
