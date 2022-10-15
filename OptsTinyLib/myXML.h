#pragma once
#include <list>
#include <string>
#include "tinyxml2.h" 

namespace myxml{
	using namespace tinyxml2;
	using namespace std;

	const char DELIMITER_NODES = ';';

	const char* getNodeName(XMLNode* p_node);
	XMLNode* findNode(XMLDocument* doc, const char* node_name);
	XMLNode* findNode(XMLNode* parrent_node, const char* node_name);
	size_t getListNodes(const char* path_node, list<string>* list_nodes);
	XMLNode* getNode(XMLDocument* in_doc, const char* node_path);
	XMLNode* getNode(const char* node_path);
}