/**
 * @file Cancion.h
 * @brief Definición de la clase Cancion para el reproductor de música
 * @author v0
 * @date Mayo 2025
 */

#ifndef CANCION_H
#define CANCION_H

#include <string>
#include "../estructuras/Lista.h"

/**
 * @brief Clase que representa una canción con sus metadatos
 */
class Cancion {
private:
    std::string titulo;         ///< Título de la canción
    std::string artista;        ///< Artista de la canción
    std::string album;          ///< Álbum al que pertenece la canción
    int anio;                   ///< Año de lanzamiento
    Lista<std::string> generos; ///< Géneros musicales de la canción
    std::string rutaArchivo;    ///< Ruta del archivo de audio
    int duracionSegundos;       ///< Duración en segundos

public:
    /**
     * @brief Constructor por defecto
     */
    Cancion() : anio(0), duracionSegundos(0) {}
    
    /**
     * @brief Constructor con parámetros
     * @param _titulo Título de la canción
     * @param _artista Artista de la canción
     * @param _album Álbum al que pertenece
     * @param _anio Año de lanzamiento
     * @param _rutaArchivo Ruta del archivo de audio
     * @param _duracionSegundos Duración en segundos
     */
    Cancion(const std::string& _titulo, const std::string& _artista, 
            const std::string& _album, int _anio, 
            const std::string& _rutaArchivo, int _duracionSegundos) 
        : titulo(_titulo), artista(_artista), album(_album), 
          anio(_anio), rutaArchivo(_rutaArchivo), duracionSegundos(_duracionSegundos) {}
    
    /**
     * @brief Obtiene el título de la canción
     * @return Título de la canción
     */
    std::string obtenerTitulo() const {
        return titulo;
    }
    
    /**
     * @brief Establece el título de la canción
     * @param _titulo Nuevo título
     */
    void establecerTitulo(const std::string& _titulo) {
        titulo = _titulo;
    }
    
    /**
     * @brief Obtiene el artista de la canción
     * @return Artista de la canción
     */
    std::string obtenerArtista() const {
        return artista;
    }
    
    /**
     * @brief Establece el artista de la canción
     * @param _artista Nuevo artista
     */
    void establecerArtista(const std::string& _artista) {
        artista = _artista;
    }
    
    /**
     * @brief Obtiene el álbum de la canción
     * @return Álbum de la canción
     */
    std::string obtenerAlbum() const {
        return album;
    }
    
    /**
     * @brief Establece el álbum de la canción
     * @param _album Nuevo álbum
     */
    void establecerAlbum(const std::string& _album) {
        album = _album;
    }
    
    /**
     * @brief Obtiene el año de lanzamiento
     * @return Año de lanzamiento
     */
    int obtenerAnio() const {
        return anio;
    }
    
    /**
     * @brief Establece el año de lanzamiento
     * @param _anio Nuevo año
     */
    void establecerAnio(int _anio) {
        anio = _anio;
    }
    
    /**
     * @brief Obtiene la ruta del archivo de audio
     * @return Ruta del archivo
     */
    std::string obtenerRutaArchivo() const {
        return rutaArchivo;
    }
    
    /**
     * @brief Establece la ruta del archivo de audio
     * @param _rutaArchivo Nueva ruta
     */
    void establecerRutaArchivo(const std::string& _rutaArchivo) {
        rutaArchivo = _rutaArchivo;
    }
    
    /**
     * @brief Obtiene la duración en segundos
     * @return Duración en segundos
     */
    int obtenerDuracionSegundos() const {
        return duracionSegundos;
    }
    
    /**
     * @brief Establece la duración en segundos
     * @param _duracionSegundos Nueva duración
     */
    void establecerDuracionSegundos(int _duracionSegundos) {
        duracionSegundos = _duracionSegundos;
    }
    
    /**
     * @brief Agrega un género a la canción
     * @param genero Género a agregar
     */
    void agregarGenero(const std::string& genero) {
        generos.agregar(genero);
    }
    
    /**
     * @brief Obtiene la lista de géneros
     * @return Lista de géneros
     */
    const Lista<std::string>& obtenerGeneros() const {
        return generos;
    }
    
    /**
     * @brief Formatea la duración en formato mm:ss
     * @return Duración formateada
     */
    std::string obtenerDuracionFormateada() const {
        int minutos = duracionSegundos / 60;
        int segundos = duracionSegundos % 60;
        
        std::string resultado = std::to_string(minutos) + ":";
        if (segundos < 10) {
            resultado += "0";
        }
        resultado += std::to_string(segundos);
        
        return resultado;
    }
    
    /**
     * @brief Operador de igualdad
     * @param otra Canción a comparar
     * @return true si son iguales, false en caso contrario
     */
    bool operator==(const Cancion& otra) const {
        return titulo == otra.titulo && 
               artista == otra.artista && 
               album == otra.album;
    }
    
    /**
     * @brief Operador menor que (para ordenamiento)
     * @param otra Canción a comparar
     * @return true si esta canción es menor, false en caso contrario
     */
    bool operator<(const Cancion& otra) const {
        return titulo < otra.titulo;
    }
    
    /**
     * @brief Operador mayor que (para ordenamiento)
     * @param otra Canción a comparar
     * @return true si esta canción es mayor, false en caso contrario
     */
    bool operator>(const Cancion& otra) const {
        return titulo > otra.titulo;
    }
};

#endif // CANCION_H
