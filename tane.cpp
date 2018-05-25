//
// Created by Hongyu Zhu on 2018/5/16.
//


#include "tane.h"

void computeDependencies(vector<Attrs > &L, unordered_map<Attrs, Attrs > &lastCPlus,
                         unordered_map<Attrs, Attrs > &currCPlus, const vector<vector<unsigned>> &partitionTotalsList,
                         const vector<vector<unsigned>> &partitionCountsList,
                         const vector<unordered_map<Attrs, unsigned>> &attrPartitionMaps,
                         ResultWriter &outWriter) {
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
                Attrs tmp = x;
                tmp.reset(i);
                if (validDependency(partitionTotalsList, partitionCountsList, attrPartitionMaps, tmp, x)) {
//                    for (int j = 0; j < MAX_COL_NUM; j++)
//                        if (tmp[j]) {
//
//                            cout << j + 1 << " ";
//                        }
//                    cout << "-> " << i + 1 << endl;
                    outWriter.add(tmp, i);
                    got->second.reset(i);
                    got->second &= x;
                }
            }
        }
    }
}

void computeInitPartition(vector<vector<vector<unsigned>>> &partitions,
                          vector<unsigned> &partitionTotals,
                          vector<unsigned> &partitionCounts,
                          vector<bool> &isKey,
                          unordered_map<Attrs, unsigned> &attrPartitionMap,
                          const vector<vector<unsigned>> &data) {
    unsigned rowNum = data.size();
    if (rowNum == 0)
        return;
    vector<unordered_map<unsigned, unsigned>> attrMaps(MAX_COL_NUM);
    vector<unsigned> maxPartitionIndex(MAX_COL_NUM, 0);
    vector<vector<vector<unsigned>>> rawPartitions(MAX_COL_NUM);
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < MAX_COL_NUM; j++) {
            auto got = attrMaps[j].find(data[i][j]);
            if (got == attrMaps[j].end()) {
                attrMaps[j].insert({data[i][j], maxPartitionIndex[j]});
                rawPartitions[j].push_back(vector<unsigned>());
                rawPartitions[j][maxPartitionIndex[j]].push_back(i);
                maxPartitionIndex[j]++;
            } else {
                rawPartitions[j][got->second].push_back(i);
            }
        }
    }
    for (int i = 0; i < MAX_COL_NUM; i++) {
        unsigned count = 0;
        partitions.push_back(vector<vector<unsigned>>());
        for (int j = 0; j < rawPartitions[i].size(); j++) {
            if (rawPartitions[i][j].size() >= 2) {
                count += rawPartitions[i][j].size();
                partitions[i].push_back(rawPartitions[i][j]);
            }
        }
        partitionCounts.push_back(partitions[i].size());
        partitionTotals.push_back(count);
        if (count)
            isKey.push_back(false);
        else
            isKey.push_back(true);
    }
    for (unsigned i = 0; i < MAX_COL_NUM; i++) {
        bitset<MAX_COL_NUM> attr(0);
        attr.set(i);
        attrPartitionMap.insert({attr, i});

    }
}


void computePrefixBlocks(vector<Attrs > &L, vector<vector<Attrs>> &prefixBlocks) {
    unordered_map<Attrs, unsigned> blockMap;
    int index = 0;

    for (int i = 0; i < L.size(); i++) {
        Attrs prefix = L[i];
        getPrefixAttr(prefix);
        auto got = blockMap.find(prefix);
        if (got == blockMap.end()) {
            blockMap.insert({prefix, index});
            prefixBlocks.emplace_back(vector<Attrs >());
            prefixBlocks[index].push_back(L[i]);
            index++;
        } else {
            prefixBlocks[got->second].push_back(L[i]);
        }
    }
}

void getPrefixAttr(Attrs &a) {
    for (int i = MAX_COL_NUM - 1; i >= 0; i--) {
        if (a[i]) {
            a[i] = false;
            break;
        }
    }

}

void prepareL1(vector<Attrs > &L) {
    for (int i = 0; i < MAX_COL_NUM; i++) {
        L.emplace_back(Attrs(0).set(i));
    }
}

