#include "HashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable() {
    table.resize(TABLE_SIZE);
    elementCount = 0;
}

int HashTable::hashFunction(const string& key) const {
    unsigned long hash = 0;
    for (char c : key) {
        hash = (hash * 31 + static_cast<unsigned char>(c)) % TABLE_SIZE;
    }
    return static_cast<int>(hash);
}

void HashTable::insert(const Resource& r) {
    if (search(r.getID()) != nullptr) {
        cout << "Resource with ID \"" << r.getID() << "\" already exists in Hash Table.\n";
        return;
    }
    int index = hashFunction(r.getID());
    table[index].push_back(r);
    elementCount++;
}

Resource* HashTable::search(const string& id) {
    int index = hashFunction(id);
    for (Resource& res : table[index]) {
        if (res.getID() == id) {
            return &res;
        }
    }
    return nullptr;
}

bool HashTable::remove(const string& id) {
    int index = hashFunction(id);
    auto& chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->getID() == id) {
            chain.erase(it);
            elementCount--;
            return true;
        }
    }
    return false;
}

void HashTable::display() const {
    cout << "\n========== Hash Table Contents ==========\n";
    bool empty = true;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[i].empty()) {
            empty = false;
            cout << "Bucket [" << i << "] (" << table[i].size() << " items):\n";
            for (const Resource& r : table[i]) {
                cout << "   ";
                // Resource::display is non-const in Student A's version, so we copy
                Resource temp = r;
                temp.display();
            }
            cout << "----------------------------------------\n";
        }
    }
    if (empty) cout << "Hash Table is empty.\n";
    cout << "Total elements : " << elementCount << endl;
    cout << "Load Factor    : " << loadFactor() << endl;
    cout << "=========================================\n";
}

double HashTable::loadFactor() const {
    return static_cast<double>(elementCount) / TABLE_SIZE;
}

int HashTable::getSize() const {
    return elementCount;
}
