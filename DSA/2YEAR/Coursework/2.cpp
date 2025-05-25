#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

using namespace std;
using namespace chrono;

class TournamentTree
{
private:
    vector<int> nodes;
    int capacity;

    void initializeTree()
    {
        for (int i = capacity - 1; i > 0; --i)
        {
            nodes[i] = min(nodes[2 * i], nodes[2 * i + 1]);
        }
    }

    void refreshTree(int index)
    {
        int current = (index + capacity) / 2;
        while (current > 0)
        {
            nodes[current] = min(nodes[2 * current], nodes[2 * current + 1]);
            current /= 2;
        }
    }

public:
    TournamentTree(const vector<int> &elements)
    {
        capacity = elements.size();
        nodes.resize(2 * capacity);
        for (int i = 0; i < capacity; ++i)
        {
            nodes[capacity + i] = elements[i];
        }
        initializeTree();
    }

    int getChampion() const
    {
        return nodes[1];
    }

    void eliminateChampion()
    {
        int champion = getChampion();
        for (int i = 0; i < capacity; ++i)
        {
            if (nodes[capacity + i] == champion)
            {
                nodes[capacity + i] = numeric_limits<int>::max();
                refreshTree(i);
                break;
            }
        }
    }

    void processAllRounds()
    {
        for (int i = 0; i < capacity; ++i)
        {
            eliminateChampion();
        }
    }
};

vector<int> createRandomDataset(int count)
{
    vector<int> dataset(count);
    for (int i = 0; i < count; ++i)
    {
        dataset[i] = rand() % 100000;
    }
    return dataset;
}

void writeResultsToFile(const vector<pair<int, pair<double, double>>> &data, const string &filePath)
{
    ofstream output(filePath);
    if (!output.is_open())
    {
        cerr << "Error: Unable to open file for writing!\n";
        return;
    }
    output << "ArraySize\tWinnerTree(s)\tMinHeap(s)\n";
    for (const auto &entry : data)
    {
        output << entry.first << "\t" << entry.second.first << "\t" << entry.second.second << "\n";
    }
    output.close();
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    vector<int> datasetSizes = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 16384, 65536, 100000};
    vector<pair<int, pair<double, double>>> performanceMetrics;

    for (int size : datasetSizes)
    {
        vector<int> dataset = createRandomDataset(size);

        auto startTime = high_resolution_clock::now();
        TournamentTree tree(dataset);
        tree.processAllRounds();
        auto endTime = high_resolution_clock::now();
        double treeDuration = duration_cast<microseconds>(endTime - startTime).count() / 1e6;

        startTime = high_resolution_clock::now();
        priority_queue<int, vector<int>, greater<>> heap(dataset.begin(), dataset.end());
        while (!heap.empty())
        {
            heap.pop();
        }
        endTime = high_resolution_clock::now();
        double heapDuration = duration_cast<microseconds>(endTime - startTime).count() / 1e6;

        performanceMetrics.emplace_back(size, make_pair(treeDuration, heapDuration));
    }

    writeResultsToFile(performanceMetrics, "Second.txt");

    cout << "Benchmarking completed. Results saved in Second.txt\n";
    return 0;
}
