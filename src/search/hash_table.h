#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../models/song.h"
#include <string>
#include <vector>

// Nodo para la tabla hash
struct HashNode {
    std::string key;
    Song* song;
    HashNode* next;
    
    HashNode(const std::string& k, Song* s) : key(k), song(s), next(nullptr) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 101; // Número primo para mejor distribución
    HashNode* table[TABLE_SIZE];
    int size;
    
    // Función hash
    unsigned int hash(const std::string& key);

public:
    // Constructor y destructor
    HashTable();
    ~HashTable();
    
    // Métodos básicos
    void insert(const std::string& key, Song* song);
    Song* search(const std::string& key);
    bool remove(const std::string& key);
    void clear();
    
    // Getter
    int getSize() const { return size; }
    
    // Obtener todas las claves
    std::vector<std::string> getKeys();
};

#endif // HASH_TABLE_H
