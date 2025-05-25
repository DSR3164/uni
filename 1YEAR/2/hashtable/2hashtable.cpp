#include <iostream>
#include <fstream>
#include <vector>
#include "iomanip"
#include "hashtable.h"

using namespace std;

int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    HashTable hashtab;
    uint32_t table_size = 200000;

    hashtab_init(hashtab, table_size);

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    for (int i = 0; i < 200000; ++i) {
        double tAdd = wtime();
        hashtab_add(hashtab, words[i], i);
        tAdd = wtime() - tAdd;

        if ((i + 1) % 10000 == 0)
            cout << setw(10) << left << i + 1 << setw(10) << left << fixed << setprecision(12) << tAdd << endl;
    }

    return 0;
}
