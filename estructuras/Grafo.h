#ifndef GRAFO_H
#define GRAFO_H

#include "Lista.h"
#include "Cola.h"
#include <stdexcept>
#include <string>

template <typename T>
class Grafo {
private:
    struct Arista {
        int destino;
        int peso;

        Arista(int _destino, int _peso = 1) : destino(_destino), peso(_peso) {}

        bool operator==(const Arista& otra) const {
            return destino == otra.destino && peso == otra.peso;
        }
    };

    Lista<T> vertices;
    Lista<Lista<Arista>> adyacencia;

public:
    // Constructor
    Grafo() {}

    // Destructor
    ~Grafo() {
        vaciar();
    }

    // Agregar vértice
    bool agregarVertice(const T& vertice) {
        if (existeVertice(vertice)) {
            return false;
        }

        vertices.agregar(vertice);
        adyacencia.agregar(Lista<Arista>());
        return true;
    }

    // Verificar si existe un vértice
    bool existeVertice(const T& vertice) const {
        return buscarVertice(vertice) != -1;
    }

    // Buscar índice de un vértice
    int buscarVertice(const T& vertice) const {
        for (int i = 0; i < vertices.obtenerTamanio(); i++) {
            if (vertices.obtener(i) == vertice) {
                return i;
            }
        }
        return -1;
    }

    // Agregar arista
    bool agregarArista(const T& origen, const T& destino, int peso = 1) {
        int indiceOrigen = buscarVertice(origen);
        int indiceDestino = buscarVertice(destino);

        if (indiceOrigen == -1 || indiceDestino == -1) {
            return false;
        }

        // Verificar si la arista ya existe
        Lista<Arista> listaAdyacencia = adyacencia.obtener(indiceOrigen);
        for (int i = 0; i < listaAdyacencia.obtenerTamanio(); i++) {
            if (listaAdyacencia.obtener(i).destino == indiceDestino) {
                return false;
            }
        }

        // Agregar la arista
        listaAdyacencia.agregar(Arista(indiceDestino, peso));
        adyacencia.modificar(indiceOrigen, listaAdyacencia);
        return true;
    }

    // Obtener vértices adyacentes (BFS)
    Lista<T> obtenerVecinosBFS(const T& origen) const {
        Lista<T> resultado;
        int indiceOrigen = buscarVertice(origen);

        if (indiceOrigen == -1) {
            return resultado;
        }

        // Arreglo para marcar vértices visitados
        bool* visitados = new bool[vertices.obtenerTamanio()];
        for (int i = 0; i < vertices.obtenerTamanio(); i++) {
            visitados[i] = false;
        }

        // Cola para BFS
        Cola<int> cola;
        cola.encolar(indiceOrigen);
        visitados[indiceOrigen] = true;

        while (!cola.estaVacia()) {
            int actual = cola.frente();
            cola.desencolar();

            // No agregar el vértice origen al resultado
            if (actual != indiceOrigen) {
                resultado.agregar(vertices.obtener(actual));
            }

            // Explorar vecinos
            Lista<Arista> vecinos = adyacencia.obtener(actual);
            for (int i = 0; i < vecinos.obtenerTamanio(); i++) {
                int vecino = vecinos.obtener(i).destino;
                if (!visitados[vecino]) {
                    cola.encolar(vecino);
                    visitados[vecino] = true;
                }
            }
        }

        delete[] visitados;
        return resultado;
    }

    // Obtener vértices adyacentes (DFS)
    Lista<T> obtenerVecinosDFS(const T& origen) const {
        Lista<T> resultado;
        int indiceOrigen = buscarVertice(origen);

        if (indiceOrigen == -1) {
            return resultado;
        }

        // Arreglo para marcar vértices visitados
        bool* visitados = new bool[vertices.obtenerTamanio()];
        for (int i = 0; i < vertices.obtenerTamanio(); i++) {
            visitados[i] = false;
        }

        // Llamada al método auxiliar recursivo
        dfsRecursivo(indiceOrigen, resultado, visitados, indiceOrigen);

        delete[] visitados;
        return resultado;
    }

    // Vaciar el grafo
    void vaciar() {
        vertices.vaciar();
        adyacencia.vaciar();
    }

    // Obtener número de vértices
    int obtenerNumVertices() const {
        return vertices.obtenerTamanio();
    }

private:
    // Método auxiliar recursivo para DFS
    void dfsRecursivo(int actual, Lista<T>& resultado, bool* visitados, int origen) const {
        visitados[actual] = true;

        // No agregar el vértice origen al resultado
        if (actual != origen) {
            resultado.agregar(vertices.obtener(actual));
        }

        // Explorar vecinos
        Lista<Arista> vecinos = adyacencia.obtener(actual);
        for (int i = 0; i < vecinos.obtenerTamanio(); i++) {
            int vecino = vecinos.obtener(i).destino;
            if (!visitados[vecino]) {
                dfsRecursivo(vecino, resultado, visitados, origen);
            }
        }
    }
};

#endif // GRAFO_H
