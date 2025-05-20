/**
 * @file Playlist.h
 * @brief Definición de la clase Playlist para el reproductor de música
 * @author v0
 * @date Mayo 2025
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include "../estructuras/Lista.h"
#include "Cancion.h"

/**
 * @brief Clase que representa una lista de reproducción
 */
class Playlist {
private:
    std::string nombre;             ///< Nombre de la lista de reproducción
    Lista<Cancion> canciones;       ///< Lista de canciones
    
public:
    /**
     * @brief Constructor por defecto
     */
    Playlist() {}
    
    /**
     * @brief Constructor con nombre
     * @param _nombre Nombre de la lista de reproducción
     */
    Playlist(const std::string& _nombre) : nombre(_nombre) {}
    
    /**
     * @brief Obtiene el nombre de la lista de reproducción
     * @return Nombre de la lista
     */
    std::string obtenerNombre() const {
        return nombre;
    }
    
    /**
     * @brief Establece el nombre de la lista de reproducción
     * @param _nombre Nuevo nombre
     */
    void establecerNombre(const std::string& _nombre) {
        nombre = _nombre;
    }
    
    /**
     * @brief Agrega una canción a la lista de reproducción
     * @param cancion Canción a agregar
     */
    void agregarCancion(const Cancion& cancion) {
        canciones.agregar(cancion);
    }
    
    /**
     * @brief Elimina una canción de la lista de reproducción por su posición
     * @param posicion Posición de la canción (0-indexado)
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminarCancion(int posicion) {
        return canciones.eliminar(posicion);
    }
    
    /**
     * @brief Elimina una canción de la lista de reproducción por su título
     * @param titulo Título de la canción a eliminar
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminarCancionPorTitulo(const std::string& titulo) {
        int tamano = canciones.obtenerTamano();
        
        for (int i = 0; i < tamano; i++) {
            Cancion actual;
            canciones.obtener(i, actual);
            
            if (actual.obtenerTitulo() == titulo) {
                return canciones.eliminar(i);
            }
        }
        
        return false;
    }
    
    /**
     * @brief Obtiene una canción por su posición
     * @param posicion Posición de la canción (0-indexado)
     * @param resultado Variable donde se almacenará el resultado
     * @return true si se obtuvo correctamente, false en caso contrario
     */
    bool obtenerCancion(int posicion, Cancion& resultado) const {
        return canciones.obtener(posicion, resultado);
    }
    
    /**
     * @brief Busca una canción por su título
     * @param titulo Título de la canción a buscar
     * @return Posición de la canción o -1 si no se encuentra
     */
    int buscarCancionPorTitulo(const std::string& titulo) const {
        int tamano = canciones.obtenerTamano();
        
        for (int i = 0; i < tamano; i++) {
            Cancion actual;
            canciones.obtener(i, actual);
            
            if (actual.obtenerTitulo() == titulo) {
                return i;
            }
        }
        
        return -1;
    }
    
    /**
     * @brief Obtiene el número de canciones en la lista
     * @return Número de canciones
     */
    int obtenerNumeroCanciones() const {
        return canciones.obtenerTamano();
    }
    
    /**
     * @brief Obtiene la duración total de la lista en segundos
     * @return Duración total en segundos
     */
    int obtenerDuracionTotal() const {
        int duracionTotal = 0;
        int tamano = canciones.obtenerTamano();
        
        for (int i = 0; i < tamano; i++) {
            Cancion actual;
            canciones.obtener(i, actual);
            duracionTotal += actual.obtenerDuracionSegundos();
        }
        
        return duracionTotal;
    }
    
    /**
     * @brief Formatea la duración total en formato hh:mm:ss
     * @return Duración total formateada
     */
    std::string obtenerDuracionTotalFormateada() const {
        int duracionTotal = obtenerDuracionTotal();
        int horas = duracionTotal / 3600;
        int minutos = (duracionTotal % 3600) / 60;
        int segundos = duracionTotal % 60;
        
        std::string resultado;
        
        if (horas > 0) {
            resultado = std::to_string(horas) + ":";
            if (minutos < 10) {
                resultado += "0";
            }
        }
        
        resultado += std::to_string(minutos) + ":";
        if (segundos < 10) {
            resultado += "0";
        }
        resultado += std::to_string(segundos);
        
        return resultado;
    }
    
    /**
     * @brief Obtiene la lista de canciones
     * @return Lista de canciones
     */
    const Lista<Cancion>& obtenerCanciones() const {
        return canciones;
    }
    
    /**
     * @brief Operador de igualdad
     * @param otra Playlist a comparar
     * @return true si son iguales, false en caso contrario
     */
    bool operator==(const Playlist& otra) const {
        return nombre == otra.nombre;
    }
};

#endif // PLAYLIST_H
