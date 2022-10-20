#include "myXML.h"
#include <string>
MyXML::MyXML(){
	doc = new tinyxml2::XMLDocument();
	node = NULL;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::~MyXML(){
	if(doc != NULL)
		delete doc;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(const char* f_name){
	setDoc(f_name);
	node = NULL;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(tinyxml2::XMLDocument* in_doc){
	setDoc(in_doc);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(tinyxml2::XMLNode* in_node){
	setDoc(in_node->GetDocument());
	node = in_node;
}  // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(tinyxml2::XMLDocument* in_doc, const char* path_node){
	setOrCreateNode(in_doc, path_node);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(const char* f_name, const char* path_node){
	setOrCreateNode(f_name, path_node);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////

const char* MyXML::getNodeName(tinyxml2::XMLNode* p_node){
	tinyxml2::XMLElement* ele = p_node->ToElement();
	if(ele == NULL)
		return NULL;
	const char* curName = ele->Name();
	return curName;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::findChildNode(tinyxml2::XMLDocument* doc, const char* find_node_name){
	const std::string findName(find_node_name);
	for(tinyxml2::XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		if(findName == getNodeName(curnode))
			return curnode;
	}
	return NULL;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::findChildNode(tinyxml2::XMLNode* parrent_node, const char* find_node_name){
	const std::string findName(find_node_name);
	for(tinyxml2::XMLNode* curnode = parrent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		const char* nodename = getNodeName(curnode);
		if(nodename == NULL)
			continue;
		if(findName == nodename)
			return curnode;
	}
	return NULL;
} // /////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLDocument* MyXML::setDoc(const char* f_name){
	fileName = f_name;
	if(doc == NULL)
		doc = new tinyxml2::XMLDocument();
	auto err = doc->LoadFile(f_name);
	if(err != tinyxml2::XML_SUCCESS){
		doc->ClearError();
		doc->Clear();
	}
	return doc;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLDocument* MyXML::setDoc(tinyxml2::XMLDocument* in_doc){
	if(doc != NULL && doc != in_doc)
		delete doc;
	doc = in_doc;
	return doc;
} // ////////////////////////////////////////////////////////////////////////////////////////////////

size_t MyXML::fillListNodes(const char* path_node){
	lstNodes.clear();
	const char* p = path_node;
	std::string s;
	while(*p != 0){
		if(*p == DELIMITER_NODES){
			if(s.size() > 0){
				lstNodes.push_back(s);
				s.clear();
			}
		} else
			s += *p;
		p++;
	}
	if(s.size() > 0)
		lstNodes.push_back(s);
	return lstNodes.size();
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::createNode(tinyxml2::XMLDocument* doc, const char* name_node){
	tinyxml2::XMLElement* element = doc->NewElement(name_node);
	tinyxml2::XMLNode* node = doc->InsertEndChild(element);
	return node;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::createNode(tinyxml2::XMLNode* parrent_node, const char* name_node){
	tinyxml2::XMLDocument* doc = parrent_node->GetDocument();
	tinyxml2::XMLElement* element = doc->NewElement(name_node);
	tinyxml2::XMLNode* node = parrent_node->InsertEndChild(element);
	return node;
} // ////////////////////////////////////////////////////////////////////////////////////////////////

tinyxml2::XMLNode* MyXML::setNode(tinyxml2::XMLNode* start_node){
	node = start_node;
	for(auto iter = lstNodes.begin(); iter != lstNodes.end(); iter++){
		const char* nodename = iter->c_str();
		auto par = node == NULL ? NULL : node->Parent();
		if(iter == lstNodes.begin())
			node = findChildNode(doc, nodename);
		else
			node = findChildNode(node, nodename);
		if(node == NULL)
			return NULL;
	}
	return node;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::setNode(tinyxml2::XMLDocument* in_doc, const char* node_path){
	setDoc(in_doc);
	fillListNodes(node_path);
	return setNode();
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::setNode(const char* f_name, const char* node_path){
	setDoc(f_name);
	fillListNodes(node_path);
	return setNode();
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::setNode(tinyxml2::XMLNode* in_node, const char* node_path){
	doc = in_node->GetDocument();
	node = in_node;
	return setNode();
} // ////////////////////////////////////////////////////////////////////////////////////////////////

tinyxml2::XMLNode* MyXML::setOrCreateNode(){
	node = NULL;
	for(auto iter = lstNodes.begin(); iter != lstNodes.end(); iter++){
		const char* nodename = iter->c_str();
		if(iter == lstNodes.begin()){
			node = findChildNode(doc, nodename);
			if(node == NULL){
				node = createNode(doc, nodename);
				if(node == NULL)
					return NULL;
			}
		} else{
			tinyxml2::XMLNode* parrentnode = node;
			node = findChildNode(parrentnode, nodename);
			if(node == NULL){
				node = createNode(parrentnode, nodename);
				if(node == NULL)
					return NULL;
			}
		}
	}
	return node;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::setOrCreateNode(tinyxml2::XMLDocument* in_doc, const char* node_path){
	setDoc(in_doc);
	fillListNodes(node_path);
	return setOrCreateNode();
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::setOrCreateNode(const char* f_name, const char* node_path){
	setDoc(f_name);
	fillListNodes(node_path);
	return setOrCreateNode();
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::setOrCreateNode(tinyxml2::XMLNode* start_node, const char* node_path){
	setDoc(start_node->GetDocument());
	fillListNodes(node_path);
	node = start_node;
	for(auto iter = lstNodes.begin(); iter != lstNodes.end(); iter++){
		const char* nodename = iter->c_str();
		tinyxml2::XMLNode* parrentnode = node;
		node = findChildNode(parrentnode, nodename);
		if(node == NULL){
			node = createNode(parrentnode, nodename);
			if(node == NULL)
				return NULL;
		}
	}
	return node;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::setOrCreateNode(const char* node_path){
	return setOrCreateNode(node, node_path);
} // ////////////////////////////////////////////////////////////////////////////////////////////////

std::string MyXML::getText(const char* def_val){
	if(node == NULL)
		return def_val;
	const char* text = node->ToElement()->GetText();
	return (text == NULL) ? def_val : text;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
std::string MyXML::getAttribute(const char* atr_name, const char* def_val){
	if(node == NULL)
		return def_val;
	const char* text = node->ToElement()->Attribute(atr_name);
	return (text == NULL) ? def_val : text;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
unsigned __int64 MyXML::getU64Attribute(const char* name_atr, unsigned __int64 defval){
	char StrDefault[20];
	sprintf_s(StrDefault, "%llu", defval);
	std::string s = getAttribute(name_atr, StrDefault);
	unsigned __int64 ret = std::stoull(s);
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
unsigned __int32 MyXML::getU32Attribute(const char* name_atr, unsigned __int32 defval){
	char StrDefault[10];
	sprintf_s(StrDefault, "%u", defval);
	std::string s = getAttribute(name_atr, StrDefault);
	unsigned __int32 ret = std::stoul(s);
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
size_t MyXML::getSizetAttribute(const char* name_atr, size_t defval){
	std::string sdef = std::to_string(defval);
	std::string s = getAttribute(name_atr, sdef.c_str());
	size_t ret = myconv::strToSize_t(s.c_str());
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
//time_t MyXML::getTimetAttribute(const char* name_atr, time_t defval){
//	std::string sdef = std::to_string(defval);
//	std::string s = getAttribute(name_atr, sdef.c_str());
//	time_t ret = atoll(s.c_str());
//	return ret;
//} // ////////////////////////////////////////////////////////////////////////////////////////////////
//template<typename T>
//T MyXML::getAttributeT(const char* name_atr, T defval){
//	std::string sdef = std::to_string(defval);
//	std::string s = getAttribute(name_atr, sdef.c_str());
//	T ret = parse_string<T>(s.c_str());
//	return ret;
//} // ////////////////////////////////////////////////////////////////////////////////////////////////
void MyXML::setText(const char* val){
	node->ToElement()->SetText(val);
} // ////////////////////////////////////////////////////////////////////////////////////////////////
void MyXML::setAttributeS(const char* name_atr, const char* val){
	node->ToElement()->SetAttribute(name_atr, val);
} // ////////////////////////////////////////////////////////////////////////////////////////////////
//template<typename T>
//void MyXML::setAttributeT(const char* name_atr, T val){
//	node->ToElement()->SetAttribute(name_atr, std::to_string(val).c_str());
//} // ////////////////////////////////////////////////////////////////////////////////////////////////
void MyXML::Load(const char* f_name){
	if(doc == NULL)
		doc = new tinyxml2::XMLDocument();
	doc->LoadFile(f_name);
} // ////////////////////////////////////////////////////////////////////////////////////////////////
void MyXML::Save(const char* f_name){
	if(doc == NULL)
		doc = new tinyxml2::XMLDocument();
	doc->SaveFile(f_name);
} // ////////////////////////////////////////////////////////////////////////////////////////////////
void MyXML::Save(){
	doc->SaveFile(fileName.c_str());
} // ////////////////////////////////////////////////////////////////////////////////////////////////

