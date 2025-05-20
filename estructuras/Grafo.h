/**
 * @file Grafo.h
 * @brief Implementación de un grafo dirigido ponderado desde cero
 * @author v0
 * @date Mayo 2025
 */

#ifndef GRAFO_H
#define GRAFO_H

#include "Lista.h"
#include "Cola.h"
#include <iostream>
#include <limits>

/**
 * @brief Arista para el grafo
 * @tparam T Tipo de dato para los vértices
 */
template <typename T>
struct Arista {
    int destino;            ///< Índice del vértice destino
    int peso;               ///< Peso de la arista
    
    /**
     * @brief Constructor de la arista
     * @param _destino Índice del vértice destino
     * @param _peso Peso de la arista
     */
    Arista(int _destino, int _peso) : destino(_destino), peso(_peso) {}
    
    /**
     * @brief Operador de igualdad
     * @param otra Arista a comparar
     * @return true si son iguales, false en caso contrario
     */
    bool operator==(const Arista& otra) const {
        return destino == otra.destino && peso == otra.peso;
    }
};

/**
 * @brief Grafo dirigido ponderado implementado con listas de adyacencia
 * @tparam T Tipo de dato para los vértices
 */
template <typename T>
class Grafo {
private:
    Lista<T> vertices;                  ///< Lista de vértices
    Lista<Lista<Arista<T>>> adyacencia; ///< Lista de adyacencia
    
public:
    /**
     * @brief Constructor por defecto
     */
    Grafo() {}
    
    /**
     * @brief Destructor
     */
    ~Grafo() {
        // La memoria se libera automáticamente con los destructores de Lista
    }
    
    /**
     * @brief Agrega un vértice al grafo
     * @param vertice Vértice a agregar
     * @return Índice del vértice agregado
     */
    int agregarVertice(const T& vertice) {
        vertices.agregar(vertice);
        adyacencia.agregar(Lista<Arista<T>>());
        return vertices.obtenerTamano() - 1;
    }
    
    /**
     * @brief Agrega una arista dirigida entre dos vértices
     * @param origen Índice del vértice origen
     * @param destino Índice del vértice destino
     * @param peso Peso de la arista
     * @return true si se agregó correctamente, false en caso contrario
     */
    bool agregarArista(int origen, int destino, int peso = 1) {
        if (origen < 0 || origen >= vertices.obtenerTamano() ||
            destino < 0 || destino >= vertices.obtenerTamano()) {
            return false;
        }
        
        Lista<Arista<T>> listaAdyacencia;
        adyacencia.obtener(origen, listaAdyacencia);
        
        // Verificar si la arista ya existe
        for (auto it = listaAdyacencia.inicio(); it != listaAdyacencia.fin(); ++it) {
            if ((*it).destino == destino) {
                return false; // La arista ya existe
            }
        }
        
        listaAdyacencia.agregar(Arista<T>(destino, peso));
        adyacencia.eliminar(origen);
        adyacencia.insertar(listaAdyacencia, origen);
        
        return true;
    }
    
    /**
     * @brief Elimina una arista entre dos vértices
     * @param origen Índice del vértice origen
     * @param destino Índice del vértice destino
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminarArista(int origen, int destino) {
        if (origen < 0 || origen >= vertices.obtenerTamano() ||
            destino < 0 || destino >= vertices.obtenerTamano()) {
            return false;
        }
        
        Lista<Arista<T>> listaAdyacencia;
        adyacencia.obtener(origen, listaAdyacencia);
        
        for (auto it = listaAdyacencia.inicio(); it != listaAdyacencia.fin(); ++it) {
            if ((*it).destino == destino) {
                listaAdyacencia.eliminarPorValor(*it);
                adyacencia.eliminar(origen);
                adyacencia.insertar(listaAdyacencia, origen);
                return true;
            }
        }
        
        return false; // La arista no existe
    }
    
    /**
     * @brief Obtiene un vértice por su índice
     * @param indice Índice del vértice
     * @param resultado Variable donde se almacenará el resultado
     * @return true si se obtuvo correctamente, false en caso contrario
     */
    bool obtenerVertice(int indice, T& resultado) const {
        return vertices.obtener(indice, resultado);
    }
    
    /**
     * @brief Busca un vértice por su valor
     * @param vertice Valor del vértice a buscar
     * @return Índice del vértice o -1 si no se encuentra
     */
    int buscarVertice(const T& vertice) const {
        return vertices.buscar(vertice);
    }
    
    /**
     * @brief Obtiene la cantidad de vértices
     * @return Número de vértices en el grafo
     */
    int obtenerNumeroVertices() const {
        return vertices.obtenerTamano();
    }
    
