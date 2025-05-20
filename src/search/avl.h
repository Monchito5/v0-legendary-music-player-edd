#ifndef AVL_H
#define AVL_H

#include "../models/song.h"
#include <vector>
#include <functional>

// Nodo del AVL
struct AVLNode {
    Song data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(const Song& song) : data(song), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    AVLNode* root;
    int size;
    std::function<bool(const Song&, const Song&)> comparator;
    
    // Métodos auxiliares
    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    
    // Métodos recursivos
    AVLNode* insertRecursive(AVLNode* node, const Song& song);
    AVLNode* removeRecursive(AVLNode* node, int id);
    AVLNode* findMin(AVLNode* node);
    AVLNode* searchRecursive(AVLNode* node, int id);
    void inOrderTraversalRecursive(AVLNode* node, std::vector<Song>& result);
    void destroyRecursive(AVLNode* node);

public:
    // Constructor y destructor
    AVL();
    ~AVL();
    
    // Configuración del comparador
    void setComparator(std::function<bool(const Song&, const Song&)> comp);
    
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

#endif // AVL_H
