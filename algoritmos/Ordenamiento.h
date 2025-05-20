/**
 * @file Ordenamiento.h
 * @brief Implementación de algoritmos de ordenamiento desde cero
 * @author v0
 * @date Mayo 2025
 */

#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include "../estructuras/Lista.h"

/**
 * @brief Clase con métodos estáticos para algoritmos de ordenamiento
 * @tparam T Tipo de dato a ordenar
 */
template <typename T>
class Ordenamiento {
public:
    /**
     * @brief Ordena una lista utilizando el algoritmo Bubble Sort
     * @param lista Lista a ordenar
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     */
    static void bubbleSort(Lista<T>& lista, bool ascendente = true) {
        int n = lista.obtenerTamano();
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                T actual, siguiente;
                lista.obtener(j, actual);
                lista.obtener(j + 1, siguiente);
                
                bool debeIntercambiar = ascendente ? actual > siguiente : actual < siguiente;
                
                if (debeIntercambiar) {
                    lista.eliminar(j);
                    lista.insertar(siguiente, j);
                    lista.eliminar(j + 1);
                    lista.insertar(actual, j + 1);
                }
            }
        }
    }
    
    /**
     * @brief Ordena una lista utilizando el algoritmo Insertion Sort
     * @param lista Lista a ordenar
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     */
    static void insertionSort(Lista<T>& lista, bool ascendente = true) {
        int n = lista.obtenerTamano();
        
        for (int i = 1; i < n; i++) {
            T valor;
            lista.obtener(i, valor);
            int j = i - 1;
            
            T valorJ;
            lista.obtener(j, valorJ);
            
            bool debeIntercambiar = ascendente ? valorJ > valor : valorJ < valor;
            
            while (j >= 0 && debeIntercambiar) {
                lista.eliminar(j + 1);
                lista.insertar(valorJ, j + 1);
                j--;
                
                if (j >= 0) {
                    lista.obtener(j, valorJ);
                    debeIntercambiar = ascendente ? valorJ > valor : valorJ < valor;
                }
            }
            
            lista.eliminar(j + 1);
            lista.insertar(valor, j + 1);
        }
    }
    
    /**
     * @brief Ordena una lista utilizando el algoritmo Quick Sort
     * @param lista Lista a ordenar
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     */
    static void quickSort(Lista<T>& lista, bool ascendente = true) {
        quickSortRecursivo(lista, 0, lista.obtenerTamano() - 1, ascendente);
    }
    
    /**
     * @brief Ordena una lista utilizando el algoritmo Merge Sort
     * @param lista Lista a ordenar
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     */
    static void mergeSort(Lista<T>& lista, bool ascendente = true) {
        mergeSortRecursivo(lista, 0, lista.obtenerTamano() - 1, ascendente);
    }
    
private:
    /**
     * @brief Método auxiliar recursivo para Quick Sort
     * @param lista Lista a ordenar
     * @param inicio Índice inicial
     * @param fin Índice final
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     */
    static void quickSortRecursivo(Lista<T>& lista, int inicio, int fin, bool ascendente) {
        if (inicio < fin) {
            int pivote = particionar(lista, inicio, fin, ascendente);
            quickSortRecursivo(lista, inicio, pivote - 1, ascendente);
            quickSortRecursivo(lista, pivote + 1, fin, ascendente);
        }
    }
    
    /**
     * @brief Método auxiliar para particionar la lista en Quick Sort
     * @param lista Lista a particionar
     * @param inicio Índice inicial
     * @param fin Índice final
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     * @return Índice del pivote
     */
    static int particionar(Lista<T>& lista, int inicio, int fin, bool ascendente) {
        T pivote;
        lista.obtener(fin, pivote);
        int i = inicio - 1;
        
        for (int j = inicio; j < fin; j++) {
            T valorJ;
            lista.obtener(j, valorJ);
            
            bool debeIntercambiar = ascendente ? valorJ <= pivote : valorJ >= pivote;
            
            if (debeIntercambiar) {
                i++;
                T valorI;
                lista.obtener(i, valorI);
                
                // Intercambiar lista[i] y lista[j]
                lista.eliminar(i);
                lista.insertar(valorJ, i);
                lista.eliminar(j);
                lista.insertar(valorI, j);
            }
        }
        
        T valorI1;
        lista.obtener(i + 1, valorI1);
        
        // Intercambiar lista[i+1] y lista[fin]
        lista.eliminar(i + 1);
        lista.insertar(pivote, i + 1);
        lista.eliminar(fin);
        lista.insertar(valorI1, fin);
        
        return i + 1;
    }
    
    /**
     * @brief Método auxiliar recursivo para Merge Sort
     * @param lista Lista a ordenar
     * @param inicio Índice inicial
     * @param fin Índice final
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     */
    static void mergeSortRecursivo(Lista<T>& lista, int inicio, int fin, bool ascendente) {
        if (inicio < fin) {
            int medio = inicio + (fin - inicio) / 2;
            
            mergeSortRecursivo(lista, inicio, medio, ascendente);
            mergeSortRecursivo(lista, medio + 1, fin, ascendente);
            
            mezclar(lista, inicio, medio, fin, ascendente);
        }
    }
    
    /**
     * @brief Método auxiliar para mezclar dos sublistas en Merge Sort
     * @param lista Lista a mezclar
     * @param inicio Índice inicial
     * @param medio Índice medio
     * @param fin Índice final
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     */
    static void mezclar(Lista<T>& lista, int inicio, int medio, int fin, bool ascendente) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;
        
        // Crear listas temporales
        T* izquierda = new T[n1];
        T* derecha = new T[n2];
        
        // Copiar datos a las listas temporales
        for (int i = 0; i < n1; i++) {
            T valor;
            lista.obtener(inicio + i, valor);
            izquierda[i] = valor;
        }
        
        for (int j = 0; j < n2; j++) {
            T valor;
            lista.obtener(medio + 1 + j, valor);
            derecha[j] = valor;
        }
        
        // Mezclar las listas temporales
        int i = 0, j = 0, k = inicio;
        
        while (i < n1 && j < n2) {
            bool debeTomarIzquierda = ascendente ? 
                izquierda[i] <= derecha[j] : izquierda[i] >= derecha[j];
            
            if (debeTomarIzquierda) {
                lista.eliminar(k);
                lista.insertar(izquierda[i], k);
                i++;
            } else {
                lista.eliminar(k);
                lista.insertar(derecha[j], k);
                j++;
            }
            k++;
        }
        
        // Copiar los elementos restantes de izquierda, si hay
        while (i < n1) {
            lista.eliminar(k);
            lista.insertar(izquierda[i], k);
            i++;
            k++;
        }
        
        // Copiar los elementos restantes de derecha, si hay
        while (j < n2) {
            lista.eliminar(k);
            lista.insertar(derecha[j], k);
            j++;
            k++;
        }
        
        delete[] izquierda;
        delete[] derecha;
    }
};

#endif // ORDENAMIENTO_H
