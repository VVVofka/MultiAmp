#include "pch.h"
#ifdef MODEA
#include "Utils.h"

void setConsole(){
#pragma warning(push)
#pragma warning(disable : 4996)
	if(::GetConsoleWindow() == NULL){
		if(::AllocConsole()){
			(void)freopen("CONIN$", "r", stdin);
			(void)freopen("CONOUT$", "w", stdout);
			(void)freopen("CONOUT$", "w", stderr);
			SetFocus(::GetConsoleWindow());
		}
	}
#pragma warning(pop)
} // ///////////////////////////////////////////////////////////////////////////
#endif  // MODEA

