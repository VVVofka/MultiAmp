#include "myXML.h"
#include <string>
namespace myxml{
	namespace priv{
		using namespace std;
		using namespace tinyxml2;
		const char* getNodeName(XMLNode* p_node){
			XMLElement* ele = p_node->ToElement();
			const char* curName = ele->Name();
			return curName;
		} // ////////////////////////////////////////////////////////////////////////////////////////////////
		XMLNode* findNode(XMLDocument* doc, const char* find_node_name){
			const string findName(find_node_name);
			for(XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
				if(findName == getNodeName(curnode))
					return curnode;
			}
			return NULL;
		} // ////////////////////////////////////////////////////////////////////////////////////////////////
		XMLNode* findNode(XMLNode* parrent_node, const char* find_node_name){
			const string findName(find_node_name);
			for(XMLNode* curnode = parrent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
				if(findName == getNodeName(curnode))
					return curnode;
			}
			return NULL;
		} // ////////////////////////////////////////////////////////////////////////////////////////////////
		size_t getListNodes(const char* path_node, list<string>* list_nodes){
			list_nodes->clear();
			const char* p = path_node;
			string s;
			while(*p != 0){
				if(*p == DELIMITER_NODES){
					if(s.size() > 0){
						list_nodes->push_back(s);
						s.clear();
					}
				} else
					s += *p;
				p++;
			}
			if(s.size() > 0)
				list_nodes->push_back(s);
			return list_nodes->size();
		} // ////////////////////////////////////////////////////////////////////////////////////////////////
		XMLNode* createNode(XMLDocument* doc, const char* name_node){
			XMLElement* element = doc->NewElement(name_node);
			XMLNode* node = doc->InsertEndChild(element);
			return node;
		} // ////////////////////////////////////////////////////////////////////////////////////////////////
		XMLNode* createNode(XMLNode* parrent_node, const char* name_node){
			XMLDocument* doc = parrent_node->GetDocument();
			XMLElement* element = doc->NewElement(name_node);
			XMLNode* node = parrent_node->InsertEndChild(element);
			return node;
		} // ////////////////////////////////////////////////////////////////////////////////////////////////
	} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
	using namespace priv;
	XMLNode* getNode(XMLDocument* doc, const char* node_path){
		list<string> vnodes;
		getListNodes(node_path, &vnodes);

		XMLNode* curnode = NULL;
		for(auto iter = vnodes.begin(); iter != vnodes.end(); iter++){
			const char* nodename = iter->c_str();
			if(iter == vnodes.begin())
				curnode = findNode(doc, nodename);
			else
				curnode = findNode(curnode, nodename);
			if(curnode == NULL)
				return NULL;
		}
		return curnode;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	XMLNode* getOrCreateNode(XMLDocument* doc, const char* node_path){
		list<string> vnodes;
		getListNodes(node_path, &vnodes);

		XMLNode* curnode = NULL;
		for(auto iter = vnodes.begin(); iter != vnodes.end(); iter++){
			const char* nodename = iter->c_str();
			if(iter == vnodes.begin()){
				curnode = findNode(doc, nodename);
				if(curnode == NULL){
					curnode = createNode(doc, nodename);
					if(curnode == NULL)
						return NULL;
				}
			} else{
				XMLNode* parrentnode = curnode;
				curnode = findNode(parrentnode, nodename);
				if(curnode == NULL){
					curnode = createNode(parrentnode, nodename);
					if(curnode == NULL)
						return NULL;
				}
			}
		}
		return curnode;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	XMLNode* getNode(const char* f_name, const char* node_path){
		XMLDocument doc;
		XMLError err = doc.LoadFile(f_name);
		if(err != XML_SUCCESS)
			return NULL;
		return getNode(&doc, node_path);
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	XMLNode* getOrCreateNode(const char* f_name, const char* node_path){
		XMLDocument doc;
		auto err = doc.LoadFile(f_name);
		if(err != XML_SUCCESS){
			doc.ClearError();
			doc.Clear();
		}
		auto ret = getOrCreateNode(&doc, node_path);
		if(ret != NULL)
			doc.SaveFile(f_name);
		return ret;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	const char* getAttribute(XMLNode* node, const char* name_atr, const char* def_val){
		const char* text = node->ToElement()->Attribute(name_atr);
		return (text == NULL) ? def_val : text;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	void setAttribute(XMLNode* node, const char* name_atr, const char* val){
		node->ToElement()->SetAttribute(name_atr, val);
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	const char* getText(XMLNode* node, const char* def_val){
		const char* text = node->ToElement()->GetText();
		return (text == NULL) ? def_val : text;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	void setText(XMLNode* node, const char* val){
		node->ToElement()->SetText(val);
	} // ////////////////////////////////////////////////////////////////////////////////////////////////

} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
XMLNode* setNode(const char* f_name, const char* node_path)
	XMLNode* setNode(XMLDocument* doc, const char* node_path)
		size_t fillListNodes(const char* path_node, list<string>* list_nodes)
		XMLNode* findNode(XMLDocument* doc, const char* find_node_name)
			const char* getNodeName(XMLNode* p_node)
		const char* getNodeName(XMLNode* p_node)
		XMLNode* findNode(XMLNode* parrent_node, const char* find_node_name)
			const char* getNodeName(XMLNode* p_node)
*/
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
	if(doc != NULL)
		delete doc;
	doc = in_doc;
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(tinyxml2::XMLNode* in_node){
	if(doc != NULL)
		delete doc;
	node = in_node;
	doc = node->GetDocument();
}  // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(tinyxml2::XMLDocument* in_doc, const char* path_node){
	if(doc != NULL)
		delete doc;
	doc = in_doc;
	fillListNodes(path_node);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(const char* f_name, const char* path_node){
	setDoc(f_name);
	fillListNodes(path_node);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
const char* getNodeName(tinyxml2::XMLNode* p_node){
	tinyxml2::XMLElement* ele = p_node->ToElement();
	const char* curName = ele->Name();
	return curName;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::findNode(tinyxml2::XMLDocument* doc, const char* find_node_name){
	const std::string findName(find_node_name);
	for(tinyxml2::XMLNode* curnode = doc->FirstChild(); curnode; curnode = curnode->NextSibling()){
		if(findName == getNodeName(curnode))
			return curnode;
	}
	return NULL;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::findNode(tinyxml2::XMLNode* parrent_node, const char* find_node_name){
	const std::string findName(find_node_name);
	for(tinyxml2::XMLNode* curnode = parrent_node->FirstChild(); curnode; curnode = curnode->NextSibling()){
		if(findName == getNodeName(curnode))
			return curnode;
	}
	return NULL;
} // /////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLDocument* MyXML::setDoc(const char* f_name){
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
	if(doc != NULL)
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

tinyxml2::XMLNode* MyXML::setNode(){
	node = NULL;
	for(auto iter = lstNodes.begin(); iter != lstNodes.end(); iter++){
		const char* nodename = iter->c_str();
		if(iter == lstNodes.begin())
			node = findNode(doc, nodename);
		else
			node = findNode(node, nodename);
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

tinyxml2::XMLNode* MyXML::setOrCreateNode(){
	node = NULL;
	for(auto iter = lstNodes.begin(); iter != lstNodes.end(); iter++){
		const char* nodename = iter->c_str();
		if(iter == lstNodes.begin()){
			node = findNode(doc, nodename);
			if(node == NULL){
				node = createNode(doc, nodename);
				if(node == NULL)
					return NULL;
			}
		} else{
			tinyxml2::XMLNode* parrentnode = node;
			node = findNode(parrentnode, nodename);
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
