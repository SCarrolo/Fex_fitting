#ifndef FCTOOLS_H
#define FCTOOLS_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "Vec.h"

using namespace std;

class FCtools {
  public:
    vector<string> ReadFile2String(string); //file name, returns lines
    vector<Vec> ReadFile2Vec(string); //file name, returns vectors of Vec’s
    Vec* ReadFile(string); //file name, returns pointer to array of Vec’s
};


#endif
