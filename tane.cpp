//
// Created by Hongyu Zhu on 2018/5/16.
//


#include "tane.h"

void
computeDependencies(vector<Attrs > &L, unordered_map<Attrs, Attrs > &lastCPlus,
                    unordered_map<Attrs, Attrs > &currCPlus) {
    for (auto &x : L) {
        Attrs newC;
        newC.set();
        for (int i = 0; i < MAX_COL_NUM; i++) {
            if (x[i]) {
                x[i] = false;
                auto got = lastCPlus.find(x);
                newC &= got->second;
                x[i] = true;
            }
        }
        currCPlus.insert({x, newC});
    }

    for (auto &x : L) {
        auto got = currCPlus.find(x);
        Attrs interXC = x & got->second;
        for (int i = 0; i < MAX_COL_NUM; i++) {
            if (interXC[i]) {

            }

        }
    }

}

//void initSingleton(vector<vector<vector<unsigned>>> &partitionMap) {
//    for (int i = 0; i < MAX_COL_NUM; i++) {
//        bitset<MAX_COL_NUM> attr(0);
//        attr.set(i);
//        partitionMap.insert({attr, vector<vector<unsigned>>()});
//    }
//}

void computeInitPartition(unordered_map<Attrs, vector<vector<unsigned>>> &partitionMap,
                          const vector<vector<unsigned>> &data) {
    unsigned rowNum = data.size();
    if (rowNum == 0)
        return;
    vector<unordered_map<unsigned, unsigned>> attrMaps(MAX_COL_NUM);
    vector<unsigned> maxPartitionIndex(MAX_COL_NUM, 0);
    vector<vector<vector<unsigned>>> partitions(MAX_COL_NUM);
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < MAX_COL_NUM; j++) {
            auto got = attrMaps[j].find(data[i][j]);
            if (got == attrMaps[j].end()) {
                attrMaps[j].insert({data[i][j], maxPartitionIndex[j]});
                partitions[j].push_back(vector<unsigned>());
                partitions[j][maxPartitionIndex[j]].push_back(i);
                maxPartitionIndex[j]++;
            } else {
                partitions[j][got->second].push_back(i);
            }
        }
    }
    vector<vector<vector<unsigned>>> strippedPartitions(MAX_COL_NUM);
    for(int i = 0; i < MAX_COL_NUM; )
    for(unsigned i = 0; i < MAX_COL_NUM; i++) {
        bitset<MAX_COL_NUM> attr(0);
        attr.set(i);
        partitionMap.insert({attr, partitions[i]});
    }
}


void strippedProduct() {

}

