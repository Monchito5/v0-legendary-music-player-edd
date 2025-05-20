#include "circular_queue.h"

CircularQueue::CircularQueue() : front(0), rear(-1), count(0) {}

bool CircularQueue::enqueue(const Song& song) {
    if (isFull()) {
        return false;
    }
    
    rear = (rear + 1) % MAX_Q;
    queue[rear] = song;
    count++;
    
    return true;
}

bool CircularQueue::dequeue(Song& song) {
    if (isEmpty()) {
        return false;
    }
    
    song = queue[front];
    front = (front + 1) % MAX_Q;
    count--;
    
    return true;
}

bool CircularQueue::peek(Song& song) const {
    if (isEmpty()) {
        return false;
    }
    
    song = queue[front];
    return true;
}

bool CircularQueue::isEmpty() const {
    return count == 0;
}

bool CircularQueue::isFull() const {
    return count == MAX_Q;
}

void CircularQueue::clear() {
    front = 0;
    rear = -1;
    count = 0;
}

bool CircularQueue::getSongAt(int index, Song& song) const {
    if (index < 0 || index >= count) {
        return false;
    }
    
    int position = (front + index) % MAX_Q;
    song = queue[position];
    
    return true;
}
