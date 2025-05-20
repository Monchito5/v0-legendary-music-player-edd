#ifndef LISTA_H
#define LISTA_H

#include <stdexcept>

template <typename T>
class Lista {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& _dato) : dato(_dato), siguiente(nullptr) {}
    };

    Nodo* primero;
    Nodo* ultimo;
    int tamanio;

public:
    // Clase iterador para recorrer la lista
    class Iterador {
    private:
        Nodo* actual;

    public:
        Iterador(Nodo* _actual = nullptr) : actual(_actual) {}

        T& operator*() {
            if (actual == nullptr) {
                throw std::runtime_error("Iterador inválido");
            }
            return actual->dato;
        }

        const T& operator*() const {
            if (actual == nullptr) {
                throw std::runtime_error("Iterador inválido");
            }
            return actual->dato;
        }

        Iterador& operator++() {
            if (actual != nullptr) {
                actual = actual->siguiente;
            }
            return *this;
        }

        bool operator==(const Iterador& otro) const {
            return actual == otro.actual;
        }

        bool operator!=(const Iterador& otro) const {
            return actual != otro.actual;
        }
    };

    // Clase iterador constante para recorrer la lista sin modificarla
    class IteradorConst {
    private:
        const Nodo* actual;

    public:
        IteradorConst(const Nodo* _actual = nullptr) : actual(_actual) {}

        const T& operator*() const {
            if (actual == nullptr) {
                throw std::runtime_error("Iterador inválido");
            }
            return actual->dato;
        }

        IteradorConst& operator++() {
            if (actual != nullptr) {
                actual = actual->siguiente;
            }
            return *this;
        }

        bool operator==(const IteradorConst& otro) const {
            return actual == otro.actual;
        }

        bool operator!=(const IteradorConst& otro) const {
            return actual != otro.actual;
        }
    };

    // Constructor
    Lista() : primero(nullptr), ultimo(nullptr), tamanio(0) {}

    // Constructor de copia
    Lista(const Lista& otra) : primero(nullptr), ultimo(nullptr), tamanio(0) {
        Nodo* actual = otra.primero;
        while (actual != nullptr) {
            agregar(actual->dato);
            actual = actual->siguiente;
        }
    }

    // Operador de asignación
    Lista& operator=(const Lista& otra) {
        if (this != &otra) {
            vaciar();

            Nodo* actual = otra.primero;
            while (actual != nullptr) {
                agregar(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;
    }

    // Destructor
    ~Lista() {
        vaciar();
    }

    // Agregar elemento al final
    void agregar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);

        if (primero == nullptr) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }

        tamanio++;
    }

    // Insertar elemento en una posición específica
    bool insertar(int indice, const T& elemento) {
        if (indice < 0 || indice > tamanio) {
            return false;
        }

        if (indice == 0) {
            Nodo* nuevo = new Nodo(elemento);
            nuevo->siguiente = primero;
            primero = nuevo;

            if (ultimo == nullptr) {
                ultimo = nuevo;
            }

            tamanio++;
            return true;
        }

        if (indice == tamanio) {
            agregar(elemento);
            return true;
        }

        Nodo* actual = primero;
        for (int i = 0; i < indice - 1; i++) {
            actual = actual->siguiente;
        }

        Nodo* nuevo = new Nodo(elemento);
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;

        tamanio++;
        return true;
    }

    // Eliminar elemento en una posición específica
    bool eliminar(int indice) {
        if (indice < 0 || indice >= tamanio || primero == nullptr) {
            return false;
        }

        Nodo* aEliminar;

        if (indice == 0) {
            aEliminar = primero;
            primero = primero->siguiente;

            if (primero == nullptr) {
                ultimo = nullptr;
            }
        } else {
            Nodo* actual = primero;
            for (int i = 0; i < indice - 1; i++) {
                actual = actual->siguiente;
            }

            aEliminar = actual->siguiente;
            actual->siguiente = aEliminar->siguiente;

            if (aEliminar == ultimo) {
                ultimo = actual;
            }
        }

        delete aEliminar;
        tamanio--;
        return true;
    }

    // Modificar elemento en una posición específica
    bool modificar(int indice, const T& elemento) {
        if (indice < 0 || indice >= tamanio) {
            return false;
        }

        Nodo* actual = primero;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }

        actual->dato = elemento;
        return true;
    }

    // Obtener elemento en una posición específica
    T obtener(int indice) const {
        if (indice < 0 || indice >= tamanio) {
            throw std::out_of_range("Índice fuera de rango");
        }

        Nodo* actual = primero;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }

        return actual->dato;
    }

    // Buscar índice de un elemento
    int buscar(const T& elemento) const {
        Nodo* actual = primero;
        int indice = 0;

        while (actual != nullptr) {
            if (actual->dato == elemento) {
                return indice;
            }

            actual = actual->siguiente;
            indice++;
        }

        return -1;
    }

    // Verificar si la lista contiene un elemento
    bool contiene(const T& elemento) const {
        return buscar(elemento) != -1;
    }

    // Obtener tamaño de la lista
    int obtenerTamanio() const {
        return tamanio;
    }

    // Verificar si la lista está vacía
    bool estaVacia() const {
        return tamanio == 0;
    }

    // Vaciar la lista
    void vaciar() {
        while (primero != nullptr) {
            Nodo* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }

        ultimo = nullptr;
        tamanio = 0;
    }

    // Iteradores
    Iterador inicio() {
        return Iterador(primero);
    }

    Iterador fin() {
        return Iterador(nullptr);
    }

    // Iteradores constantes
    IteradorConst inicio() const {
        return IteradorConst(primero);
    }

    IteradorConst fin() const {
        return IteradorConst(nullptr);
    }
};

#endif // LISTA_H
