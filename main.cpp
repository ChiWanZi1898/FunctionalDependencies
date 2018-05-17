#include <bitset>
#include "Preprocessor.h"
#include "constants.h"
#include "tane.h"
using namespace std;



void prune() {

}

void generateNextLevel() {

}

void computeCPlus(unordered_map<unsigned, unsigned> lastCPlusSet) {

}

int main() {
    unsigned long rowNum = 100000; // estimated number of row
    unsigned long colNum = 15; // [exact] number of column
    string filePath = "/Users/aglax/Desktop/data.txt";
    vector<vector<unsigned>> data;
    data.reserve(rowNum);
    Preprocessor prep(filePath, colNum);

//    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    prep.getData(data);
//    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
//    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1e9 <<std::endl;

//    // ===== DEBUG ======
//    for(auto row: data) {
//        for(auto elem: row) {
//            cout << elem << " ";
//        }
//        cout << endl;
//    }
//    // ==== DEBUGEND ====

    vector<unordered_map<Attrs, Attrs>> cPlusMaps(colNum+1);
    vector<vector<Attrs>> Ls(colNum+1, vector<Attrs>());
    vector<unordered_map<Attrs, vector<vector<unsigned>>>> partitionMaps;
    Ls[0].push_back(Attrs(0));
    cPlusMaps[0].insert({Ls[0][0], Attrs().set()});
    partitionMaps.push_back(unordered_map<Attrs, vector<vector<unsigned>>>());
    computeInitPartition(partitionMaps[0], data);
    int level = 1;
    while(Ls[level].size() > 0) {

    }
    return 0;
}