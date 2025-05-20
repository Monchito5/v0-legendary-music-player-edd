/**
 * @file Cola.h
 * @brief Implementación de una cola genérica desde cero
 * @author v0
 * @date Mayo 2025
 */

#ifndef COLA_H
#define COLA_H

#include <iostream>

/**
 * @brief Nodo para la cola
 * @tparam T Tipo de dato a almacenar
 */
template <typename T>
struct NodoCola {
    T dato;                 ///< Dato almacenado en el nodo
    NodoCola<T>* siguiente; ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param _dato Dato a almacenar
     */
    NodoCola(const T& _dato) : dato(_dato), siguiente(nullptr) {}
};

/**
 * @brief Cola genérica implementada con nodos enlazados
 * @tparam T Tipo de dato a almacenar
 */
template <typename T>
class Cola {
private:
    NodoCola<T>* frente;    ///< Puntero al primer elemento
    NodoCola<T>* final;     ///< Puntero al último elemento
    int tamano;             ///< Cantidad de elementos en la cola

public:
    /**
     * @brief Constructor por defecto
     */
    Cola() : frente(nullptr), final(nullptr), tamano(0) {}
    
    /**
     * @brief Destructor
     */
    ~Cola() {
        vaciar();
    }
    
    /**
     * @brief Agrega un elemento al final de la cola
     * @param dato Elemento a agregar
     */
    void encolar(const T& dato) {
        NodoCola<T>* nuevo = new NodoCola<T>(dato);
        
        if (estaVacia()) {
            frente = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        
        tamano++;
    }
    
    /**
     * @brief Elimina el elemento del frente de la cola
     * @return true si se desencoló correctamente, false si la cola está vacía
     */
    bool desencolar() {
        if (estaVacia()) {
            return false;
        }
        
        NodoCola<T>* temp = frente;
        frente = frente->siguiente;
        
        if (frente == nullptr) {
            final = nullptr;
        }
        
        delete temp;
        tamano--;
        return true;
    }
    
    /**
     * @brief Obtiene el elemento del frente sin eliminarlo
     * @param resultado Variable donde se almacenará el resultado
     * @return true si se obtuvo correctamente, false si la cola está vacía
     */
    bool frenteCola(T& resultado) const {
        if (estaVacia()) {
            return false;
        }
        
        resultado = frente->dato;
        return true;
    }
    
    /**
     * @brief Verifica si la cola está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const {
        return tamano == 0;
    }
    
    /**
     * @brief Obtiene el tamaño de la cola
     * @return Cantidad de elementos en la cola
     */
    int obtenerTamano() const {
        return tamano;
    }
    
    /**
     * @brief Vacía la cola liberando toda la memoria
     */
    void vaciar() {
        while (!estaVacia()) {
            desencolar();
        }
    }
};

#endif // COLA_H
