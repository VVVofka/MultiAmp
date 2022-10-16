#pragma once
#include <list>
#include <string>
#include "tinyxml2.h" 

namespace myxml{
	//using namespace tinyxml2;
	//using namespace std;

	namespace priv{
		const char DELIMITER_NODES = ';';

		const char* getNodeName(tinyxml2::XMLNode* p_node);
		tinyxml2::XMLNode* findNode(tinyxml2::XMLDocument* doc, const char* node_name);
		tinyxml2::XMLNode* findNode(tinyxml2::XMLNode* parrent_node, const char* node_name);
		size_t getListNodes(const char* path_node, std::list<std::string>* list_nodes);
		tinyxml2::XMLNode* createNode(tinyxml2::XMLDocument* doc, const char* name_node);
		tinyxml2::XMLNode* createNode(tinyxml2::XMLNode* parrent_node, const char* name_node);

	}	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	tinyxml2::XMLNode* getNode(tinyxml2::XMLDocument* in_doc, const char* node_path);
	tinyxml2::XMLNode* getOrCreateNode(tinyxml2::XMLDocument* in_doc, const char* node_path);
	tinyxml2::XMLNode* getNode(const char* f_name, const char* node_path);
	tinyxml2::XMLNode* getOrCreateNode(const char* f_name, const char* node_path);

	const char* getAttribute(tinyxml2::XMLNode* node, const char* name_atr, const char* def_val);
	void setAttribute(tinyxml2::XMLNode* node, const char* name_atr, const char* val);
	const char* getText(tinyxml2::XMLNode* node, const char* def_val);
	void setText(tinyxml2::XMLNode* node, const char* val);
} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
class MyXML{
public:
	tinyxml2::XMLDocument* doc = NULL;
	tinyxml2::XMLNode* node = NULL;
	char DELIMITER_NODES = ';';

	MyXML();
	MyXML(const char* f_name);
	MyXML(tinyxml2::XMLDocument* in_doc);
	MyXML(tinyxml2::XMLNode* in_node);
	MyXML(tinyxml2::XMLDocument* in_doc, const char* path_node);
	MyXML(const char* f_name, const char* path_node);
	~MyXML();

	tinyxml2::XMLNode* setNode(tinyxml2::XMLDocument* in_doc, const char* node_path);
	tinyxml2::XMLNode* setOrCreateNode(tinyxml2::XMLDocument* in_doc, const char* node_path);
	tinyxml2::XMLNode* setNode(const char* f_name, const char* node_path);
	tinyxml2::XMLNode* setOrCreateNode(const char* f_name, const char* node_path);

private:
	std::list<std::string> lstNodes;

	tinyxml2::XMLDocument* setDoc(const char* f_name);
	tinyxml2::XMLDocument* setDoc(tinyxml2::XMLDocument*);

	tinyxml2::XMLNode* findNode(tinyxml2::XMLDocument* doc, const char* node_name);
	tinyxml2::XMLNode* findNode(tinyxml2::XMLNode* parrent_node, const char* node_name);

	size_t fillListNodes(const char* path_node);

	static tinyxml2::XMLNode* createNode(tinyxml2::XMLDocument* doc, const char* name_node);
	static tinyxml2::XMLNode* createNode(tinyxml2::XMLNode* parrent_node, const char* name_node);

	tinyxml2::XMLNode* setNode();
	tinyxml2::XMLNode* setOrCreateNode();
};
