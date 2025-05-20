#include "bst.h"

BST::BST() : root(nullptr), size(0) {}

BST::~BST() {
    destroyRecursive(root);
}

void BST::destroyRecursive(BSTNode* node) {
    if (node) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

void BST::insert(const Song& song) {
    root = insertRecursive(root, song);
    size++;
}

BSTNode* BST::insertRecursive(BSTNode* node, const Song& song) {
    if (!node) {
        return new BSTNode(song);
    }
    
    if (song.id < node->data.id) {
        node->left = insertRecursive(node->left, song);
    } else if (song.id > node->data.id) {
        node->right = insertRecursive(node->right, song);
    } else {
        // Si el ID ya existe, actualizar los datos
        node->data = song;
    }
    
    return node;
}

bool BST::remove(int id) {
    int originalSize = size;
    root = removeRecursive(root, id);
    return size < originalSize;
}

BSTNode* BST::removeRecursive(BSTNode* node, int id) {
    if (!node) {
        return nullptr;
    }
    
    if (id < node->data.id) {
        node->left = removeRecursive(node->left, id);
    } else if (id > node->data.id) {
        node->right = removeRecursive(node->right, id);
    } else {
        // Nodo encontrado, proceder a eliminarlo
        
        // Caso 1: Nodo hoja (sin hijos)
        if (!node->left && !node->right) {
            delete node;
            size--;
            return nullptr;
        }
        
        // Caso 2: Nodo con un solo hijo
        if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            size--;
            return temp;
        }
        
        if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            size--;
            return temp;
        }
        
        // Caso 3: Nodo con dos hijos
        // Encontrar el sucesor inorden (el más pequeño en el subárbol derecho)
        BSTNode* temp = findMin(node->right);
        
        // Copiar los datos del sucesor al nodo actual
        node->data = temp->data;
        
        // Eliminar el sucesor
        node->right = removeRecursive(node->right, temp->data.id);
    }
    
    return node;
}

BSTNode* BST::findMin(BSTNode* node) {
    BSTNode* current = node;
    
    while (current && current->left) {
        current = current->left;
    }
    
    return current;
}

Song* BST::search(int id) {
    BSTNode* result = searchRecursive(root, id);
    return result ? &(result->data) : nullptr;
}

BSTNode* BST::searchRecursive(BSTNode* node, int id) {
    if (!node || node->data.id == id) {
        return node;
    }
    
    if (id < node->data.id) {
        return searchRecursive(node->left, id);
    }
    
    return searchRecursive(node->right, id);
}

std::vector<Song> BST::inOrderTraversal() {
    std::vector<Song> result;
    inOrderTraversalRecursive(root, result);
    return result;
}

void BST::inOrderTraversalRecursive(BSTNode* node, std::vector<Song>& result) {
    if (node) {
        inOrderTraversalRecursive(node->left, result);
        result.push_back(node->data);
        inOrderTraversalRecursive(node->right, result);
    }
}
