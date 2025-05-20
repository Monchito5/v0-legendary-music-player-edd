#ifndef CANCION_H
#define CANCION_H

#include <string>
#include "../estructuras/Lista.h"

/**
 * @brief Estructura que representa una canción
 */
struct Cancion {
    std::string titulo;           // Título de la canción
    std::string artista;          // Artista o intérprete
    std::string album;            // Álbum al que pertenece
    int anio;                     // Año de lanzamiento
    int duracion;                 // Duración en segundos
    Lista<std::string> generos;   // Géneros musicales
    
    // Constructor por defecto
    Cancion() : titulo(""), artista(""), album(""), anio(0), duracion(0) {}
    
    // Constructor con parámetros
    Cancion(const std::string& _titulo, const std::string& _artista, const std::string& _album, 
            int _anio, int _duracion) 
        : titulo(_titulo), artista(_artista), album(_album), anio(_anio), duracion(_duracion) {}
    
    // Métodos de comparación para ordenamiento
    bool compararPorTitulo(const Cancion& otra) const {
        return titulo < otra.titulo;
    }
    
    bool compararPorArtista(const Cancion& otra) const {
        return artista < otra.artista;
    }
    
    bool compararPorAlbum(const Cancion& otra) const {
        return album < otra.album;
    }
    
    bool compararPorAnio(const Cancion& otra) const {
        return anio < otra.anio;
    }
    
    // Operadores de comparación necesarios para los algoritmos de ordenamiento
    bool operator<=(const Cancion& otra) const {
        return titulo <= otra.titulo;
    }
    
    bool operator>=(const Cancion& otra) const {
        return titulo >= otra.titulo;
    }
    
    bool operator<(const Cancion& otra) const {
        return titulo < otra.titulo;
    }
    
    bool operator>(const Cancion& otra) const {
        return titulo > otra.titulo;
    }
    
    bool operator==(const Cancion& otra) const {
        return titulo == otra.titulo && artista == otra.artista;
    }
    
    bool operator!=(const Cancion& otra) const {
        return !(*this == otra);
    }
    
    // Método para formatear la duración
    std::string obtenerDuracionFormateada() const {
        int minutos = duracion / 60;
        int segundos = duracion % 60;
        char buffer[10];
        sprintf(buffer, "%02d:%02d", minutos, segundos);
        return std::string(buffer);
    }
};

#endif // CANCION_H