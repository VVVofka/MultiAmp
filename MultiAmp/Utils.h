#pragma once
#include <afxstr.h>
#include <afxwin.h>
class ForMfsControls{
public:
	static size_t strToSize_t(const char* s){
#ifndef WIN32
		return size_t(std::stoull(s));
#else
		return size_t(std::stoul(s));
#endif // WIN32
	} // ////////////////////////////////////////////////////////////////////////////////////
	static int getIntFromCEdit(CEdit& edit, int def_val = 0){
		CString sb;
		edit.GetWindowTextA(sb);
		sb.Replace(" ", "");
		int u;
		int ret = sscanf_s((LPCSTR)sb, "%d", &u);
		if(ret == 1)
		return u;
		return def_val;
	} // //////////////////////////////////////////////////////////////////////////////
	static std::string getStrFromCEdit(CEdit& edit){
		CString sb;
		edit.GetWindowTextA(sb);
		return std::string(sb);
	} // //////////////////////////////////////////////////////////////////////////////
	static float getFloatFromCEdit(CEdit& edit, std::string* s_out = NULL){
		CString sb;
		edit.GetWindowTextA(sb);
		sb.Replace(" ", "");
		sb.Replace(',', '.');
		//float ret = std::strtof((LPCSTR)sb, NULL);
		float flt;
		sscanf_s((LPCSTR)sb, "%f", &flt);
		std::string s = std::to_string(flt);
		//edit.SetWindowTextA(s.c_str());
		//edit.UpdateWindow();
		if(s_out != NULL)
			*s_out = s;
		return flt;
	} // //////////////////////////////////////////////////////////////////////////////
	static UINT32 getUINT32FromCEdit(CEdit& edit, std::string* s_out = NULL){
		CString sb;
		edit.GetWindowTextA(sb);
		sb.Replace(" ", "");
		UINT32 u;
		sscanf_s((LPCSTR)sb, "%u", &u);
		std::string s = std::to_string(u);
		edit.SetWindowTextA(s.c_str());
		edit.UpdateWindow();
		if(s_out != NULL)
			*s_out = s;
		return u;
	} // //////////////////////////////////////////////////////////////////////////////
	static UINT64 getUINT64FromCEdit(CEdit& edit, std::string* s_out = NULL){
		CString sb;
		edit.GetWindowTextA(sb);
		sb.Replace(" ", "");
		UINT64 u = std::stoull((LPCSTR)sb);
		std::string s = std::to_string(u);
		edit.SetWindowTextA(s.c_str());
		edit.UpdateWindow();
		if(s_out != NULL)
			*s_out = s;
		return u;
	} // //////////////////////////////////////////////////////////////////////////////
	static size_t getSizetFromCEdit(CEdit& edit, std::string* s_out = NULL){
		CString sb;
		edit.GetWindowTextA(sb);
		sb.Replace(" ", "");
		size_t u = strToSize_t(sb);
		std::string s = std::to_string(u);
		edit.SetWindowTextA(s.c_str());
		edit.UpdateWindow();
		if(s_out != NULL)
			*s_out = s;
		return u;
	} // //////////////////////////////////////////////////////////////////////////////


};