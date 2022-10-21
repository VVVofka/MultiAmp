#pragma once
#include "..\OptsTinyLib\structsAll.h"

int tstdllMain(HINSTANCE hInstance, int nCmdShow, int a, int b);
int openwnd(HINSTANCE hInstance, int nCmdShow, char* json_in, char* json_out);

// File: Tutorial01.cpp
int mn(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, structAll* cfg_all);
