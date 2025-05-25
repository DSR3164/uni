#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include "bstree.h"
#include "iomanip"

using namespace std;

int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    bstree* tree = nullptr;

    for (int i = 1; i <= 200000; ++i) {
        if(tree == nullptr) {
            tree = new bstree(words[i - 1], i - 1);
        } else {
            tree->bstree_add(tree, words[i - 1], i - 1);
        }

        if (i % 10000 == 0) {
            string w = words[getrand(0, i - 1)];

            // Измерение времени выполнения функции add
            double tAdd = wtime();
            tree->bstree_add(tree, w, i);
            tAdd = wtime() - tAdd;

            cout << setw(7) << left << i << setw(10) << left << fixed << setprecision(7) << left << tAdd << endl;
        }
    }

    return 0;
}
