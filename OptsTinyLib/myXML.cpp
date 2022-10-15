#include "myXML.h"
#include <string>
namespace myxml{
	namespace priv{
		using namespace std;
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
		doc.LoadFile(f_name);
		return getOrCreateNode(&doc, node_path);
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