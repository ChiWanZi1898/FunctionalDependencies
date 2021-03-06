//
// Created by Hongyu Zhu on 2018/5/17.
//

#include "StrippedProductCalculator.h"

StrippedProductCalculator::StrippedProductCalculator(unsigned rowNum) : rowNum(rowNum), S(20400) {
}

unsigned
StrippedProductCalculator::strippedProduct(const Attrs &ap1, const Attrs &ap2, const vector<vector<unsigned>> &p1,
                                           const vector<vector<unsigned>> &p2,
                                           vector<vector<unsigned>> &p) {
    p.clear();
    unsigned count = 0;

    //p.resize(30, vector<unsigned>());
    //unsigned index = 0;
    auto got = TMap.find(ap1);
    if (got == TMap.end()) {
        vector<int> Tt(rowNum+1, -1);
        for (unsigned i = 0; i < p1.size(); i++) {
            for (unsigned j = 0; j < p1[i].size(); j++) {
                Tt[p1[i][j]] = i;
            }
        }
        TMap.insert({ap1, Tt});
        got = TMap.find(ap1);
    }
    vector<int> &T = got->second;

    p.reserve(10500);

    for (unsigned i = 0; i < p2.size(); i++) {

        for (unsigned j = 0; j < p2[i].size(); j++) {
            if (T[p2[i][j]] != -1) {
                S[T[p2[i][j]]].push_back(p2[i][j]);
            }
        }
        for (unsigned j = 0; j < p2[i].size(); j++) {
            if (T[p2[i][j]] != -1) {
                if (S[T[p2[i][j]]].size() >= 2) {
                    count += S[T[p2[i][j]]].size();
                    //if(index < 30)
                    //p[index] =S[T[p2[i][j]]];
                    //else
                    p.push_back(S[T[p2[i][j]]]);
                    //index++;
                }
                S[T[p2[i][j]]].clear();
            }
        }
    }
//    for (unsigned i = 0; i < p1.size(); i++) {
//        for (unsigned j = 0; j < p1[i].size(); j++) {
//            T[p1[i][j]] = -1;
//        }
//    }
    //p.resize(index);
    return count;
}
