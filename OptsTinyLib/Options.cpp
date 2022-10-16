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
	//node = NULL;
	//for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
	//	XMLElement* ele = curnode->ToElement();
	//	std::string name(ele->Name());
	//	if(name == XMLName){
	//		XMLNode* datacfg_node = datacfg.load(curnode);
	//		if(datacfg_node != NULL){
	//			node = curnode;
	//			break;
	//		}
	//	}
	//}
	//return node;
	return NULL;
} // ///////////////////////////////////////////////////////////

const char* Options::get_maskA() const{
	return masks.get_maskA();
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_maskA(XMLDocument* doc, const char* s){
	//XMLNode* curnode = setNode(doc);
	//return masks.set_maskA(s);
	return NULL;
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

const char* Options::get_maskF() const{
	return masks.get_maskF();
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_maskF(XMLDocument* doc, const char* s){
	//XMLNode* curnode = setNode(doc);
	//return masks.set_maskF(s);
	return NULL;
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structLaysCfg Options::get_laysCfg() const{
	return lays.cfg;
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_laysCfg(XMLDocument* doc, const structLaysCfg& lays_cfg){
	//XMLNode* curnode = setNode(doc);
	//return lays.set(curnode, lays_cfg);
	return NULL;
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

structDataCfg Options::get_dataCfg() const{
	//return datacfg.cfg;
	return structDataCfg();
} // ////////////////////////////////////////////////////////////////
XMLNode* Options::set_dataCfg(XMLDocument* doc, const structDataCfg& data_cfg){
	//XMLNode* curnode = setNode(doc);
	//return datacfg.set(curnode, data_cfg);
	return NULL;
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Options::clear_dataCfg(XMLDocument* doc){
	//XMLNode* curnode = setNode(doc);
	//datacfg.clear(curnode);
} // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

