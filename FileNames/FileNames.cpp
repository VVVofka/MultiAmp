// FileNames.cpp : Defines the functions for the static library.
#include "framework.h"
#include "FileNames.h"

std::string exeDir(){
	TCHAR szPath[MAX_PATH];
	if(!GetModuleFileName(NULL, szPath, MAX_PATH)){
		printf("GetModuleFileName failed (%d)\n", GetLastError());
		return std::string();
	}
	PathRemoveFileSpec(szPath);
	return std::string(szPath);
} // //////////////////////////////////////////////////////////////
std::string curDir(){
	char cCurrentPath[FILENAME_MAX];
	if(!_getcwd(cCurrentPath, sizeof(cCurrentPath))){
		printf("_getcwd failed (%d)\n", GetLastError());
		return std::string();
	}
	return std::string(cCurrentPath);
} // //////////////////////////////////////////////////////////////
