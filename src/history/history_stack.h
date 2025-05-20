#ifndef HISTORY_STACK_H
#define HISTORY_STACK_H

#include "../models/song.h"

class HistoryStack {
private:
    Song history[MAX_HIST];
    int top;

public:
    // Constructor
    HistoryStack();
    
    // Métodos básicos de pila
    bool push(const Song& song);
    bool pop(Song& song);
    bool peek(Song& song) const;
    bool isEmpty() const;
    bool isFull() const;
    void clear();
    
    // Getter
    int getSize() const { return top + 1; }
};

#endif // HISTORY_STACK_H
