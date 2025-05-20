#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "../models/song.h"

class CircularQueue {
private:
    Song queue[MAX_Q];
    int front;
    int rear;
    int count;

public:
    // Constructor
    CircularQueue();
    
    // Métodos básicos de cola
    bool enqueue(const Song& song);
    bool dequeue(Song& song);
    bool peek(Song& song) const;
    bool isEmpty() const;
    bool isFull() const;
    void clear();
    
    // Getter
    int getSize() const { return count; }
    
    // Acceso a elementos específicos (para visualización)
    bool getSongAt(int index, Song& song) const;
};

#endif // CIRCULAR_QUEUE_H
