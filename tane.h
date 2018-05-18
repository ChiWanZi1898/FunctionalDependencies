//
// Created by Hongyu Zhu on 2018/5/17.
//

#ifndef FD_TANE_H
#define FD_TANE_H

#include <vector>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include "constants.h"
#include "StrippedProductCalculator.h"

using namespace std;

void computeDependencies(vector<Attrs > &L, unordered_map<Attrs, Attrs > &lastCPlus,
                         unordered_map<Attrs, Attrs > &currCPlus, const vector<vector<unsigned>> &,
                         const vector<vector<unsigned>> &, const vector<unordered_map<Attrs, unsigned>> &);

void computeInitPartition(vector<vector<vector<unsigned >>> &partitions,
                          vector<unsigned>&,
                          vector<unsigned>&,
                          unordered_map<Attrs, unsigned> &attrPartitionMap,
                          const vector<vector<unsigned>> &data);

void computePrefixBlocks(vector<Attrs > &L, vector<vector<Attrs>> &);

void getPrefixAttr(Attrs &);

void prepareL1(vector<Attrs > &);

void generateNextLevel(vector<vector<Attrs>> &, int,
                       vector<vector<vector<vector<unsigned>>>> &,
                       vector<unordered_map<Attrs, unsigned>> &,
                       vector<vector<unsigned>>&,
                       vector<vector<unsigned>>&,
                       StrippedProductCalculator &);

bool validDependency(const vector<vector<unsigned>> &,
                     const vector<vector<unsigned>> &,
                     const vector<unordered_map<Attrs, unsigned>> &,
                      const Attrs &, const Attrs &);

void prune(vector<Attrs > &L, unordered_map<Attrs, Attrs > &lastCPlus);

void quickDelete(int, vector<Attrs>&);


#endif //FD_TANE_H