void generateNextLevel(vector<vector<Attrs>> &Ls,
                       int level,
                       vector<vector<vector<vector<unsigned>>>> &partitionsList,
                       vector<unordered_map<Attrs, unsigned>> &attrPartitionMaps,
                       vector<vector<unsigned>> &partitionTotalsList,
                       vector<vector<unsigned>> &partitionCountsList,
                       vector<vector<bool>> &isKey,
                       StrippedProductCalculator &cal) {
    vector<vector<Attrs>> prefixBlocks;
    computePrefixBlocks(Ls[level], prefixBlocks);
    for (const auto &prefixBlock : prefixBlocks) {
        for (int i = 0; i < prefixBlock.size(); i++) {
            for (int j = i + 1; j < prefixBlock.size(); j++) {
                Attrs comAttr = prefixBlock[i] | prefixBlock[j];
                bool allFound = true;
                for (int k = 0; k < MAX_COL_NUM; k++) {
                    if (comAttr[k]) {
                        comAttr.reset(k);
                        auto got = find(Ls[level].begin(), Ls[level].end(), comAttr);
                        if (got == Ls[level].end()) {
                            allFound = false;
                            break;
                        }
                        comAttr.set(k);
                    }
                }
                if (allFound) {
                    Ls[level + 1].emplace_back(comAttr);
                    auto index = partitionsList[level + 1].size();
                    partitionsList[level + 1].emplace_back(vector<vector<unsigned>>());
                    attrPartitionMaps[level + 1].insert({comAttr, index});
                    Attrs z(1);
                    Attrs w(16);
                    if (prefixBlock[i] == z && prefixBlock[j] == w) {
                        int x;
                    }

                    unsigned total = cal.strippedProduct(
                            prefixBlock[i],
                            prefixBlock[j],
                            partitionsList[level][attrPartitionMaps[level].find(prefixBlock[i])->second],
                            partitionsList[level][attrPartitionMaps[level].find(prefixBlock[j])->second],
                            partitionsList[level + 1][index]);
                    partitionTotalsList[level + 1].push_back(total);
                    partitionCountsList[level + 1].push_back(partitionsList[level + 1][index].size());
                    if (total)
                        isKey[level + 1].push_back(false);
                    else
                        isKey[level + 1].push_back(true);
                }
            }
        }
    }
}

bool validDependency(const vector<vector<unsigned>> &partitionTotalsList,
                     const vector<vector<unsigned>> &partitionCountsList,
                     const vector<unordered_map<Attrs, unsigned>> &attrPartitionMaps,
                     const Attrs &x_a, const Attrs &x) {
    unsigned level = x.count();
    auto gotX_a = attrPartitionMaps[level - 1].find(x_a);
    auto gotX = attrPartitionMaps[level].find(x);
    auto eX_a = partitionTotalsList[level - 1][gotX_a->second] - partitionCountsList[level - 1][gotX_a->second];
    auto l = partitionTotalsList[level].size();
    auto eX = partitionTotalsList[level][gotX->second] - partitionCountsList[level][gotX->second];
    if (eX_a == eX)
        return true;
    else
        return false;
}

void prune(vector<Attrs > &L, unordered_map<Attrs, Attrs > &CPlus, vector<bool> &isKey, ResultWriter &outWriter) {
    int idx = 0;
    while (!L.empty() && idx < L.size()) {
        auto got = CPlus.find(L[idx]);
        if (got->second.none()) {
            quickDelete<Attrs >(idx, L);
            quickDelete<bool>(idx, isKey);
            continue;
        } else {
            idx++;
        }
//        if(isKey[idx]) {
//            Attrs a = got->second ^ (got->second & L[idx]);
//            for(int i = 0; i < MAX_COL_NUM; i++) {
//                if(a[i]) {
//                    Attrs comb;
//                    Attrs xxx = L[idx];
//                    comb.set();
//
//                    for(int j = 0; j < MAX_COL_NUM; j++) {
//                        if(L[idx][j]) {
//                            Attrs tmp = L[idx];
//                            tmp.set(i);
//                            tmp.reset(j);
//                            auto got2 = CPlus.find(tmp);
//                            if(got2 == CPlus.end()) {
//                                comb.reset();
//                                break;
//                            }
//                            comb &= got2->second;
//
//                        }
//                    }
//                    if(comb[i]) {
//                        outWriter.add(L[idx], i);
////                        for (int j = 0; j < MAX_COL_NUM; j++)
////                            if (L[idx][j]) {
////                                cout << j + 1 << " ";
////                            }
////                        cout << "-> " << i + 1 << endl;
//                    }
//                }
//            }
//            quickDelete<Attrs>(idx, L);
//            quickDelete<bool>(idx, isKey);
//        }
    }
}

template<typename T>
void quickDelete(int idx, vector<T> &vec) {
    vec[idx] = vec.back();
    vec.pop_back();
}

