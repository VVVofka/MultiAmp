#include "pch.h"
#include "Main.h"

int tstdllMain(HINSTANCE hInstance, int nCmdShow, int a, int b){
	return a + b;
} // /////////////////////////////////////////////////////////////////////
int openwnd(HINSTANCE hInstance, int nCmdShow, char* json_in, char* json_out){
	int ret = mn(hInstance, NULL, NULL, nCmdShow, json_in, json_out);
	return ret;
} // /////////////////////////////////////////////////////////////////////