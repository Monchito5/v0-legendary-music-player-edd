#ifndef DYN_STACK_H
#define DYN_STACK_H

#include "../models/song.h"

// Nodo para la pila dinámica
struct StackNode {
    Song song;
    StackNode* next;
    
    StackNode(const Song& s) : song(s), next(nullptr) {}
};

class DynStack {
private:
    StackNode* top;
    int size;

public:
    // Constructor y destructor
    DynStack();
    ~DynStack();
    
    // Métodos básicos de pila
    void push(const Song& song);
    bool pop(Song& song);
    bool peek(Song& song) const;
    bool isEmpty() const;
    void clear();
    
    // Getter
    int getSize() const { return size; }
};

#endif // DYN_STACK_H
