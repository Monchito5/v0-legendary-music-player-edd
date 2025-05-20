#include "heap.h"
#include <algorithm>

Heap::Heap() : size(0) {
    // Comparador por defecto: min-heap por playCount (menor primero)
    comparator = [](const Song& a, const Song& b) {
        return a.playCount < b.playCount;
    };
}

void Heap::setComparator(std::function<bool(const Song&, const Song&)> comp) {
    comparator = comp;
    
    // Reconstruir el heap con el nuevo comparador
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

bool Heap::insert(const Song& song) {
    if (isFull()) {
        return false;
    }
    
    data[size] = song;
    heapifyUp(size);
    size++;
    
    return true;
}

bool Heap::extractTop(Song& song) {
    if (isEmpty()) {
        return false;
    }
    
    song = data[0];
    data[0] = data[size - 1];
    size--;
    
    if (size > 0) {
        heapifyDown(0);
    }
    
    return true;
}

bool Heap::peek(Song& song) const {
    if (isEmpty()) {
        return false;
    }
    
    song = data[0];
    return true;
}

void Heap::heapifyUp(int index) {
    while (index > 0) {
        int p = parent(index);
        
        if (comparator(data[index], data[p])) {
            std::swap(data[index], data[p]);
            index = p;
        } else {
            break;
        }
    }
}

void Heap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < size && comparator(data[left], data[smallest])) {
        smallest = left;
    }
    
    if (right < size && comparator(data[right], data[smallest])) {
        smallest = right;
    }
    
    if (smallest != index) {
        std::swap(data[index], data[smallest]);
        heapifyDown(smallest);
    }
}
