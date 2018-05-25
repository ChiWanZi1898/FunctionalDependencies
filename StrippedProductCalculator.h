//
// Created by Hongyu Zhu on 2018/5/17.
//

#ifndef FD_STRIPPEDPRODUCTCALCULATOR_H
#define FD_STRIPPEDPRODUCTCALCULATOR_H

#include <vector>
#include <bitset>
#include <iostream>
#include <unordered_map>
#include "constants.h"
using namespace std;

class StrippedProductCalculator {
public:
    StrippedProductCalculator(unsigned rowNum);
    unsigned strippedProduct(const Attrs &ap1, const Attrs &ap2,
                                const vector<vector<unsigned>> &p1,
                             const vector<vector<unsigned>> &p2,
                             vector<vector<unsigned>> &p);
private:
    unsigned rowNum;
    unordered_map<Attrs, vector<int>> TMap;
    vector<vector<unsigned>> S;
};


#endif //FD_STRIPPEDPRODUCTCALCULATOR_H
