#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <functional>
#include "../estructuras/Lista.h"

template <typename T>
class Ordenamiento {
public:
    // Ordenamiento burbuja
    static void bubbleSort(Lista<T>& lista, bool ascendente = true) {
        int n = lista.obtenerTamanio();

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                T elemento1 = lista.obtener(j);
                T elemento2 = lista.obtener(j + 1);

                bool debeIntercambiar = ascendente ?
                    (elemento1 > elemento2) : (elemento1 < elemento2);

                if (debeIntercambiar) {
                    lista.modificar(j, elemento2);
                    lista.modificar(j + 1, elemento1);
                }
            }
        }
    }

    // Ordenamiento por inserción
    static void insertionSort(Lista<T>& lista, bool ascendente = true) {
        int n = lista.obtenerTamanio();

        for (int i = 1; i < n; i++) {
            T elementoActual = lista.obtener(i);
            int j = i - 1;

            bool seguirMoviendo = ascendente ?
                (j >= 0 && lista.obtener(j) > elementoActual) :
                (j >= 0 && lista.obtener(j) < elementoActual);

            while (seguirMoviendo) {
                lista.modificar(j + 1, lista.obtener(j));
                j--;

                seguirMoviendo = ascendente ?
                    (j >= 0 && lista.obtener(j) > elementoActual) :
                    (j >= 0 && lista.obtener(j) < elementoActual);
            }

            lista.modificar(j + 1, elementoActual);
        }
    }

    // Ordenamiento rápido (QuickSort)
    static void quickSort(Lista<T>& lista, bool ascendente = true) {
        quickSortRecursivo(lista, 0, lista.obtenerTamanio() - 1, ascendente);
    }

    // Ordenamiento por mezcla (MergeSort)
    static void mergeSort(Lista<T>& lista, bool ascendente = true) {
        mergeSortRecursivo(lista, 0, lista.obtenerTamanio() - 1, ascendente);
    }

    // Ordenamiento por campo específico usando una función de comparación
    template <typename Comparador>
    static void ordenarPorCampo(Lista<T>& lista, Comparador comparador, bool ascendente = true) {
        int n = lista.obtenerTamanio();

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                T elemento1 = lista.obtener(j);
                T elemento2 = lista.obtener(j + 1);

                bool debeIntercambiar;
                if (ascendente) {
                    debeIntercambiar = !comparador(elemento1, elemento2);
                } else {
                    debeIntercambiar = comparador(elemento1, elemento2);
                }

                if (debeIntercambiar) {
                    lista.modificar(j, elemento2);
                    lista.modificar(j + 1, elemento1);
                }
            }
        }
    }

private:
    // Método auxiliar para QuickSort
    static int particionar(Lista<T>& lista, int inicio, int fin, bool ascendente) {
        T pivote = lista.obtener(fin);
        int i = inicio - 1;

        for (int j = inicio; j < fin; j++) {
            T elementoActual = lista.obtener(j);

            bool debeIntercambiar = ascendente ?
                (elementoActual <= pivote) : (elementoActual >= pivote);

            if (debeIntercambiar) {
                i++;
                T temp = lista.obtener(i);
                lista.modificar(i, elementoActual);
                lista.modificar(j, temp);
            }
        }

        T temp = lista.obtener(i + 1);
        lista.modificar(i + 1, pivote);
        lista.modificar(fin, temp);

        return i + 1;
    }

    // Método recursivo para QuickSort
    static void quickSortRecursivo(Lista<T>& lista, int inicio, int fin, bool ascendente) {
        if (inicio < fin) {
            int indicePivote = particionar(lista, inicio, fin, ascendente);

            quickSortRecursivo(lista, inicio, indicePivote - 1, ascendente);
            quickSortRecursivo(lista, indicePivote + 1, fin, ascendente);
        }
    }

    // Método auxiliar para MergeSort
    static void mezclar(Lista<T>& lista, int inicio, int medio, int fin, bool ascendente) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        // Crear listas temporales
        T* izquierda = new T[n1];
        T* derecha = new T[n2];

        // Copiar datos a las listas temporales
        for (int i = 0; i < n1; i++) {
            izquierda[i] = lista.obtener(inicio + i);
        }

        for (int j = 0; j < n2; j++) {
            derecha[j] = lista.obtener(medio + 1 + j);
        }

        // Mezclar las listas temporales
        int i = 0;
        int j = 0;
        int k = inicio;

        while (i < n1 && j < n2) {
            bool debeTomarIzquierda = ascendente ?
                (izquierda[i] <= derecha[j]) : (izquierda[i] >= derecha[j]);

            if (debeTomarIzquierda) {
                lista.modificar(k, izquierda[i]);
                i++;
            } else {
                lista.modificar(k, derecha[j]);
                j++;
            }
            k++;
        }

        // Copiar los elementos restantes de izquierda, si hay alguno
        while (i < n1) {
            lista.modificar(k, izquierda[i]);
            i++;
            k++;
        }

        // Copiar los elementos restantes de derecha, si hay alguno
        while (j < n2) {
            lista.modificar(k, derecha[j]);
            j++;
            k++;
        }

        // Liberar memoria
        delete[] izquierda;
        delete[] derecha;
    }

    // Método recursivo para MergeSort
    static void mergeSortRecursivo(Lista<T>& lista, int inicio, int fin, bool ascendente) {
        if (inicio < fin) {
            int medio = inicio + (fin - inicio) / 2;

            mergeSortRecursivo(lista, inicio, medio, ascendente);
            mergeSortRecursivo(lista, medio + 1, fin, ascendente);

            mezclar(lista, inicio, medio, fin, ascendente);
        }
    }
};

#endif // ORDENAMIENTO_H
