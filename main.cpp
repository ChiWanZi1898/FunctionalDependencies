#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

class Preprocessor {
public:
    Preprocessor(string filePath, unsigned long colNum);

    int getData(vector<vector<int>> &data);

private:
    int parseLine(vector<unsigned> &parsed, const string &line, vector<unordered_map<string, unsigned>> &metElementSet,
                  vector<unsigned> &maxIndex);

    string filePath; // path to data file
    unsigned long colNum;
};

int Preprocessor::getData(vector<vector<int>> &data) {
    ifstream dataFile(filePath);
    string line;
    vector<unordered_map<string, unsigned>> metElementSet(colNum, unordered_map<string, unsigned>());
    vector<unsigned> maxIndex(colNum, 0);
    vector<unsigned> parsed(colNum, 0);
    if (dataFile.is_open()) {
        int rowCount = 0;
        while (getline(dataFile, line)) {
            parseLine(parsed, line, metElementSet, maxIndex);
//            for (int j = 0; j < colNum; j++) {
//                cout << parsed[j] << " ";
//            }
//            cout << endl;
        }
        cout << "finished" << endl;
        dataFile.close();
        return rowCount;
    }
    return -1;
}

int Preprocessor::parseLine(vector<unsigned> &parsed, const string &line,
                            vector<unordered_map<string, unsigned>> &metElementSet,
                            vector<unsigned> &maxIndex) {
    // split line by ","(a comma) but not by ", "(a comma and a space)
    // and transform each element to an unsigned int.
    unsigned lastPos = 0;
    unsigned pos = 0;
    unsigned len = line.length();
    string elem;
    for (int i = 0; i < colNum - 1; i++) {
        while (line[pos] != ',' || (pos + 1 < len && line[pos + 1] == ' ')) {
            pos++;
        }
        elem = line.substr(lastPos, pos - lastPos);
        lastPos = pos + 1;
        auto got = metElementSet[i].find(elem);
        if (got == metElementSet[i].end()) {
            maxIndex[i]++;
            metElementSet[i].insert({elem, maxIndex[i]});
            parsed[i] = maxIndex[i];
        } else {
            parsed[i] = got->second;
        }
    }
    elem = line.substr(lastPos, len - lastPos);
    lastPos = pos + 1;
    auto got = metElementSet[colNum - 1].find(elem);
    if (got == metElementSet[colNum - 1].end()) {
        maxIndex[colNum - 1]++;
        metElementSet[colNum - 1].insert({elem, maxIndex[colNum - 1]});
        parsed[colNum - 1] = maxIndex[colNum - 1];
    } else {
        parsed[colNum - 1] = got->second;
    }
    return 0;
}

Preprocessor::Preprocessor(string filePath, unsigned long colNum) : filePath(std::move(filePath)), colNum(colNum) {

}

int main() {
    unsigned long rowNum = 150000; // estimated number of row
    unsigned long colNum = 15; // [exact] number of column
    string filePath = "/Users/aglax/Desktop/test_data.txt";
    vector<vector<int>> data;
    data.reserve(rowNum);
    Preprocessor prep(filePath, colNum);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    prep.getData(data);
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() <<std::endl;
    
    return 0;
}