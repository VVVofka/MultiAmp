#pragma once
#include <afxstr.h>
#include <afxwin.h>
class ForMfsControls{
public:
	static float getFloatFromCEdit(CEdit& edit, std::string* s_out = NULL){
		CString sb;
		edit.GetWindowTextA(sb);
		sb.Replace(" ", "");
		sb.Replace(',', '.');
		//float ret = std::strtof((LPCSTR)sb, NULL);
		float flt;
		sscanf_s((LPCSTR)sb, "%f", &flt);
		std::string s = std::to_string(flt);
		edit.SetWindowTextA(s.c_str());
		edit.UpdateWindow();
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


};