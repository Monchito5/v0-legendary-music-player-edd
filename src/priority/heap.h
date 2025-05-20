#ifndef HEAP_H
#define HEAP_H

#include "../models/song.h"
#include <functional>

const int MAX_HEAP = 100;

class Heap {
private:
    Song data[MAX_HEAP];
    int size;
    std::function<bool(const Song&, const Song&)> comparator;
    
    // Métodos auxiliares
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

public:
    // Constructor
    Heap();
    
    // Configuración del comparador
    void setComparator(std::function<bool(const Song&, const Song&)> comp);
    
    // Métodos básicos
    bool insert(const Song& song);
    bool extractTop(Song& song);
    bool peek(Song& song) const;
    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == MAX_HEAP; }
    void clear() { size = 0; }
    
    // Getter
    int getSize() const { return size; }
};

#endif // HEAP_H
