#pragma once
#include <list>
#include <string>
#include <sstream>      // std::ostringstream
#include "tinyxml2.h" 
#include "myconv.h"

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
	tinyxml2::XMLNode* setNode(tinyxml2::XMLNode* in_node, const char* node_path);
	tinyxml2::XMLNode* setOrCreateNode(tinyxml2::XMLNode* in_node, const char* node_path);
	tinyxml2::XMLNode* setOrCreateNode(const char* node_path);

	std::string getText(const char* defval = "");
	std::string getAttributeS(const char* atr_name, const char* defval = "");
	std::string getAttributeS(const char* atr_name, const std::string& defval = "");
	template<typename T> T getAttributeT(const char* name_atr, T defval = 0){
		std::string s = getAttributeS(name_atr, std::to_string(defval));
		return parse_string<T>(s.c_str());
	}
	void setText(const char* s);
	void setText(std::string& s){ setText(s.c_str()); };
	void setAttributeS(const char* name_atr, const char* val);
	void setAttributeS(const char* name_atr, const std::string& val);
	template<typename T> void setAttributeT(const char* name_atr, T val){
		node->ToElement()->SetAttribute(name_atr, std::to_string(val).c_str());
	}

	void Load(const char* f_name);
	void Save(const char* f_name);
	void Save();
private:
	std::list<std::string> lstNodes;
	std::string fileName;

	tinyxml2::XMLDocument* setDoc(const char* f_name);
	tinyxml2::XMLDocument* setDoc(tinyxml2::XMLDocument*);

	static const char* getNodeName(tinyxml2::XMLNode* p_node);
	static tinyxml2::XMLNode* findChildNode(tinyxml2::XMLDocument* doc, const char* node_name);
	static tinyxml2::XMLNode* findChildNode(tinyxml2::XMLNode* parrent_node, const char* node_name);

	size_t fillListNodes(const char* path_node);

	static tinyxml2::XMLNode* createNode(tinyxml2::XMLDocument* doc, const char* name_node);
	static tinyxml2::XMLNode* createNode(tinyxml2::XMLNode* parrent_node, const char* name_node);

	tinyxml2::XMLNode* setNode(tinyxml2::XMLNode* start_node = NULL);
	tinyxml2::XMLNode* setOrCreateNode();

	// parse_string
	template <typename RETURN_TYPE, typename STRING_TYPE>
	RETURN_TYPE parse_string(const STRING_TYPE& str){
		std::stringstream buf;
		buf << str;
		RETURN_TYPE val;
		buf >> val;
		return val;
	}
};
