#ifndef DYN_QUEUE_H
#define DYN_QUEUE_H

#include "../models/song.h"

// Nodo para la cola dinámica
struct QueueNode {
    Song song;
    QueueNode* next;
    
    QueueNode(const Song& s) : song(s), next(nullptr) {}
};

class DynQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int size;

public:
    // Constructor y destructor
    DynQueue();
    ~DynQueue();
    
    // Métodos básicos de cola
    void enqueue(const Song& song);
    bool dequeue(Song& song);
    bool peek(Song& song) const;
    bool isEmpty() const;
    void clear();
    
    // Getter
    int getSize() const { return size; }
};

#endif // DYN_QUEUE_H
