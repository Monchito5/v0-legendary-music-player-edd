#ifndef DYN_HEAP_H
#define DYN_HEAP_H

#include "../models/song.h"
#include <vector>
#include <functional>

class DynHeap {
private:
    std::vector<Song> data;
    std::function<bool(const Song&, const Song&)> comparator;
    
    // Métodos auxiliares
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

public:
    // Constructor
    DynHeap();
    
    // Configuración del comparador
    void setComparator(std::function<bool(const Song&, const Song&)> comp);
    
    // Métodos básicos
    void insert(const Song& song);
    bool extractTop(Song& song);
    bool peek(Song& song) const;
    bool isEmpty() const { return data.empty(); }
    void clear() { data.clear(); }
    
    // Getter
    int getSize() const { return data.size(); }
};

#endif // DYN_HEAP_H
