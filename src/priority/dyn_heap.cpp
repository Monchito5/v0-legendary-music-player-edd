#include "dyn_heap.h"
#include <algorithm>

DynHeap::DynHeap() {
    // Comparador por defecto: min-heap por playCount (menor primero)
    comparator = [](const Song& a, const Song& b) {
        return a.playCount < b.playCount;
    };
}

void DynHeap::setComparator(std::function<bool(const Song&, const Song&)> comp) {
    comparator = comp;
    
    // Reconstruir el heap con el nuevo comparador
    for (int i = data.size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

void DynHeap::insert(const Song& song) {
    data.push_back(song);
    heapifyUp(data.size() - 1);
}

bool DynHeap::extractTop(Song& song) {
    if (isEmpty()) {
        return false;
    }
    
    song = data[0];
    data[0] = data.back();
    data.pop_back();
    
    if (!data.empty()) {
        heapifyDown(0);
    }
    
    return true;
}

bool DynHeap::peek(Song& song) const {
    if (isEmpty()) {
        return false;
    }
    
    song = data[0];
    return true;
}

void DynHeap::heapifyUp(int index) {
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

void DynHeap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < data.size() && comparator(data[left], data[smallest])) {
        smallest = left;
    }
    
    if (right < data.size() && comparator(data[right], data[smallest])) {
        smallest = right;
    }
    
    if (smallest != index) {
        std::swap(data[index], data[smallest]);
        heapifyDown(smallest);
    }
}
