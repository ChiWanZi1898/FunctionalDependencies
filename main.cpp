#include <bitset>
#include "Preprocessor.h"
#include "constants.h"
#include "tane.h"
#include "StrippedProductCalculator.h"
#include "ResultWriter.h"

using namespace std;

int main() {
    unsigned long rowNum = 100000; // estimated number of row
//    unsigned long colNum = 12; // [exact] number of column
    string filePath;
    cout << "Please insert data path: " << endl;
    cin >> filePath;
//    if (filePath.length() == 0)
//        filePath = "/Users/aglax/Desktop/data.txt";
    string outputPath;
    cout << "Please insert result path: " << endl;
    cin >> outputPath;
//    if (outputPath.length() == 0)
//        outputPath = "/Users/aglax/Desktop/result.txt";
    vector<vector<unsigned>> data;
    data.reserve(MAX_COL_NUM);
    Preprocessor prep(filePath, MAX_COL_NUM);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    rowNum = prep.getData(data);


//    // ===== DEBUG ======
//    for(auto row: data) {
//        for(auto elem: row) {
//            cout << elem << " ";
//        }
//        cout << endl;
//    }
//    // ==== DEBUGEND ====

    vector<unordered_map<Attrs, Attrs>> cPlusMaps(MAX_COL_NUM + 1);
    vector<vector<Attrs>> Ls(MAX_COL_NUM + 1, vector<Attrs >());
    vector<vector<vector<vector<unsigned>>>> partitionsList(MAX_COL_NUM + 1);
    vector<vector<unsigned>> partitionTotalsList(MAX_COL_NUM + 1);
    vector<vector<unsigned>> partitionCountsList(MAX_COL_NUM + 1);
    vector<vector<bool>> isKey(MAX_COL_NUM + 1);
    vector<unordered_map<Attrs, unsigned>> attrPartitionMaps(MAX_COL_NUM + 1);

    Ls[0].emplace_back(Attrs(0));
    cPlusMaps[0].insert({Attrs(0), Attrs(0).set()});
    prepareL1(Ls[1]);
    computeInitPartition(partitionsList[1], partitionTotalsList[1], partitionCountsList[1], isKey[1],
                         attrPartitionMaps[1], data);
    partitionCountsList[0].push_back(0);
    partitionTotalsList[0].push_back(rowNum);
    attrPartitionMaps[0].insert({Attrs(0), 0});

    StrippedProductCalculator cal(rowNum);
    ResultWriter outWriter(outputPath);

    int level = 1;
    while (level <= MAX_COL_NUM && Ls[level].size() > 0) {
        computeDependencies(Ls[level], cPlusMaps[level - 1], cPlusMaps[level], partitionTotalsList,
                            partitionCountsList, attrPartitionMaps, outWriter);
        prune(Ls[level], cPlusMaps[level], isKey[level], outWriter);
        generateNextLevel(Ls, level, partitionsList, attrPartitionMaps, partitionTotalsList, partitionCountsList, isKey,
                          cal);
        level++;
    }

    outWriter.write();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time consumption = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1e9
              << std::endl;
    return 0;
}