#include "history_stack.h"

HistoryStack::HistoryStack() : top(-1) {}

bool HistoryStack::push(const Song& song) {
    if (isFull()) {
        // Si la pila está llena, desplazar todos los elementos una posición
        for (int i = 0; i < MAX_HIST - 1; i++) {
            history[i] = history[i + 1];
        }
        history[MAX_HIST - 1] = song;
        return true;
    }
    
    history[++top] = song;
    return true;
}

bool HistoryStack::pop(Song& song) {
    if (isEmpty()) {
        return false;
    }
    
    song = history[top--];
    return true;
}

bool HistoryStack::peek(Song& song) const {
    if (isEmpty()) {
        return false;
    }
    
    song = history[top];
    return true;
}

bool HistoryStack::isEmpty() const {
    return top == -1;
}

bool HistoryStack::isFull() const {
    return top == MAX_HIST - 1;
}

void HistoryStack::clear() {
    top = -1;
}
