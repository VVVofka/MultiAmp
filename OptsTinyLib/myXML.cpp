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
	} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
	using namespace priv;
	XMLNode* getNode(XMLDocument* doc, const char* node_path){
		list<string> vnodes;
		size_t cntNodes = getListNodes(node_path, &vnodes);

		auto last = vnodes.end();
		string lastName = last->c_str();

		auto iter = vnodes.begin();
		XMLNode* curnode = findNode(doc, iter->c_str());
		if(curnode == NULL)
			return NULL;
		const char* curname0 = getNodeName(curnode);
		if(lastName == curname0)
			return curnode;

		while(++iter != last){
			curnode = findNode(curnode, iter->c_str());
			if(curnode == NULL)
				return NULL;
			const char* curname = getNodeName(curnode);
			if(lastName == curname)
				return curnode;
		}
		return NULL;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	XMLNode* getOrCreateNode(XMLDocument* doc, const char* node_path){
		list<string> vnodes;
		size_t cntNodes = getListNodes(node_path, &vnodes);

		auto last = vnodes.end();
		string lastName = last->c_str();

		auto iter = vnodes.begin();
		XMLNode* curnode = findNode(doc, iter->c_str());
		if(curnode == NULL)
			return NULL;
		const char* curname0 = getNodeName(curnode);
		if(lastName == curname0)
			return curnode;

		while(++iter != last){
			curnode = findNode(curnode, iter->c_str());
			if(curnode == NULL)
				return NULL;
			const char* curname = getNodeName(curnode);
			if(lastName == curname)
				return curnode;
		}
		return NULL;
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	XMLNode* getNode(const char* f_name, const char* node_path){
		XMLDocument doc;
		XMLError err = doc.LoadFile(f_name);
		if(err != XML_SUCCESS){
			//doc.ClearError();
			//doc.Clear();
			return NULL;
		}
		return getNode(&doc, node_path);
	} // ////////////////////////////////////////////////////////////////////////////////////////////////
	XMLNode* getOrCreateNode(const char* f_name, const char* node_path){
		XMLDocument doc;
		doc.LoadFile(f_name);
		return getOrCreateNode(&doc, node_path);
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