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
XMLNode* getNode(const char* f_name, const char* node_path)
	XMLNode* getNode(XMLDocument* doc, const char* node_path)
		size_t getListNodes(const char* path_node, list<string>* list_nodes)
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
	auto err = doc->LoadFile(f_name);
	if(err != tinyxml2::XML_SUCCESS){
		doc->ClearError();
		doc->Clear();
	}
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
	getListNodes(path_node);
} // ///////////////////////////////////////////////////////////////////////////////////////////////////
MyXML::MyXML(const char* f_name, const char* path_node){
	auto err = doc->LoadFile(f_name);
	if(err != tinyxml2::XML_SUCCESS){
		doc->ClearError();
		doc->Clear();
	}
	getListNodes(path_node);
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
} // ////////////////////////////////////////////////////////////////////////////////////////////////
size_t MyXML::getListNodes(const char* path_node, std::list<std::string>* list_nodes){
	list_nodes->clear();
	const char* p = path_node;
	std::string s;
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
size_t MyXML::getListNodes(const char* path_node){
	return getListNodes(path_node, &lstNodes);
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
tinyxml2::XMLNode* MyXML::getNode(tinyxml2::XMLDocument* doc, const char* node_path){
	std::list<std::string> vnodes;
	getListNodes(node_path, &vnodes);

	tinyxml2::XMLNode* curnode = NULL;
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
tinyxml2::XMLNode*  MyXML::getOrCreateNode(tinyxml2::XMLDocument* doc, const char* node_path){
	std::list<std::string> vnodes;
	getListNodes(node_path, &vnodes);

	tinyxml2::XMLNode* curnode = NULL;
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
			tinyxml2::XMLNode* parrentnode = curnode;
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
tinyxml2::XMLNode* MyXML::getNode(const char* f_name, const char* node_path){
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.LoadFile(f_name);
	if(err != tinyxml2::XML_SUCCESS)
		return NULL;
	return getNode(&doc, node_path);
} // ////////////////////////////////////////////////////////////////////////////////////////////////
tinyxml2::XMLNode* MyXML::getOrCreateNode(const char* f_name, const char* node_path){
	tinyxml2::XMLDocument doc;
	auto err = doc.LoadFile(f_name);
	if(err != tinyxml2::XML_SUCCESS){
		doc.ClearError();
		doc.Clear();
	}
	auto ret = getOrCreateNode(&doc, node_path);
	if(ret != NULL)
		doc.SaveFile(f_name);
	return ret;
} // ////////////////////////////////////////////////////////////////////////////////////////////////
