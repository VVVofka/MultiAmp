#include "Options.h"
using namespace tinyxml2;

void Options::create(XMLDocument* doc){
	XMLElement* ele_out = doc->NewElement(XMLName);
	XMLNode* node = doc->InsertEndChild(ele_out);
	masks.create(node);
} // ///////////////////////////////////////////////////////////
void Options::load(XMLDocument* doc){
	//lays.load();
	// TODO: ---
	//masks.load(*doc);
} // ///////////////////////////////////////////////////////////
