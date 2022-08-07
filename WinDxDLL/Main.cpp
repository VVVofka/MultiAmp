#include "pch.h"
#include "Main.h"

int tstdllMain(HINSTANCE hInstance, int nCmdShow, int a, int b){
	return a + b;
} // /////////////////////////////////////////////////////////////////////
int openwnd(HINSTANCE hInstance, int nCmdShow, char* json){
	int ret = mn(hInstance, NULL, NULL, nCmdShow, json);
	return ret;
} // /////////////////////////////////////////////////////////////////////