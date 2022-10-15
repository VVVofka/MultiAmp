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