#ifndef __COMMON_H_
#define __COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <list>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "utils/math.h"
#include "utils/random.h"

using namespace std;

void split(const string &s, char delim, vector<string> &elems, unsigned int maxElems);
vector<string> split(const string &s, char delim, unsigned int maxElems = 0);

#endif
