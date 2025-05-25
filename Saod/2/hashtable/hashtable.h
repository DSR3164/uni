#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <chrono>

using namespace std;

struct ListNode {
    string key;
    uint32_t value;
    ListNode* next;

    ListNode(const string& k, uint32_t v) : key(k), value(v), next(nullptr) {}
};

using HashTable = vector<ListNode*>;

uint32_t hashtab_hash(const string& key, uint32_t table_size) {
    uint32_t hashval = 0;
    for (char c : key) {
        hashval = hashval * 37 + c;
    }
    return hashval % table_size;
}

void hashtab_init(HashTable& hashtab, uint32_t table_size) {
    hashtab.resize(table_size, nullptr);
}

void hashtab_add(HashTable& hashtab, const string& key, uint32_t value) {
    uint32_t index = hashtab_hash(key, hashtab.size());
    ListNode* newNode = new ListNode(key, value);
    
    if (hashtab[index] == nullptr) {
        hashtab[index] = newNode;
    } else {
        ListNode* current = hashtab[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}


ListNode* hashtab_lookup(const HashTable& hashtab, const string& key) {
    uint32_t index = hashtab_hash(key, hashtab.size());
    ListNode* currentNode = hashtab[index];
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

void hashtab_delete(HashTable& hashtab, const string& key) {
    uint32_t index = hashtab_hash(key, hashtab.size());
    ListNode* prevNode = nullptr;
    ListNode* currentNode = hashtab[index];
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            if (prevNode == nullptr) {
                hashtab[index] = currentNode->next;
            } else {
                prevNode->next = currentNode->next;
            }
            delete currentNode;
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    cerr << "Element with key '" << key << "' not found for deletion." << endl;
}

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

uint32_t kr_hash(const string& key, uint32_t table_size) {
    uint32_t hashval = 0;
    for (char ch : key) {
        hashval = (hashval * 131) + ch;
    }
    return hashval % table_size;
}

uint32_t fnv(const string& key, uint32_t table_size) {
    const uint32_t fnv_prime = 16777619;
    const uint32_t fnv_offset_basis = 2166136261;
    uint32_t hashval = fnv_offset_basis;
    
    for (char c : key) {
        hashval ^= c;
        hashval *= fnv_prime;
    }
    
    return hashval % table_size;
}
double measure_time(HashTable& hashtab, const string& key, uint32_t (*hash_func)(const string&, uint32_t)) {
    double start_time = wtime();

    hashtab_lookup(hashtab, key);

    return wtime() - start_time;
}


void choosehashtab_add(HashTable& hashtab, const string& key, uint32_t value, uint32_t (*hash_func)(const string&, uint32_t), uint32_t& collisions) {
    uint32_t index = hash_func(key, hashtab.size());

    // Проверяем, пуст ли текущий "бакет" (bucket)
    if (hashtab[index] == nullptr) {
        // Создаем новый узел и добавляем его в "бакет"
        hashtab[index] = new (std::nothrow) ListNode(key, value);
        if (hashtab[index] == nullptr) {
            cerr << "Не удалось выделить память для нового узла." << endl;
            return;
        }
    } else {
        // "Бакет" не пуст, просматриваем связный список, чтобы найти правильную позицию
        ListNode* current = hashtab[index];
        while (current != nullptr) {
            if (current->key == key) {
                // Узел с таким ключом уже существует
                cerr << "Узел с ключом '" << key << "' уже существует." << endl;
                // Увеличиваем счетчик коллизий и возвращаемся
                collisions += 1;
                return;
            }
            current = current->next;
        }
        // Попробуем выделить память для нового узла
        ListNode* newNode = new (std::nothrow) ListNode(key, value);
        if (newNode == nullptr) {
            cerr << "Не удалось выделить память для нового узла." << endl;
            return;
        }
        // Добавляем новый узел в конец связного списка "бакета"
        current = hashtab[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        // Увеличиваем счетчик коллизий, если новый ключ не совпадает с существующими
        collisions += 1;
    }
}
