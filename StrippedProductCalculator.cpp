//
// Created by Hongyu Zhu on 2018/5/17.
//

#include "StrippedProductCalculator.h"

StrippedProductCalculator::StrippedProductCalculator(unsigned rowNum) : rowNum(rowNum), T(rowNum + 1, -1) {
}

unsigned
StrippedProductCalculator::strippedProduct(const vector<vector<unsigned>> &p1, const vector<vector<unsigned>> &p2,
                                           vector<vector<unsigned>> &p) {
    p.clear();
    unsigned count = 0;
    unsigned xxx = 0;
    int y;
    vector<vector<unsigned>> S(p1.size());
    for (unsigned i = 0; i < p1.size(); i++) {
        for (unsigned j = 0; j < p1[i].size(); j++) {
            T[p1[i][j]] = i;
            y = p1[i][j];
            xxx++;
        }
    }
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
                    p.push_back(S[T[p2[i][j]]]);

                }
                S[T[p2[i][j]]].clear();
            }
        }
    }
    for (unsigned i = 0; i < p1.size(); i++) {
        for (unsigned j = 0; j < p1[i].size(); j++) {
            T[p1[i][j]] = -1;
        }
    }
    return count;
}
