#include <cstring>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <chrono>

using namespace std;

class bstree {
public:
    char* key;
    uint32_t value;
    bstree *left, *right;

    bstree(const string& key, uint32_t value) : key(nullptr), value(value), left(nullptr), right(nullptr) {
        this->key = new char[key.length() + 1];
        strcpy(this->key, key.c_str());
    }

    ~bstree() {
        delete[] key;
    }

    void bstree_add(bstree*& tree, const string& key, uint32_t value) {
        bstree* parent = nullptr;
        bstree* current = tree;

        while (current != nullptr) {
            parent = current;

            if (!key.empty() && strcmp(key.c_str(), current->key) < 0) {
                current = current->left;
            }
            else if (strcmp(key.c_str(), current->key) > 0)
                current = current->right;
            else {
                current->value = value;
                return;
            }
        }

        bstree* newNode = new bstree(key, value);

        if (parent == nullptr)
            tree = newNode;
        else if (strcmp(key.c_str(), parent->key) < 0)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    bstree* bstree_delete(bstree*& tree, const string& key) {
        if (tree == nullptr) {
            return nullptr;
        }

        if (strcmp(key.c_str(), tree->key) < 0) {
            tree->left = bstree_delete(tree->left, key);
        } else if (strcmp(key.c_str(), tree->key) > 0) {
            tree->right = bstree_delete(tree->right, key);
        } else {
            if (tree->left == nullptr && tree->right == nullptr) {
                delete tree;
                tree = nullptr;
            } else if (tree->left == nullptr) {
                bstree* temp = tree;
                tree = tree->right;
                delete temp;
            } else if (tree->right == nullptr) {
                bstree* temp = tree;
                tree = tree->left;
                delete temp;
            } else {
                bstree* min_right_subtree = tree_min(tree->right);
                delete[] tree->key;
                tree->key = new char[strlen(min_right_subtree->key) + 1];
                strcpy(tree->key, min_right_subtree->key);
                tree->value = min_right_subtree->value;
                tree->right = bstree_delete(tree->right, min_right_subtree->key);
            }
        }

        return tree;
    }

    bstree* bstree_lookup(bstree* tree, const std::string& key) {
        while (tree != nullptr) {
            int comparison = strcmp(key.c_str(), tree->key);

            if (comparison > 0)
                tree = tree->right;
            else if (comparison < 0)
                tree = tree->left;
            else
                return tree;
        }

        return nullptr;
    }

    bstree* tree_min(bstree* tree) {
        while (tree->left != nullptr) {
            tree = tree->left;
        }

        return tree;
    }
    bstree* tree_max(bstree* tree){
        while(tree->right != nullptr){
            tree = tree->right;
        }

        return tree;
    }
};

int getrand(int min, int max) {
    return min + rand() % (max - min + 1);
}
double wtime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}