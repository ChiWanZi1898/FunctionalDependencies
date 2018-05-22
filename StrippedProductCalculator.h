//
// Created by Hongyu Zhu on 2018/5/17.
//

#ifndef FD_STRIPPEDPRODUCTCALCULATOR_H
#define FD_STRIPPEDPRODUCTCALCULATOR_H

#include <vector>
#include <bitset>
#include <iostream>
#include "constants.h"
using namespace std;

class StrippedProductCalculator {
public:
    StrippedProductCalculator(unsigned rowNum);
    unsigned strippedProduct(const vector<vector<unsigned>> &p1,
                             const vector<vector<unsigned>> &p2,
                             vector<vector<unsigned>> &p);
private:
    unsigned rowNum;
    vector<int> T;
    vector<vector<unsigned>> S;
};


#endif //FD_STRIPPEDPRODUCTCALCULATOR_H
