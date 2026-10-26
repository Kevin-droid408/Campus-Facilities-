#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Resource.h"
#include <string>
#include <vector>
#include <iostream>

// ============================================================
// Hash Table with Separate Chaining
// Adapted to Student A's Resource (uses getID())
// Table size 101 (prime), polynomial rolling hash
// ============================================================

const int TABLE_SIZE = 101;

class HashTable {
private:
    std::vector<std::vector<Resource>> table;
    int elementCount;

    int hashFunction(const std::string& key) const;

public:
    HashTable();
    ~HashTable() = default;

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void insert(const Resource& r);
    Resource* search(const std::string& id);
    bool remove(const std::string& id);

    void display() const;
    double loadFactor() const;
    int getSize() const;
};

#endif
