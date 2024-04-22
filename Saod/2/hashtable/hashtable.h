#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <cstdint>
#include "../RandTime.h"

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
    newNode->next = hashtab[index];
    hashtab[index] = newNode;
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


uint32_t kr_hash(const string& key, uint32_t table_size) {
    uint32_t hashval = 0;
    for (char c : key) {
        hashval = (hashval << 5) + c;
    }
    return hashval % table_size;
}

uint32_t djb_hash(const string& key, uint32_t table_size) {
    uint32_t hashval = 5381;
    for (char c : key) {
        hashval = ((hashval << 5) + hashval) + c;
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
    if (hashtab[index] != nullptr) {
        collisions++;
    }
    else {
        ListNode* currentNode = hashtab[index];
        while (currentNode != nullptr) {
            if (currentNode->key == key) {
                collisions++; // Увеличиваем счетчик коллизий, если хеш совпал с существующим ключом
                break;
            }
            currentNode = currentNode->next;
        }
    }

    // Вставка нового элемента в хеш-таблицу
    ListNode* newNode = new ListNode(key, value);
    newNode->next = hashtab[index];
    hashtab[index] = newNode;
}

uint32_t count_collisions(const HashTable& hashtab) {
    uint32_t collisions = 0;
    for (const auto& node : hashtab) {
        ListNode* current = node;
        while (current != nullptr) {
            if (current->next != nullptr) {
                collisions++;
            }
            current = current->next;
        }
    }
    return collisions;
}
