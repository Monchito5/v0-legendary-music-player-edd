/**
 * @file Lista.h
 * @brief Implementación de una lista dinámica genérica desde cero
 * @author v0
 * @date Mayo 2025
 */

#ifndef LISTA_H
#define LISTA_H

#include <iostream>

/**
 * @brief Nodo para la lista dinámica
 * @tparam T Tipo de dato a almacenar
 */
template <typename T>
struct Nodo {
    T dato;                 ///< Dato almacenado en el nodo
    Nodo<T>* siguiente;     ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param _dato Dato a almacenar
     */
    Nodo(const T& _dato) : dato(_dato), siguiente(nullptr) {}
};

/**
 * @brief Lista dinámica genérica
 * @tparam T Tipo de dato a almacenar
 */
template <typename T>
class Lista {
private:
    Nodo<T>* primero;       ///< Puntero al primer nodo
    Nodo<T>* ultimo;        ///< Puntero al último nodo
    int tamano;             ///< Cantidad de elementos en la lista

public:
    /**
     * @brief Constructor por defecto
     */
    Lista() : primero(nullptr), ultimo(nullptr), tamano(0) {}
    
    /**
     * @brief Destructor
     */
    ~Lista() {
        vaciar();
    }
    
    /**
     * @brief Agrega un elemento al final de la lista
     * @param dato Elemento a agregar
     */
    void agregar(const T& dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        
        if (estaVacia()) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        
        tamano++;
    }
    
    /**
     * @brief Inserta un elemento en una posición específica
     * @param dato Elemento a insertar
     * @param posicion Posición donde insertar (0-indexado)
     * @return true si se insertó correctamente, false en caso contrario
     */
    bool insertar(const T& dato, int posicion) {
        if (posicion < 0 || posicion > tamano) {
            return false;
        }
        
        if (posicion == 0) {
            Nodo<T>* nuevo = new Nodo<T>(dato);
            nuevo->siguiente = primero;
            primero = nuevo;
            
            if (tamano == 0) {
                ultimo = nuevo;
            }
            
            tamano++;
            return true;
        }
        
        if (posicion == tamano) {
            agregar(dato);
            return true;
        }
        
        Nodo<T>* actual = primero;
        for (int i = 0; i < posicion - 1; i++) {
            actual = actual->siguiente;
        }
        
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
        
        tamano++;
        return true;
    }
    
    /**
     * @brief Elimina un elemento en una posición específica
     * @param posicion Posición del elemento a eliminar (0-indexado)
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminar(int posicion) {
        if (posicion < 0 || posicion >= tamano || estaVacia()) {
            return false;
        }
        
        Nodo<T>* temp;
        
        if (posicion == 0) {
            temp = primero;
            primero = primero->siguiente;
            
            if (tamano == 1) {
                ultimo = nullptr;
            }
        } else {
            Nodo<T>* actual = primero;
            for (int i = 0; i < posicion - 1; i++) {
                actual = actual->siguiente;
            }
            
            temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            
            if (posicion == tamano - 1) {
                ultimo = actual;
            }
        }
        
        delete temp;
        tamano--;
        return true;
    }
    
    /**
     * @brief Elimina un elemento por valor (primera ocurrencia)
     * @param dato Valor a eliminar
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminarPorValor(const T& dato) {
        if (estaVacia()) {
            return false;
        }
        
        if (primero->dato == dato) {
            Nodo<T>* temp = primero;
            primero = primero->siguiente;
            
            if (tamano == 1) {
                ultimo = nullptr;
            }
            
            delete temp;
            tamano--;
            return true;
        }
        
        Nodo<T>* actual = primero;
        while (actual->siguiente && actual->siguiente->dato != dato) {
            actual = actual->siguiente;
        }
        
        if (!actual->siguiente) {
            return false;
        }
        
        Nodo<T>* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        
        if (temp == ultimo) {
            ultimo = actual;
        }
        
        delete temp;
        tamano--;
        return true;
    }
    
    /**
     * @brief Obtiene el elemento en una posición específica
     * @param posicion Posición del elemento (0-indexado)
     * @param resultado Variable donde se almacenará el resultado
     * @return true si se obtuvo correctamente, false en caso contrario
     */
    bool obtener(int posicion, T& resultado) const {
        if (posicion < 0 || posicion >= tamano || estaVacia()) {
            return false;
        }
        
        Nodo<T>* actual = primero;
        for (int i = 0; i < posicion; i++) {
            actual = actual->siguiente;
        }
        
        resultado = actual->dato;
        return true;
    }
    
    /**
     * @brief Busca un elemento en la lista
     * @param dato Elemento a buscar
     * @return Posición del elemento o -1 si no se encuentra
     */
    int buscar(const T& dato) const {
        if (estaVacia()) {
            return -1;
        }
        
        Nodo<T>* actual = primero;
        int posicion = 0;
        
        while (actual) {
            if (actual->dato == dato) {
                return posicion;
            }
            
            actual = actual->siguiente;
            posicion++;
        }
        
        return -1;
    }
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const {
        return tamano == 0;
    }
    
    /**
     * @brief Obtiene el tamaño de la lista
     * @return Cantidad de elementos en la lista
     */
    int obtenerTamano() const {
        return tamano;
    }
    
    /**
     * @brief Vacía la lista liberando toda la memoria
     */
    void vaciar() {
        while (primero) {
            Nodo<T>* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }
        
        primero = nullptr;
        ultimo = nullptr;
        tamano = 0;
    }
    
    /**
     * @brief Clase iterador para recorrer la lista
     */
    class Iterador {
    private:
        Nodo<T>* actual;
        
    public:
        /**
         * @brief Constructor del iterador
         * @param nodo Nodo inicial
         */
        Iterador(Nodo<T>* nodo) : actual(nodo) {}
        
        /**
         * @brief Avanza al siguiente elemento
         * @return Referencia al iterador
         */
        Iterador& operator++() {
            if (actual) {
                actual = actual->siguiente;
            }
            return *this;
        }
        
        /**
         * @brief Obtiene el dato actual
         * @return Referencia al dato
         */
        T& operator*() {
            return actual->dato;
        }
        
        /**
         * @brief Compara dos iteradores
         * @param otro Iterador a comparar
         * @return true si son diferentes, false en caso contrario
         */
        bool operator!=(const Iterador& otro) const {
            return actual != otro.actual;
        }
    };
    
    /**
     * @brief Obtiene un iterador al inicio de la lista
     * @return Iterador al inicio
     */
    Iterador inicio() {
        return Iterador(primero);
    }
    
    /**
     * @brief Obtiene un iterador al final de la lista
     * @return Iterador al final
     */
    Iterador fin() {
        return Iterador(nullptr);
    }
};

#endif // LISTA_H
