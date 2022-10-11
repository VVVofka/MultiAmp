#pragma once
#include <afxstr.h>
#include <afxwin.h>
class ForMfsControls{
public:
	static float getFloatFromCEdit(CEdit& edit){
		CString sb;
		edit.GetWindowTextA(sb);
		sb.Replace(" ", "");
		sb.Replace(',', '.');
		return std::strtof((LPCSTR)sb, NULL);
	} // //////////////////////////////////////////////////////////////////////////////
	static UINT32 getUINT32FromCEdit(CEdit& edit){
		CString sb;
		edit.GetWindowTextA(sb);
		UINT32 u;
		sscanf_s((LPCSTR)sb, "%u", &u);
		return u;
	} // //////////////////////////////////////////////////////////////////////////////


};