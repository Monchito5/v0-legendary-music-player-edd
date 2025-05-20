#include "hash_table.h"

HashTable::HashTable() : size(0) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
}

unsigned int HashTable::hash(const std::string& key) {
    unsigned int hashValue = 0;
    
    for (char c : key) {
        hashValue = (hashValue * 31) + c;
    }
    
    return hashValue % TABLE_SIZE;
}

void HashTable::insert(const std::string& key, Song* song) {
    unsigned int index = hash(key);
    
    // Buscar si la clave ya existe
    HashNode* current = table[index];
    while (current) {
        if (current->key == key) {
            // Actualizar el valor si la clave ya existe
            current->song = song;
            return;
        }
        current = current->next;
    }
    
    // Crear un nuevo nodo
    HashNode* newNode = new HashNode(key, song);
    
    // Insertar al principio de la lista
    newNode->next = table[index];
    table[index] = newNode;
    size++;
}

Song* HashTable::search(const std::string& key) {
    unsigned int index = hash(key);
    
    HashNode* current = table[index];
    while (current) {
        if (current->key == key) {
            return current->song;
        }
        current = current->next;
    }
    
    return nullptr;
}

bool HashTable::remove(const std::string& key) {
    unsigned int index = hash(key);
    
    HashNode* current = table[index];
    HashNode* prev = nullptr;
    
    while (current) {
        if (current->key == key) {
            // Eliminar el nodo
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            
            delete current;
            size--;
            return true;
        }
        
        prev = current;
        current = current->next;
    }
    
    return false;
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = table[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
    size = 0;
}

std::vector<std::string> HashTable::getKeys() {
    std::vector<std::string> keys;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = table[i];
        while (current) {
            keys.push_back(current->key);
            current = current->next;
        }
    }
    
    return keys;
}
