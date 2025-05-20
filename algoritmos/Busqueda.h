#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <string>
#include <cctype>
#include <functional>
#include "../estructuras/Lista.h"

template <typename T>
class Busqueda {
public:
    // B�squeda lineal
    static int busquedaLineal(const Lista<T>& lista, const T& elemento) {
        for (int i = 0; i < lista.obtenerTamanio(); i++) {
            if (lista.obtener(i) == elemento) {
                return i;
            }
        }
        return -1;
    }

    // B�squeda binaria (requiere que la lista est� ordenada)
    static int busquedaBinaria(const Lista<T>& lista, const T& elemento) {
        int inicio = 0;
        int fin = lista.obtenerTamanio() - 1;

        while (inicio <= fin) {
            int medio = inicio + (fin - inicio) / 2;

            if (lista.obtener(medio) == elemento) {
                return medio;
            }

            if (lista.obtener(medio) < elemento) {
                inicio = medio + 1;
            } else {
                fin = medio - 1;
            }
        }

        return -1;
    }

    // B�squeda por criterio usando puntero a funci�n
    static Lista<int> busquedaPorCriterio(const Lista<T>& lista, bool (*criterio)(const T&)) {
        Lista<int> resultados;

        for (int i = 0; i < lista.obtenerTamanio(); i++) {
            if (criterio(lista.obtener(i))) {
                resultados.agregar(i);
            }
        }

        return resultados;
    }

    // B�squeda por criterio usando funci�n lambda (nueva funci�n)
    template <typename Func>
    static Lista<int> busquedaPorCriterioFunc(const Lista<T>& lista, Func criterio) {
        Lista<int> resultados;

        for (int i = 0; i < lista.obtenerTamanio(); i++) {
            if (criterio(lista.obtener(i))) {
                resultados.agregar(i);
            }
        }

        return resultados;
    }

    // Utilidad para convertir a min�sculas
    static std::string aMinusculas(const std::string& texto) {
        std::string resultado = texto;
        for (size_t i = 0; i < resultado.length(); i++) {
            resultado[i] = std::tolower(resultado[i]);
        }
        return resultado;
    }

    // Utilidad para verificar si una cadena contiene otra (insensible a may�sculas/min�sculas)
    static bool contieneCadenaInsensible(const std::string& texto, const std::string& busqueda) {
        std::string textoMin = aMinusculas(texto);
        std::string busquedaMin = aMinusculas(busqueda);

        return textoMin.find(busquedaMin) != std::string::npos;
    }
};

#endif // BUSQUEDA_H
