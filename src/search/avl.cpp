#include "avl.h"
#include <algorithm>

AVL::AVL() : root(nullptr), size(0) {
    // Comparador por defecto: ordenar por ID
    comparator = [](const Song& a, const Song& b) {
        return a.id < b.id;
    };
}

AVL::~AVL() {
    destroyRecursive(root);
}

void AVL::destroyRecursive(AVLNode* node) {
    if (node) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

void AVL::setComparator(std::function<bool(const Song&, const Song&)> comp) {
    comparator = comp;
    
    // Reconstruir el árbol con el nuevo comparador
    std::vector<Song> songs = inOrderTraversal();
    destroyRecursive(root);
    root = nullptr;
    size = 0;
    
    for (const auto& song : songs) {
        insert(song);
    }
}

int AVL::getHeight(AVLNode* node) {
    if (!node) {
        return 0;
    }
    return node->height;
}

int AVL::getBalanceFactor(AVLNode* node) {
    if (!node) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* AVL::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // Realizar rotación
    x->right = y;
    y->left = T2;
    
    // Actualizar alturas
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

AVLNode* AVL::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // Realizar rotación
    y->left = x;
    x->right = T2;
    
    // Actualizar alturas
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

void AVL::insert(const Song& song) {
    root = insertRecursive(root, song);
    size++;
}

AVLNode* AVL::insertRecursive(AVLNode* node, const Song& song) {
    // Paso 1: Inserción BST normal
    if (!node) {
        return new AVLNode(song);
    }
    
    if (song.id == node->data.id) {
        // Si el ID ya existe, actualizar los datos
        node->data = song;
        return node;
    }
    
    if (comparator(song, node->data)) {
        node->left = insertRecursive(node->left, song);
    } else {
        node->right = insertRecursive(node->right, song);
    }
    
    // Paso 2: Actualizar altura del nodo actual
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    
    // Paso 3: Obtener el factor de balance
    int balance = getBalanceFactor(node);
    
    // Paso 4: Si el nodo está desbalanceado, hay 4 casos
    
    // Caso Izquierda-Izquierda
    if (balance > 1 && comparator(song, node->left->data)) {
        return rightRotate(node);
    }
    
    // Caso Derecha-Derecha
    if (balance < -1 && !comparator(song, node->right->data)) {
        return leftRotate(node);
    }
    
    // Caso Izquierda-Derecha
    if (balance > 1 && !comparator(song, node->left->data)) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Caso Derecha-Izquierda
    if (balance < -1 && comparator(song, node->right->data)) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // Nodo balanceado
    return node;
}

bool AVL::remove(int id) {
    int originalSize = size;
    root = removeRecursive(root, id);
    return size < originalSize;
}

AVLNode* AVL::removeRecursive(AVLNode* node, int id) {
    if (!node) {
        return nullptr;
    }
    
    // Paso 1: Eliminación BST normal
    if (id < node->data.id) {
        node->left = removeRecursive(node->left, id);
    } else if (id > node->data.id) {
        node->right = removeRecursive(node->right, id);
    } else {
        // Nodo encontrado, proceder a eliminarlo
        
        // Caso 1: Nodo hoja o con un solo hijo
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            
            // Sin hijos
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                // Un hijo
                *node = *temp;
            }
            
            delete temp;
            size--;
        } else {
            // Caso 2: Nodo con dos hijos
            // Encontrar el sucesor inorden (el más pequeño en el subárbol derecho)
            AVLNode* temp = findMin(node->right);
            
            // Copiar los datos del sucesor al nodo actual
            node->data = temp->data;
            
            // Eliminar el sucesor
            node->right = removeRecursive(node->right, temp->data.id);
        }
    }
    
    // Si el árbol tenía solo un nodo, retornar
    if (!node) {
        return nullptr;
    }
    
    // Paso 2: Actualizar altura del nodo actual
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    
    // Paso 3: Obtener el factor de balance
    int balance = getBalanceFactor(node);
    
    // Paso 4: Si el nodo está desbalanceado, hay 4 casos
    
    // Caso Izquierda-Izquierda
    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        return rightRotate(node);
    }
    
    // Caso Izquierda-Derecha
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Caso Derecha-Derecha
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        return leftRotate(node);
    }
    
    // Caso Derecha-Izquierda
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

AVLNode* AVL::findMin(AVLNode* node) {
    AVLNode* current = node;
    
    while (current && current->left) {
        current = current->left;
    }
    
    return current;
}

Song* AVL::search(int id) {
    AVLNode* result = searchRecursive(root, id);
    return result ? &(result->data) : nullptr;
}

AVLNode* AVL::searchRecursive(AVLNode* node, int id) {
    if (!node || node->data.id == id) {
        return node;
    }
    
    if (id < node->data.id) {
        return searchRecursive(node->left, id);
    }
    
    return searchRecursive(node->right, id);
}

std::vector<Song> AVL::inOrderTraversal() {
    std::vector<Song> result;
    inOrderTraversalRecursive(root, result);
    return result;
}

void AVL::inOrderTraversalRecursive(AVLNode* node, std::vector<Song>& result) {
    if (node) {
        inOrderTraversalRecursive(node->left, result);
        result.push_back(node->data);
        inOrderTraversalRecursive(node->right, result);
    }
}
