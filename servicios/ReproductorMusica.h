/**
 * @file ReproductorMusica.h
 * @brief Definición de la clase ReproductorMusica para controlar la reproducción
 * @author v0
 * @date Mayo 2025
 */

#ifndef REPRODUCTOR_MUSICA_H
#define REPRODUCTOR_MUSICA_H

#include <string>
#include "../estructuras/Lista.h"
#include "../estructuras/Pila.h"
#include "../estructuras/Cola.h"
#include "../modelos/Cancion.h"
#include "../modelos/Playlist.h"
#include "BibliotecaMusical.h"

/**
 * @brief Clase que controla la reproducción de música
 */
class ReproductorMusica {
private:
    BibliotecaMusical* biblioteca;     ///< Puntero a la biblioteca musical
    Cancion* cancionActual;            ///< Puntero a la canción en reproducción
    bool reproduciendo;                ///< Indica si está reproduciendo
    bool pausado;                      ///< Indica si está pausado
    int volumen;                       ///< Volumen actual (0-100)
    int posicionActual;                ///< Posición actual en segundos
    Pila<Cancion> historial;           ///< Historial de canciones reproducidas
    Cola<Cancion> colaReproduccion;    ///< Cola de reproducción
    int limiteHistorial;               ///< Límite de canciones en el historial
    
public:
    /**
     * @brief Constructor con parámetros
     * @param _biblioteca Puntero a la biblioteca musical
     * @param _limiteHistorial Límite de canciones en el historial
     */
    ReproductorMusica(BibliotecaMusical* _biblioteca, int _limiteHistorial = 10)
        : biblioteca(_biblioteca), cancionActual(nullptr), reproduciendo(false),
          pausado(false), volumen(80), posicionActual(0), limiteHistorial(_limiteHistorial) {}
    
    /**
     * @brief Destructor
     */
    ~ReproductorMusica() {
        if (cancionActual) {
            delete cancionActual;
        }
    }
    
    /**
     * @brief Reproduce una canción de la biblioteca
     * @param posicion Posición de la canción en la biblioteca
     * @return true si se inició la reproducción, false en caso contrario
     */
    bool reproducir(int posicion) {
        Cancion cancion;
        if (biblioteca->obtenerCancion(posicion, cancion)) {
            // Guardar la canción actual en el historial si existe
            if (cancionActual) {
                agregarAlHistorial(*cancionActual);
                delete cancionActual;
            }
            
            cancionActual = new Cancion(cancion);
            reproduciendo = true;
            pausado = false;
            posicionActual = 0;
            
            return true;
        }
        
        return false;
    }
    
