#ifndef LISTA_REPRODUCCION_H
#define LISTA_REPRODUCCION_H

#include <string>
#include "../estructuras/Lista.h"

/**
 * @brief Estructura que representa una lista de reproducción
 */
struct ListaReproduccion {
    std::string nombre;           // Nombre de la lista de reproducción
    std::string descripcion;      // Descripción opcional
    Lista<int> canciones;         // Índices de canciones en la biblioteca
    
    // Constructor por defecto
    ListaReproduccion() : nombre("Nueva Lista"), descripcion("") {}
    
    // Constructor con nombre
    ListaReproduccion(const std::string& _nombre) : nombre(_nombre), descripcion("") {}
    
    // Constructor completo
    ListaReproduccion(const std::string& _nombre, const std::string& _descripcion) : 
        nombre(_nombre), descripcion(_descripcion) {}
    
    // Agrega una canción a la lista de reproducción
    bool agregarCancion(int indiceCancion) {
        if (canciones.contiene(indiceCancion)) {
            return false;
        }
        
        canciones.agregar(indiceCancion);
        return true;
    }
    
    // Elimina una canción de la lista de reproducción
    bool eliminarCancion(int indiceCancion) {
        int posicion = canciones.buscar(indiceCancion);
        if (posicion == -1) {
            return false;
        }
        
        canciones.eliminar(posicion);
        return true;
    }
    
    // Verifica si la lista contiene una canción específica
    bool contieneCancion(int indiceCancion) const {
        return canciones.contiene(indiceCancion);
    }
    
    // Obtiene el número de canciones en la lista
    int obtenerNumCanciones() const {
        return canciones.obtenerTamanio();
    }
    
    // Vacía la lista de reproducción
    void vaciar() {
        canciones.vaciar();
    }
    
    // Operadores de comparación
    bool operator==(const ListaReproduccion& otra) const {
        return nombre == otra.nombre;
    }
    
    bool operator!=(const ListaReproduccion& otra) const {
        return !(*this == otra);
    }
    
    bool operator<(const ListaReproduccion& otra) const {
        return nombre < otra.nombre;
    }
    
    bool operator>(const ListaReproduccion& otra) const {
        return nombre > otra.nombre;
    }
    
    bool operator<=(const ListaReproduccion& otra) const {
        return nombre <= otra.nombre;
    }
    
    bool operator>=(const ListaReproduccion& otra) const {
        return nombre >= otra.nombre;
    }
};

#endif // LISTA_REPRODUCCION_H