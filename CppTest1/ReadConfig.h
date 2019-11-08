//
// Created by LiXiang on 2018/12/15.
//

#ifndef SYSTEMTEST_READCONFIG_H
#define SYSTEMTEST_READCONFIG_H

#include <string>
#include <map>
#include <fstream>
//#include "logc.h"
#include "tools.h"
#include "FDGazeVR.h"

using namespace std;

int ReadConfigFile(const char * cfgfilepath, map<string,string> &cfg_map,PupilGlint &pg);


#endif //SYSTEMTEST_READCONFIG_H
