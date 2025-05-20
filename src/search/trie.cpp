#include "trie.h"
#include <algorithm>

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    
    for (char c : word) {
        // Convertir a minúscula y asegurarse de que sea una letra
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        
        if (c < 'a' || c > 'z') {
            continue; // Ignorar caracteres que no son letras
        }
        
        int index = c - 'a';
        if (!current->children[index]) {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    
    current->isEndOfWord = true;
}

bool Trie::search(const std::string& word) {
    TrieNode* current = root;
    
    for (char c : word) {
        // Convertir a minúscula y asegurarse de que sea una letra
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        
        if (c < 'a' || c > 'z') {
            return false; // Caracteres no válidos
        }
        
        int index = c - 'a';
        if (!current->children[index]) {
            return false;
        }
        current = current->children[index];
    }
    
    return current->isEndOfWord;
}

bool Trie::startsWith(const std::string& prefix) {
    TrieNode* current = root;
    
    for (char c : prefix) {
        // Convertir a minúscula y asegurarse de que sea una letra
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        
        if (c < 'a' || c > 'z') {
            return false; // Caracteres no válidos
        }
        
        int index = c - 'a';
        if (!current->children[index]) {
            return false;
        }
        current = current->children[index];
    }
    
    return true;
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    std::vector<std::string> result;
    TrieNode* current = root;
    
    // Navegar hasta el nodo que representa el prefijo
    for (char c : prefix) {
        // Convertir a minúscula y asegurarse de que sea una letra
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        
        if (c < 'a' || c > 'z') {
            return result; // Prefijo contiene caracteres no válidos
        }
        
        int index = c - 'a';
        if (!current->children[index]) {
            return result; // Prefijo no encontrado
        }
        current = current->children[index];
    }
    
    // Recolectar todas las palabras que comienzan con el prefijo
    collectWords(current, prefix, result);
    
    return result;
}

void Trie::collectWords(TrieNode* node, std::string prefix, std::vector<std::string>& result) {
    if (node->isEndOfWord) {
        result.push_back(prefix);
    }
    
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            char c = 'a' + i;
            collectWords(node->children[i], prefix + c, result);
        }
    }
}
