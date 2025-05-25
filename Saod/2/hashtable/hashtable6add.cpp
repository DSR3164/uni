#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include "hashtable.h"

using namespace std;

int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    HashTable hashtab_kr, hashtab_add;
    uint32_t table_size = 200000;

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    
    hashtab_init(hashtab_kr, table_size); // Инициализация хэш-таблицы для kr
    hashtab_init(hashtab_add, table_size); // Инициализация хэш-таблицы для fnv
        uint32_t collisions_kr = 0, collisions_fnv = 0;
    for (int i = 0; i < 200000; ++i) {
    choosehashtab_add(hashtab_kr, words[i], i, kr_hash, collisions_kr); // Добавление слова в хэш-таблицу для kr
    choosehashtab_add(hashtab_add, words[i], i, fnv, collisions_fnv); // Добавление слова в хэш-таблицу для fnv
    if ((i + 1) % 10000 == 0) {
        string w;
        if (i > 0) {
            w = words[getrand(0, i - 1)];
        } else {
            w = words[0];
        }

        double t_kr = 0.0, t_fnv = 0.0;

        t_kr = measure_time(hashtab_kr, w, kr_hash); // Измерение времени для kr_hash
        t_fnv = measure_time(hashtab_add, w, fnv); // Измерение времени для fnv

        // Выводим значения коллизий для каждой хэш-функции
        cout << i + 1 << "\t\t\t" << t_kr << "\t\t\t" << collisions_kr << "\t\t\t" << t_fnv << "\t\t\t" << collisions_fnv << endl;
    }
}


    return 0;
}