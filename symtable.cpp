/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #pragma once
#include "symtable.h"

SymEntry* findMin(SymEntry* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
SymEntry* recursiveRemove(SymEntry* node, string k) {
    if (node == nullptr) {
        return nullptr;
    }
    if (k < node->key) {
        node->left = recursiveRemove(node->left, k);
    } else if (k > node->key) {
        node->right = recursiveRemove(node->right, k);
    } else {
        if (node->left == nullptr) {
            SymEntry* temp = node->right;
            delete node->val;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            SymEntry* temp = node->left;
            delete node->val;
            delete node;
            return temp;
        }
        SymEntry* successor = findMin(node->right);
        node->key = successor->key;
        node->val = successor->val;
        node->right = recursiveRemove(node->right, successor->key);
    }

    return node;
}
SymEntry* recursiveSearch(SymEntry* node, string k) {
    if (node == nullptr || node->key == k) {
        return node;
    }

    if (k < node->key) {
        return recursiveSearch(node->left, k);
    }

    return recursiveSearch(node->right, k);
}
SymEntry* recursiveInsert(SymEntry* node, string k, UnlimitedRational* v) {
    if (node == nullptr) {
        return new SymEntry(k, v);
    }
    if (k < node->key) {
        node->left = recursiveInsert(node->left, k, v);
    } else if (k > node->key) {
        node->right = recursiveInsert(node->right, k, v);
    } else {
        delete node->val; 
        node->val = v;
    }

    return node;
}
void recursiveDelete(SymEntry* node) {
    if (node == nullptr) {
        return;
    }
    recursiveDelete(node->left);
    recursiveDelete(node->right);
    delete node;
}
SymbolTable::SymbolTable() {
    size = 0;
    root = nullptr;
}
SymbolTable::~SymbolTable() {
recursiveDelete(root);
    size = 0;
    root = nullptr;

}
void SymbolTable::insert(string k, UnlimitedRational* v) {
    root = recursiveInsert(root, k, v);
    size++;
}
void SymbolTable::remove(string k) {
    root = recursiveRemove(root, k);
    size--;
}
UnlimitedRational* SymbolTable::search(string k) {
    SymEntry* result = recursiveSearch(root, k);
    return (result != nullptr) ? result->val : nullptr;
}
int SymbolTable::get_size() {
    return size;
}
SymEntry* SymbolTable::get_root() {
    return root;
}
