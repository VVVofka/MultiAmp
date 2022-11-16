#pragma once
#include <stdlib.h>
#include <string>
#include <Shlwapi.h>
#include <direct.h>
#pragma comment(lib, "shlwapi.lib")

// small lib for get cur dir
// use in OptsTinyLibs

std::string exeDir();
std::string curDir();