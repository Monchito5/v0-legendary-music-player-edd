/**
 * @file Busqueda.h
 * @brief Implementación de algoritmos de búsqueda desde cero
 * @author v0
 * @date Mayo 2025
 */

#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include "../estructuras/Lista.h"

/**
 * @brief Clase con métodos estáticos para algoritmos de búsqueda
 * @tparam T Tipo de dato a buscar
 */
template <typename T>
class Busqueda {
public:
    /**
     * @brief Realiza una búsqueda lineal en una lista
     * @param lista Lista donde buscar
     * @param valor Valor a buscar
     * @return Índice del elemento encontrado o -1 si no se encuentra
     */
    static int busquedaLineal(const Lista<T>& lista, const T& valor) {
        int tamano = lista.obtenerTamano();
        
        for (int i = 0; i < tamano; i++) {
            T actual;
            lista.obtener(i, actual);
            
            if (actual == valor) {
                return i;
            }
        }
        
        return -1;
    }
    
    /**
     * @brief Realiza una búsqueda binaria en una lista ordenada
     * @param lista Lista ordenada donde buscar
     * @param valor Valor a buscar
     * @param ascendente true si la lista está ordenada ascendentemente, false si está descendentemente
     * @return Índice del elemento encontrado o -1 si no se encuentra
     */
    static int busquedaBinaria(const Lista<T>& lista, const T& valor, bool ascendente = true) {
        int inicio = 0;
        int fin = lista.obtenerTamano() - 1;
        
        while (inicio <= fin) {
            int medio = inicio + (fin - inicio) / 2;
            T valorMedio;
            lista.obtener(medio, valorMedio);
            
            // Si el elemento está presente en el medio
            if (valorMedio == valor) {
                return medio;
            }
            
            if (ascendente) {
                // Si el valor es mayor, ignorar la mitad izquierda
                if (valorMedio < valor) {
                    inicio = medio + 1;
                }
                // Si el valor es menor, ignorar la mitad derecha
                else {
                    fin = medio - 1;
                }
            } else {
                // Si el valor es menor, ignorar la mitad izquierda (para orden descendente)
                if (valorMedio > valor) {
                    inicio = medio + 1;
                }
                // Si el valor es mayor, ignorar la mitad derecha (para orden descendente)
                else {
                    fin = medio - 1;
                }
            }
        }
        
        // Elemento no encontrado
        return -1;
    }
    
    /**
     * @brief Realiza una búsqueda por criterio en una lista
     * @param lista Lista donde buscar
     * @param criterio Función que evalúa si un elemento cumple con el criterio
     * @return Lista con los índices de los elementos que cumplen el criterio
     */
    static Lista<int> busquedaPorCriterio(const Lista<T>& lista, bool (*criterio)(const T&)) {
        Lista<int> resultados;
        int tamano = lista.obtenerTamano();
        
        for (int i = 0; i < tamano; i++) {
            T actual;
            lista.obtener(i, actual);
            
            if (criterio(actual)) {
                resultados.agregar(i);
            }
        }
        
        return resultados;
    }
};

#endif // BUSQUEDA_H
