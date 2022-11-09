#include "Main.h"

int tstdllMain(HINSTANCE hInstance, int nCmdShow, int a, int b){
	return a + b;
} // /////////////////////////////////////////////////////////////////////
int openwnd(HINSTANCE hInstance, int nCmdShow, structAll* cfg_all){
	int ret = mn(hInstance, NULL, NULL, nCmdShow, cfg_all);
	return ret;
} // /////////////////////////////////////////////////////////////////////