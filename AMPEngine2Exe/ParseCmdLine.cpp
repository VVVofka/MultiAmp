#include "pch.h"
#include "ParseCmdLine.h"
#include <algorithm>
#include <functional>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;
INT64 ParseCmdLine::parse(LPWSTR s_in){
	tick_cnt = 0;
	fname.clear();
	
	string s = ws2s(s_in);
	trim(s);
	size_t len = s.size();
	
	char delim;
	size_t pos;
	if(s[0] == '"' || s[0] == '\'' || s[0] == '`'){
		delim = s[0];
		pos = 1;
	}
	else{
		delim = ' ';
		pos = 0;
		fname = s[0];
	}

	while(pos < len){
		if(s[pos] == delim)
			break;
		fname += s[pos++];
	}
	if(fname.size() == 0 ) 
		fname = def_fname;

	while(pos < len){
		const int ch = s[pos] - '0';
		if(ch >= 0 && ch <= 9)
			tick_cnt = tick_cnt * 10 + ch;
		pos++;
	}
	return tick_cnt;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////
//std::wstring ParseCmdLine::trim(wchar_t const* str){
//} // ////////////////////////////////////////////////////////////////////////////////////////////////////
std::string& ParseCmdLine::ltrim(std::string& s){
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::ptr_fun<int, int>(std::isgraph)));
	return s;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////
std::string& ParseCmdLine::rtrim(std::string& s){
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::ptr_fun<int, int>(std::isgraph)).base(), s.end());
	return s;
} // ////////////////////////////////////////////////////////////////////////////////////////////////////
std::string& ParseCmdLine::trim(std::string& s){
	return ltrim(rtrim(s));
} // ////////////////////////////////////////////////////////////////////////////////////////////////////
std::wstring ParseCmdLine::s2ws(const std::string& str){
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;
	return converterX.from_bytes(str);
} // ////////////////////////////////////////////////////////////////////////////////////////////////////
std::string ParseCmdLine::ws2s(const std::wstring& wstr){
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;
	return converterX.to_bytes(wstr);
} // ////////////////////////////////////////////////////////////////////////////////////////////////////