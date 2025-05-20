#ifndef COLA_H
#define COLA_H

#include <stdexcept>

template <typename T>
class Cola {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& _dato) : dato(_dato), siguiente(nullptr) {}
    };

    Nodo* frente_;
    Nodo* final_;
    int tamanio;

public:
    // Constructor
    Cola() : frente_(nullptr), final_(nullptr), tamanio(0) {}

    // Destructor
    ~Cola() {
        vaciar();
    }

    // Encolar elemento
    void encolar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);

        if (estaVacia()) {
            frente_ = nuevo;
            final_ = nuevo;
        } else {
            final_->siguiente = nuevo;
            final_ = nuevo;
        }

        tamanio++;
    }

    // Desencolar elemento
    bool desencolar() {
        if (estaVacia()) {
            return false;
        }

        Nodo* temp = frente_;
        frente_ = frente_->siguiente;

        if (frente_ == nullptr) {
            final_ = nullptr;
        }

        delete temp;
        tamanio--;
        return true;
    }

    // Obtener elemento en el frente
    T frente() const {
        if (estaVacia()) {
            throw std::out_of_range("La cola está vacía");
        }
        return frente_->dato;
    }

    // Verificar si la cola está vacía
    bool estaVacia() const {
        return tamanio == 0;
    }

    // Obtener tamaño de la cola
    int obtenerTamanio() const {
        return tamanio;
    }

    // Vaciar la cola
    void vaciar() {
        while (!estaVacia()) {
            desencolar();
        }
    }
};

#endif // COLA_H
