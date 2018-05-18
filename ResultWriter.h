//
// Created by Hongyu Zhu on 2018/5/18.
//

#ifndef FD_RESULTWRITER_H
#define FD_RESULTWRITER_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "constants.h"
using namespace std;

class ResultWriter {
public:
    ResultWriter(string);
    void add(Attrs&, unsigned);
    void write();

private:
    string outputPath;
    vector<vector<unsigned>> results;
};


#endif //FD_RESULTWRITER_H
