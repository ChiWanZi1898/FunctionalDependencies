//
// Created by Hongyu Zhu on 2018/5/18.
//

#include "ResultWriter.h"

ResultWriter::ResultWriter(string outputPath) : outputPath(outputPath), results(vector<vector<unsigned>>()) {
    results.reserve(600);
}

void ResultWriter::add(Attrs &lefts, unsigned right) {
    results.emplace_back();
    for (unsigned i = 0; i < MAX_COL_NUM; i++) {
        if (lefts[i])
            results.back().push_back(i + 1);
    }
    results.back().push_back(right + 1);
}


void ResultWriter::write() {

    sort(results.begin(), results.end(), [](const vector<unsigned> &lhs, const vector<unsigned> &rhs) {
        auto len = min(lhs.size(), rhs.size());
        for(int i = 0; i < len; i++) {
            if(lhs[i] == rhs[i])
                continue;
            return lhs[i] < rhs[i];
        }
        return lhs.size() < rhs.size();
    });
    ofstream outputFile(outputPath);
    if (outputFile.is_open()) {
        for (int i = 0; i < results.size(); i++) {
            for (int j = 0; j < results[i].size() - 1; j++) {
                outputFile << results[i][j] << " ";
            }
            outputFile << "-> " << results[i].back() << endl;
        }
    }
    outputFile.close();
}