    /**
     * @brief Verifica si existe una arista entre dos vértices
     * @param origen Índice del vértice origen
     * @param destino Índice del vértice destino
     * @return true si existe la arista, false en caso contrario
     */
    bool existeArista(int origen, int destino) const {
        if (origen < 0 || origen >= vertices.obtenerTamano() ||
            destino < 0 || destino >= vertices.obtenerTamano()) {
            return false;
        }
        
        Lista<Arista<T>> listaAdyacencia;
        adyacencia.obtener(origen, listaAdyacencia);
        
        for (auto it = listaAdyacencia.inicio(); it != listaAdyacencia.fin(); ++it) {
            if ((*it).destino == destino) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * @brief Obtiene el peso de una arista
     * @param origen Índice del vértice origen
     * @param destino Índice del vértice destino
     * @param peso Variable donde se almacenará el resultado
     * @return true si se obtuvo correctamente, false en caso contrario
     */
    bool obtenerPesoArista(int origen, int destino, int& peso) const {
        if (origen < 0 || origen >= vertices.obtenerTamano() ||
            destino < 0 || destino >= vertices.obtenerTamano()) {
            return false;
        }
        
        Lista<Arista<T>> listaAdyacencia;
        adyacencia.obtener(origen, listaAdyacencia);
        
        for (auto it = listaAdyacencia.inicio(); it != listaAdyacencia.fin(); ++it) {
            if ((*it).destino == destino) {
                peso = (*it).peso;
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * @brief Obtiene los vértices adyacentes a un vértice
     * @param origen Índice del vértice
     * @param adyacentes Lista donde se almacenarán los índices de los vértices adyacentes
     * @return true si se obtuvo correctamente, false en caso contrario
     */
    bool obtenerAdyacentes(int origen, Lista<int>& adyacentes) const {
        if (origen < 0 || origen >= vertices.obtenerTamano()) {
            return false;
        }
        
        Lista<Arista<T>> listaAdyacencia;
        adyacencia.obtener(origen, listaAdyacencia);
        
        for (auto it = listaAdyacencia.inicio(); it != listaAdyacencia.fin(); ++it) {
            adyacentes.agregar((*it).destino);
        }
        
        return true;
    }
    
    /**
     * @brief Realiza un recorrido en anchura (BFS) desde un vértice
     * @param inicio Índice del vértice inicial
     * @param visitados Lista donde se almacenarán los índices de los vértices visitados
     * @return true si se realizó correctamente, false en caso contrario
     */
    bool bfs(int inicio, Lista<int>& visitados) const {
        if (inicio < 0 || inicio >= vertices.obtenerTamano()) {
            return false;
        }
        
        // Arreglo para marcar vértices visitados
        bool* marcados = new bool[vertices.obtenerTamano()];
        for (int i = 0; i < vertices.obtenerTamano(); i++) {
            marcados[i] = false;
        }
        
        Cola<int> cola;
        cola.encolar(inicio);
        marcados[inicio] = true;
        
        while (!cola.estaVacia()) {
            int actual;
            cola.frenteCola(actual);
            cola.desencolar();
            
            visitados.agregar(actual);
            
            Lista<Arista<T>> listaAdyacencia;
            adyacencia.obtener(actual, listaAdyacencia);
            
            for (auto it = listaAdyacencia.inicio(); it != listaAdyacencia.fin(); ++it) {
                int adyacente = (*it).destino;
                if (!marcados[adyacente]) {
                    cola.encolar(adyacente);
                    marcados[adyacente] = true;
                }
            }
        }
        
        delete[] marcados;
        return true;
    }
    
    /**
     * @brief Realiza un recorrido en profundidad (DFS) desde un vértice
     * @param inicio Índice del vértice inicial
     * @param visitados Lista donde se almacenarán los índices de los vértices visitados
     * @return true si se realizó correctamente, false en caso contrario
     */
    bool dfs(int inicio, Lista<int>& visitados) const {
        if (inicio < 0 || inicio >= vertices.obtenerTamano()) {
            return false;
        }
        
        // Arreglo para marcar vértices visitados
        bool* marcados = new bool[vertices.obtenerTamano()];
        for (int i = 0; i < vertices.obtenerTamano(); i++) {
            marcados[i] = false;
        }
        
        // Llamada al método auxiliar recursivo
        dfsRecursivo(inicio, visitados, marcados);
        
        delete[] marcados;
        return true;
    }
    
private:
    /**
     * @brief Método auxiliar recursivo para DFS
     * @param actual Índice del vértice actual
     * @param visitados Lista donde se almacenarán los índices de los vértices visitados
     * @param marcados Arreglo para marcar vértices visitados
     */
    void dfsRecursivo(int actual, Lista<int>& visitados, bool* marcados) const {
        marcados[actual] = true;
        visitados.agregar(actual);
        
        Lista<Arista<T>> listaAdyacencia;
        adyacencia.obtener(actual, listaAdyacencia);
        
        for (auto it = listaAdyacencia.inicio(); it != listaAdyacencia.fin(); ++it) {
            int adyacente = (*it).destino;
            if (!marcados[adyacente]) {
                dfsRecursivo(adyacente, visitados, marcados);
            }
        }
    }
};

#endif // GRAFO_H
