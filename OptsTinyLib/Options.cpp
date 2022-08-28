#include "Options.h"
using namespace tinyxml2;

XMLNode* Options::create(XMLDocument* doc){
	XMLElement* ele_out = doc->NewElement(XMLName);
	node = doc->InsertEndChild(ele_out);
	XMLNode* masks_node = masks.create(node);
	XMLNode* layscfg_node = lays.create(node);
	if(masks_node == NULL || layscfg_node == NULL)
		return NULL;
	return node;
} // ///////////////////////////////////////////////////////////
XMLNode* Options::load(XMLDocument* doc){
	node = NULL;
	for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			XMLNode* masks_node = masks.load(curnode);
			XMLNode* layscfg_node = lays.load(curnode);
			if(masks_node != NULL && layscfg_node != NULL){
				node = curnode;
				break;
			}
		}
	}
	return node;
} // ///////////////////////////////////////////////////////////
const char* Options::get_maskA() const{
	return masks.get_maskA();
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_maskA(const char* s){
	return masks.set_maskA(s);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
const char* Options::get_maskF() const{
	return masks.get_maskF();
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_maskF(const char* s){
	return masks.set_maskF(s);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
structLaysCfg Options::get_laysCfg() const{
	return lays.cfg;
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_laysCfg(const structLaysCfg& lays_cfg){
	return lays.set(node, lays_cfg);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
