#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

// Nodo del Trie
struct TrieNode {
    bool isEndOfWord;
    TrieNode* children[26]; // Solo letras minúsculas del alfabeto inglés
    
    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
    
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (children[i]) {
                delete children[i];
            }
        }
    }
};

class Trie {
private:
    TrieNode* root;
    
    // Método auxiliar para autocompletado
    void collectWords(TrieNode* node, std::string prefix, std::vector<std::string>& result);

public:
    // Constructor y destructor
    Trie();
    ~Trie();
    
    // Métodos básicos
    void insert(const std::string& word);
    bool search(const std::string& word);
    bool startsWith(const std::string& prefix);
    
    // Autocompletado
    std::vector<std::string> autocomplete(const std::string& prefix);
};

#endif // TRIE_H