    /**
     * @brief Reproduce una canción de una playlist
     * @param posicionPlaylist Posición de la playlist
     * @param posicionCancion Posición de la canción en la playlist
     * @return true si se inició la reproducción, false en caso contrario
     */
    bool reproducirDePlaylist(int posicionPlaylist, int posicionCancion) {
        Playlist playlist;
        if (biblioteca->obtenerPlaylist(posicionPlaylist, playlist)) {
            Cancion cancion;
            if (playlist.obtenerCancion(posicionCancion, cancion)) {
                // Guardar la canción actual en el historial si existe
                if (cancionActual) {
                    agregarAlHistorial(*cancionActual);
                    delete cancionActual;
                }
                
                cancionActual = new Cancion(cancion);
                reproduciendo = true;
                pausado = false;
                posicionActual = 0;
                
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * @brief Pausa o reanuda la reproducción
     * @return true si se cambió el estado, false en caso contrario
     */
    bool pausarReanudar() {
        if (!cancionActual) {
            return false;
        }
        
        pausado = !pausado;
        return true;
    }
    
    /**
     * @brief Detiene la reproducción
     * @return true si se detuvo, false en caso contrario
     */
    bool detener() {
        if (!cancionActual) {
            return false;
        }
        
        reproduciendo = false;
        pausado = false;
        posicionActual = 0;
        return true;
    }
    
    /**
     * @brief Avanza a la siguiente canción en la cola
     * @return true si se avanzó, false en caso contrario
     */
    bool siguiente() {
        if (colaReproduccion.estaVacia()) {
            return false;
        }
        
        // Guardar la canción actual en el historial si existe
        if (cancionActual) {
            agregarAlHistorial(*cancionActual);
            delete cancionActual;
        }
        
        Cancion siguiente;
        colaReproduccion.frenteCola(siguiente);
        colaReproduccion.desencolar();
        
        cancionActual = new Cancion(siguiente);
        reproduciendo = true;
        pausado = false;
        posicionActual = 0;
        
        return true;
    }
    
    /**
     * @brief Retrocede a la canción anterior en el historial
     * @return true si se retrocedió, false en caso contrario
     */
    bool anterior() {
        if (historial.estaVacia()) {
            return false;
        }
        
        // Si hay una canción actual, encolarla al principio
        if (cancionActual) {
            Cancion actual = *cancionActual;
            delete cancionActual;
            
            // Encolar la canción actual al principio de la cola
            Cola<Cancion> nuevaCola;
            nuevaCola.encolar(actual);
            
            // Copiar el resto de la cola
            while (!colaReproduccion.estaVacia()) {
                Cancion temp;
                colaReproduccion.frenteCola(temp);
                colaReproduccion.desencolar();
                nuevaCola.encolar(temp);
            }
            
            colaReproduccion = nuevaCola;
        }
        
        // Obtener la canción anterior del historial
        Cancion anterior;
        historial.cimaPila(anterior);
        historial.desapilar();
        
        cancionActual = new Cancion(anterior);
        reproduciendo = true;
        pausado = false;
        posicionActual = 0;
        
        return true;
    }
    
    /**
     * @brief Establece el volumen
     * @param _volumen Nuevo volumen (0-100)
     * @return true si se estableció correctamente, false en caso contrario
     */
    bool establecerVolumen(int _volumen) {
        if (_volumen < 0 || _volumen > 100) {
            return false;
        }
        
        volumen = _volumen;
        return true;
    }
    
    /**
     * @brief Establece la posición en la canción
     * @param _posicion Nueva posición en segundos
     * @return true si se estableció correctamente, false en caso contrario
     */
    bool establecerPosicion(int _posicion) {
        if (!cancionActual || _posicion < 0 || _posicion > cancionActual->obtenerDuracionSegundos()) {
            return false;
        }
        
        posicionActual = _posicion;
        return true;
    }
    
    /**
     * @brief Encola una canción para reproducción
     * @param posicion Posición de la canción en la biblioteca
     * @return true si se encoló correctamente, false en caso contrario
     */
    bool encolarCancion(int posicion) {
        Cancion cancion;
        if (biblioteca->obtenerCancion(posicion, cancion)) {
            colaReproduccion.encolar(cancion);
            return true;
        }
        
        return false;
    }
    
    /**
     * @brief Encola una playlist completa para reproducción
     * @param posicion Posición de la playlist
     * @return true si se encoló correctamente, false en caso contrario
     */
    bool encolarPlaylist(int posicion) {
        Playlist playlist;
        if (biblioteca->obtenerPlaylist(posicion, playlist)) {
            int numCanciones = playlist.obtenerNumeroCanciones();
            
            for (int i = 0; i < numCanciones; i++) {
                Cancion cancion;
                if (playlist.obtenerCancion(i, cancion)) {
                    colaReproduccion.encolar(cancion);
                }
            }
            
            return true;
        }
        
        return false;
    }
    
    /**
     * @brief Vacía la cola de reproducción
     */
    void vaciarCola() {
        while (!colaReproduccion.estaVacia()) {
            colaReproduccion.desencolar();
        }
    }
    
    /**
     * @brief Obtiene la canción actual
     * @return Puntero a la canción actual o nullptr si no hay
     */
    const Cancion* obtenerCancionActual() const {
        return cancionActual;
    }
    
    /**
     * @brief Verifica si está reproduciendo
     * @return true si está reproduciendo, false en caso contrario
     */
    bool estaReproduciendo() const {
        return reproduciendo && !pausado;
    }
    
    /**
     * @brief Verifica si está pausado
     * @return true si está pausado, false en caso contrario
     */
    bool estaPausado() const {
        return pausado;
    }
    
    /**
     * @brief Obtiene el volumen actual
     * @return Volumen actual (0-100)
     */
    int obtenerVolumen() const {
        return volumen;
    }
    
    /**
     * @brief Obtiene la posición actual en la canción
     * @return Posición actual en segundos
     */
    int obtenerPosicionActual() const {
        return posicionActual;
    }
    
    /**
     * @brief Obtiene el tamaño de la cola de reproducción
     * @return Número de canciones en la cola
     */
    int obtenerTamanoCola() const {
        return colaReproduccion.obtenerTamano();
    }
    
    /**
     * @brief Obtiene el tamaño del historial
     * @return Número de canciones en el historial
     */
    int obtenerTamanoHistorial() const {
        return historial.obtenerTamano();
    }
    
private:
    /**
     * @brief Agrega una canción al historial
     * @param cancion Canción a agregar
     */
    void agregarAlHistorial(const Cancion& cancion) {
        // Si el historial está lleno, eliminar la canción más antigua
        if (historial.obtenerTamano() >= limiteHistorial) {
            // No podemos eliminar directamente la canción más antigua en una pila
            // Así que creamos una pila temporal y transferimos todas menos la última
            Pila<Cancion> temp;
            int cantidadATransferir = historial.obtenerTamano() - 1;
            
            for (int i = 0; i < cantidadATransferir; i++) {
                Cancion c;
                historial.cimaPila(c);
                historial.desapilar();
                temp.apilar(c);
            }
            
            // Descartar la canción más antigua
            historial.desapilar();
            
            // Restaurar el historial
            while (!temp.estaVacia()) {
                Cancion c;
                temp.cimaPila(c);
                temp.desapilar();
                historial.apilar(c);
            }
        }
        
        historial.apilar(cancion);
    }
};

#endif // REPRODUCTOR_MUSICA_H
