#include "Options.h"
using namespace tinyxml2;

XMLNode* Options::create(XMLDocument* doc){
	XMLElement* ele_out = doc->NewElement(XMLName);
	node = doc->InsertEndChild(ele_out);
	XMLNode* masks_node = masks.create(node);
	XMLNode* layscfg_node = lays.create(node);
	XMLNode* datacfg_node = datacfg.create(node);
	if(masks_node == NULL || layscfg_node == NULL || datacfg_node == NULL)
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
			XMLNode* datacfg_node = datacfg.load(curnode);
			if(masks_node != NULL && layscfg_node != NULL && datacfg_node != NULL){
				node = curnode;
				break;
			}
		}
	}
	return node;
} // ///////////////////////////////////////////////////////////
XMLNode* Options::loadMasks(XMLDocument* doc){
	node = NULL;
	for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			XMLNode* maskscfg_node = masks.load(curnode);
			if(maskscfg_node != NULL){
				node = curnode;
				break;
			}
		}
	}
	return node;
} // ///////////////////////////////////////////////////////////
XMLNode* Options::loadLaysCfg(XMLDocument* doc){
	node = NULL;
	for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			XMLNode* layscfg_node = lays.load(curnode);
			if(layscfg_node != NULL){
				node = curnode;
				break;
			}
		}
	}
	return node;
} // ///////////////////////////////////////////////////////////
XMLNode* Options::loadDataCfg(XMLDocument* doc){
	node = NULL;
	for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName){
			XMLNode* datacfg_node = datacfg.load(curnode);
			if(datacfg_node != NULL){
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
XMLNode* Options::set_maskA(XMLDocument* doc, const char* s){
	XMLNode* curnode = getNode(doc);
	return masks.set_maskA(s);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

const char* Options::get_maskF() const{
	return masks.get_maskF();
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_maskF(XMLDocument* doc, const char* s){
	XMLNode* curnode = getNode(doc);
	return masks.set_maskF(s);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structLaysCfg Options::get_laysCfg() const{
	return lays.cfg;
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_laysCfg(XMLDocument* doc, const structLaysCfg& lays_cfg){
	XMLNode* curnode = getNode(doc);
	return lays.set(curnode, lays_cfg);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structDataCfg Options::get_dataCfg() const{
	return datacfg.cfg;
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_dataCfg(XMLDocument* doc, const structDataCfg& data_cfg){
	XMLNode* curnode = getNode(doc);
	return datacfg.set(curnode, data_cfg);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Options::clear_dataCfg(XMLDocument* doc){
	XMLNode* curnode = getNode(doc);
	datacfg.clear(curnode);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

XMLNode* Options::getNode(XMLDocument* doc){
	for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		XMLElement* ele = curnode->ToElement();
		std::string name(ele->Name());
		if(name == XMLName)
			return curnode;
	}
	return NULL;
} // ////////////////////////////////////////////////////////////////
