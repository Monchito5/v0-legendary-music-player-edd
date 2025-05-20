#ifndef PILA_H
#define PILA_H

#include <stdexcept>

template <typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& _dato) : dato(_dato), siguiente(nullptr) {}
    };

    Nodo* cima_;
    int tamanio;

public:
    // Constructor
    Pila() : cima_(nullptr), tamanio(0) {}

    // Destructor
    ~Pila() {
        vaciar();
    }

    // Apilar elemento
    void apilar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);
        nuevo->siguiente = cima_;
        cima_ = nuevo;
        tamanio++;
    }

    // Desapilar elemento
    bool desapilar() {
        if (estaVacia()) {
            return false;
        }

        Nodo* temp = cima_;
        cima_ = cima_->siguiente;
        delete temp;
        tamanio--;
        return true;
    }

    // Obtener elemento en la cima
    T cima() const {
        if (estaVacia()) {
            throw std::out_of_range("La pila está vacía");
        }
        return cima_->dato;
    }

    // Verificar si la pila está vacía
    bool estaVacia() const {
        return tamanio == 0;
    }

    // Obtener tamaño de la pila
    int obtenerTamanio() const {
        return tamanio;
    }

    // Vaciar la pila
    void vaciar() {
        while (!estaVacia()) {
            desapilar();
        }
    }
};

#endif // PILA_H
