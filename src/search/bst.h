#ifndef BST_H
#define BST_H

#include "../models/song.h"
#include <vector>

// Nodo del BST
struct BSTNode {
    Song data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const Song& song) : data(song), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;
    int size;
    
    // Métodos auxiliares recursivos
    BSTNode* insertRecursive(BSTNode* node, const Song& song);
    BSTNode* removeRecursive(BSTNode* node, int id);
    BSTNode* findMin(BSTNode* node);
    BSTNode* searchRecursive(BSTNode* node, int id);
    void inOrderTraversalRecursive(BSTNode* node, std::vector<Song>& result);
    void destroyRecursive(BSTNode* node);

public:
    // Constructor y destructor
    BST();
    ~BST();
    
    // Métodos básicos
    void insert(const Song& song);
    bool remove(int id);
    Song* search(int id);
    
    // Recorridos
    std::vector<Song> inOrderTraversal();
    
    // Getters
    int getSize() const { return size; }
    bool isEmpty() const { return root == nullptr; }
};

#endif // BST_H
