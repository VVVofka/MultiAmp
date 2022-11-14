#pragma once
#include <string>
class ParseCmdLine{
public:
	std::string fname;
	const char* def_fname = "defaultcfg.xml";
	INT64 tick_cnt;
	INT64 parse(LPWSTR s);

	static std::string& ltrim(std::string& s);
	static std::string& rtrim(std::string& s);
	static std::string& trim(std::string& s);
	static std::wstring s2ws(const std::string& str);
	static std::string ws2s(const std::wstring& wstr);
private:

};

