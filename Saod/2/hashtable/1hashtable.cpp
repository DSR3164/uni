#include <iostream>
#include <vector>
#include <sys/time.h>
#include "hashtable.h"
#include <iomanip>
#include <cstdint>

using namespace std;

int main() {
    uint32_t max_n = 200000; // Максимальное число элементов n
    HashTable hashtab;

    // Инициализация хеш-таблицы
    hashtab_init(hashtab, max_n);

    // Вывод заголовка таблицы
    cout << "Количество элементов в словаре\tВремя выполнения функции hashtab_lookup, с" << endl;

    // Измерение времени выполнения операции поиска для каждого n
    for (uint32_t i = 1; i <= max_n; ++i) {
        string word = "word_" + to_string(i);

        // Заполнение хеш-таблицы
        hashtab_add(hashtab, word, i);

        // Если i кратно 10000, измеряем время выполнения операции поиска
        if (i % 10000 == 0) {
            double t_hash = wtime();
            hashtab_lookup(hashtab, word);
            t_hash = wtime() - t_hash;

            // Вывод количества элементов и времени выполнения
            cout << "n=" << setw(7) << left << i << "time=" << setw(9) << left  << fixed << setprecision(9) << t_hash<< endl;
        }
    }

    return 0;
}
