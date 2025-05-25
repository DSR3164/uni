#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;
using namespace chrono;

class TreeMerger {
private:
    vector<pair<int, int>> nodes;
    vector<vector<int>> dataArrays;
    vector<int> progress;
    int numNodes;

    void constructTree() {
        for (int i = numNodes - 1; i > 0; --i) {
            nodes[i] = choose(nodes[2 * i], nodes[2 * i + 1]);
        }
    }

    pair<int, int> choose(const pair<int, int> &a, const pair<int, int> &b) {
        return (a.first <= b.first) ? a : b;
    }

    void refreshTree(int idx) {
        int pos = (idx + numNodes) / 2;
        while (pos > 0) {
            nodes[pos] = choose(nodes[2 * pos], nodes[2 * pos + 1]);
            pos /= 2;
        }
    }

public:
    TreeMerger(const vector<vector<int>> &arrays) {
        dataArrays = arrays;
        numNodes = arrays.size();
        progress.resize(numNodes, 0);

        nodes.resize(2 * numNodes, {INT_MAX, -1});
        for (int i = 0; i < numNodes; ++i) {
            if (!dataArrays[i].empty()) {
                nodes[numNodes + i] = {dataArrays[i][0], i};
            }
        }
        constructTree();
    }

    pair<int, int> topNode() const {
        return nodes[1];
    }

    void popNode() {
        auto [val, arrIdx] = topNode();
        if (arrIdx != -1) {
            progress[arrIdx]++;
            if (progress[arrIdx] < dataArrays[arrIdx].size()) {
                nodes[numNodes + arrIdx] = {dataArrays[arrIdx][progress[arrIdx]], arrIdx};
            } else {
                nodes[numNodes + arrIdx] = {INT_MAX, -1};
            }
            refreshTree(arrIdx);
        }
    }

    vector<int> combine() {
        vector<int> merged;
        while (topNode().first != INT_MAX) {
            merged.push_back(topNode().first);
            popNode();
        }
        return merged;
    }
};

vector<vector<int>> createDataArrays(int groupCount, int groupSize) {
    vector<vector<int>> data(groupCount);
    for (int i = 0; i < groupCount; ++i) {
        data[i].resize(groupSize);
        for (int j = 0; j < groupSize; ++j) {
            data[i][j] = rand() % 100000;
        }
        sort(data[i].begin(), data[i].end());
    }
    return data;
}

void logResults(const vector<pair<pair<int, int>, pair<double, double>>> &timings, const string &filename) {
    ofstream outputFile(filename, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error: Cannot open file for writing.\n";
        return;
    }
    outputFile << "NumOfArrays\tArraySize\tWinnerTree(s)\tMinHeap(s)\n";
    for (const auto &entry : timings) {
        outputFile << entry.first.first << "\t"<< entry.first.second << "\t" << entry.second.first << "\t" << entry.second.second << "\n";
    }
    outputFile.close();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<pair<int, int>> testCases = {
        {10, 10000}, {20, 10000}, {30, 10000}, {40, 10000}, {50, 10000}, {60, 10000}, {70, 10000}, {80, 10000}, {90, 10000}
    }; 

    vector<pair<pair<int, int>, pair<double, double>>> timingResults;

    for (auto [arrays, size] : testCases) {
        vector<vector<int>> dataGroups = createDataArrays(arrays, size);

        auto start = high_resolution_clock::now();
        TreeMerger merger(dataGroups);
        vector<int> mergedTree = merger.combine();
        auto end = high_resolution_clock::now();
        double treeTime = duration_cast<microseconds>(end - start).count() / 1e6;

        start = high_resolution_clock::now();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        vector<int> positions(arrays, 0);

        for (int i = 0; i < arrays; ++i) {
            if (!dataGroups[i].empty()) {
                minHeap.emplace(dataGroups[i][0], i);
            }
        }

        vector<int> heapMerged;
        while (!minHeap.empty()) {
            auto [val, idx] = minHeap.top();
            minHeap.pop();
            heapMerged.push_back(val);

            if (++positions[idx] < dataGroups[idx].size()) {
                minHeap.emplace(dataGroups[idx][positions[idx]], idx);
            }
        }
        end = high_resolution_clock::now();
        double heapTime = duration_cast<microseconds>(end - start).count() / 1e6;

        timingResults.emplace_back(make_pair(arrays, size), make_pair(treeTime, heapTime));
    }

    logResults(timingResults, "First.txt");

    cout << "Process completed. Results are stored in First.txt\n";
    return 0;
}
