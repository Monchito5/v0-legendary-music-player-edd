#include "dyn_queue.h"

DynQueue::DynQueue() : front(nullptr), rear(nullptr), size(0) {}

DynQueue::~DynQueue() {
    clear();
}

void DynQueue::enqueue(const Song& song) {
    QueueNode* newNode = new QueueNode(song);
    
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    
    size++;
}

bool DynQueue::dequeue(Song& song) {
    if (isEmpty()) {
        return false;
    }
    
    QueueNode* temp = front;
    song = temp->song;
    
    front = front->next;
    delete temp;
    
    // Si la cola queda vacía, actualizar rear
    if (front == nullptr) {
        rear = nullptr;
    }
    
    size--;
    return true;
}

bool DynQueue::peek(Song& song) const {
    if (isEmpty()) {
        return false;
    }
    
    song = front->song;
    return true;
}

bool DynQueue::isEmpty() const {
    return front == nullptr;
}

void DynQueue::clear() {
    while (!isEmpty()) {
        Song dummy;
        dequeue(dummy);
    }
}
