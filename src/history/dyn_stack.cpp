#include "dyn_stack.h"

DynStack::DynStack() : top(nullptr), size(0) {}

DynStack::~DynStack() {
    clear();
}

void DynStack::push(const Song& song) {
    StackNode* newNode = new StackNode(song);
    newNode->next = top;
    top = newNode;
    size++;
}

bool DynStack::pop(Song& song) {
    if (isEmpty()) {
        return false;
    }
    
    StackNode* temp = top;
    song = temp->song;
    top = top->next;
    delete temp;
    size--;
    
    return true;
}

bool DynStack::peek(Song& song) const {
    if (isEmpty()) {
        return false;
    }
    
    song = top->song;
    return true;
}

bool DynStack::isEmpty() const {
    return top == nullptr;
}

void DynStack::clear() {
    while (!isEmpty()) {
        Song dummy;
        pop(dummy);
    }
}
