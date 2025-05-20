/**
 * @file Pila.h
 * @brief Implementación de una pila genérica desde cero
 * @author v0
 * @date Mayo 2025
 */

#ifndef PILA_H
#define PILA_H

#include <iostream>

/**
 * @brief Nodo para la pila
 * @tparam T Tipo de dato a almacenar
 */
template <typename T>
struct NodoPila {
    T dato;                 ///< Dato almacenado en el nodo
    NodoPila<T>* siguiente; ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param _dato Dato a almacenar
     */
    NodoPila(const T& _dato) : dato(_dato), siguiente(nullptr) {}
};

/**
 * @brief Pila genérica implementada con nodos enlazados
 * @tparam T Tipo de dato a almacenar
 */
template <typename T>
class Pila {
private:
    NodoPila<T>* cima;      ///< Puntero al nodo superior
    int tamano;             ///< Cantidad de elementos en la pila

public:
    /**
     * @brief Constructor por defecto
     */
    Pila() : cima(nullptr), tamano(0) {}
    
    /**
     * @brief Destructor
     */
    ~Pila() {
        vaciar();
    }
    
    /**
     * @brief Agrega un elemento a la cima de la pila
     * @param dato Elemento a agregar
     */
    void apilar(const T& dato) {
        NodoPila<T>* nuevo = new NodoPila<T>(dato);
        nuevo->siguiente = cima;
        cima = nuevo;
        tamano++;
    }
    
    /**
     * @brief Elimina el elemento de la cima de la pila
     * @return true si se desapiló correctamente, false si la pila está vacía
     */
    bool desapilar() {
        if (estaVacia()) {
            return false;
        }
        
        NodoPila<T>* temp = cima;
        cima = cima->siguiente;
        delete temp;
        tamano--;
        return true;
    }
    
    /**
     * @brief Obtiene el elemento de la cima sin eliminarlo
     * @param resultado Variable donde se almacenará el resultado
     * @return true si se obtuvo correctamente, false si la pila está vacía
     */
    bool cimaPila(T& resultado) const {
        if (estaVacia()) {
            return false;
        }
        
        resultado = cima->dato;
        return true;
    }
    
    /**
     * @brief Verifica si la pila está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const {
        return tamano == 0;
    }
    
    /**
     * @brief Obtiene el tamaño de la pila
     * @return Cantidad de elementos en la pila
     */
    int obtenerTamano() const {
        return tamano;
    }
    
    /**
     * @brief Vacía la pila liberando toda la memoria
     */
    void vaciar() {
        while (!estaVacia()) {
            desapilar();
        }
    }
};

#endif // PILA_H
