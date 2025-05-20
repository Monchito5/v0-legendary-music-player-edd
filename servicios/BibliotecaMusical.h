#ifndef BIBLIOTECA_MUSICAL_H
#define BIBLIOTECA_MUSICAL_H

#include <string>
#include <functional>
#include <ctime>
#include <cstdlib>

#include "../estructuras/Lista.h"
#include "../estructuras/Pila.h"
#include "../estructuras/Cola.h"
#include "../estructuras/Grafo.h"
#include "../modelos/Cancion.h"
#include "../modelos/ListaReproduccion.h"
#include "../algoritmos/Busqueda.h"
#include "../algoritmos/Ordenamiento.h"
#include "UTF8Util.h"

class BibliotecaMusical {
private:
    Lista<Cancion> canciones;
    Lista<ListaReproduccion> listasReproduccion;
    Pila<int> historial;
    Cola<int> colaReproduccion;
    Grafo<std::string> grafoAfinidad;
    
    int cancionActual;
    bool reproduciendo;
    
    // Método para cargar datos ficticios
    void cargarDatosFicticios() {
        // Canciones ficticias
        Cancion cancion1("Bohemian Rhapsody", "Queen", "A Night at the Opera", 1975, 355);
        cancion1.generos.agregar("Rock");
        cancion1.generos.agregar("Progresivo");
        
        Cancion cancion2("Imagine", "John Lennon", "Imagine", 1971, 183);
        cancion2.generos.agregar("Rock");
        cancion2.generos.agregar("Pop");
        
        Cancion cancion3("Billie Jean", "Michael Jackson", "Thriller", 1982, 294);
        cancion3.generos.agregar("Pop");
        cancion3.generos.agregar("Funk");
        
        Cancion cancion4("Hotel California", "Eagles", "Hotel California", 1976, 390);
        cancion4.generos.agregar("Rock");
        
        Cancion cancion5("Sweet Child O' Mine", "Guns N' Roses", "Appetite for Destruction", 1987, 356);
        cancion5.generos.agregar("Rock");
        cancion5.generos.agregar("Hard Rock");
        
        Cancion cancion6("Smells Like Teen Spirit", "Nirvana", "Nevermind", 1991, 301);
        cancion6.generos.agregar("Grunge");
        cancion6.generos.agregar("Rock Alternativo");
        
        Cancion cancion7("Like a Rolling Stone", "Bob Dylan", "Highway 61 Revisited", 1965, 379);
        cancion7.generos.agregar("Folk Rock");
        
        Cancion cancion8("I Want to Hold Your Hand", "The Beatles", "Meet the Beatles!", 1963, 146);
        cancion8.generos.agregar("Rock");
        cancion8.generos.agregar("Pop");
        
        Cancion cancion9("Purple Haze", "Jimi Hendrix", "Are You Experienced", 1967, 170);
        cancion9.generos.agregar("Rock Psicodélico");
        cancion9.generos.agregar("Hard Rock");
        
        Cancion cancion10("Johnny B. Goode", "Chuck Berry", "Chuck Berry Is on Top", 1958, 161);
        cancion10.generos.agregar("Rock and Roll");
        
        Cancion cancion11("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", 1971, 482);
        cancion11.generos.agregar("Rock");
        cancion11.generos.agregar("Hard Rock");
        
        Cancion cancion12("Respect", "Aretha Franklin", "I Never Loved a Man the Way I Love You", 1967, 148);
        cancion12.generos.agregar("Soul");
        cancion12.generos.agregar("R&B");
        
        Cancion cancion13("Good Vibrations", "The Beach Boys", "Smiley Smile", 1966, 217);
        cancion13.generos.agregar("Pop");
        cancion13.generos.agregar("Rock Psicodélico");
        
        Cancion cancion14("My Generation", "The Who", "My Generation", 1965, 198);
        cancion14.generos.agregar("Rock");
        
        Cancion cancion15("What's Going On", "Marvin Gaye", "What's Going On", 1971, 235);
        cancion15.generos.agregar("Soul");
        cancion15.generos.agregar("R&B");
        
        // Agregar canciones a la biblioteca
        agregarCancion(cancion1);
        agregarCancion(cancion2);
        agregarCancion(cancion3);
        agregarCancion(cancion4);
        agregarCancion(cancion5);
        agregarCancion(cancion6);
        agregarCancion(cancion7);
        agregarCancion(cancion8);
        agregarCancion(cancion9);
        agregarCancion(cancion10);
        agregarCancion(cancion11);
        agregarCancion(cancion12);
        agregarCancion(cancion13);
        agregarCancion(cancion14);
        agregarCancion(cancion15);
        
        // Listas de reproducción ficticias
        ListaReproduccion lista1("Clásicos del Rock", "Las mejores canciones de rock de todos los tiempos");
        lista1.agregarCancion(0);  // Bohemian Rhapsody
        lista1.agregarCancion(3);  // Hotel California
        lista1.agregarCancion(4);  // Sweet Child O' Mine
        lista1.agregarCancion(5);  // Smells Like Teen Spirit
        lista1.agregarCancion(10); // Stairway to Heaven
        
        ListaReproduccion lista2("Pop Hits", "Éxitos del pop a través de las décadas");
        lista2.agregarCancion(1);  // Imagine
        lista2.agregarCancion(2);  // Billie Jean
        lista2.agregarCancion(7);  // I Want to Hold Your Hand
        lista2.agregarCancion(12); // Good Vibrations
        
        ListaReproduccion lista3("Años 60", "Lo mejor de la década de los 60");
        lista3.agregarCancion(6);  // Like a Rolling Stone
        lista3.agregarCancion(7);  // I Want to Hold Your Hand
        lista3.agregarCancion(8);  // Purple Haze
        lista3.agregarCancion(9);  // Johnny B. Goode
        lista3.agregarCancion(12); // Good Vibrations
        lista3.agregarCancion(13); // My Generation
        
        ListaReproduccion lista4("Soul & R&B", "Clásicos del soul y rhythm and blues");
        lista4.agregarCancion(11); // Respect
        lista4.agregarCancion(14); // What's Going On
        
        // Agregar listas a la biblioteca
        listasReproduccion.agregar(lista1);
        listasReproduccion.agregar(lista2);
        listasReproduccion.agregar(lista3);
        listasReproduccion.agregar(lista4);
        
        // Construir grafo de afinidad
        construirGrafoAfinidad();
    }
    
public:
    // Constructor
    BibliotecaMusical() 
        : cancionActual(-1),
          reproduciendo(false) {
        
        cargarDatosFicticios();
    }
    
    // Destructor
    ~BibliotecaMusical() {
        // No es necesario guardar datos en esta versión simplificada
    }
    
    // Métodos para gestionar canciones
    void agregarCancion(const Cancion& cancion) {
        canciones.agregar(cancion);
        actualizarGrafoAfinidad(cancion);
    }
    
    bool eliminarCancion(int indice) {
        if (indice >= 0 && indice < canciones.obtenerTamanio()) {
            canciones.eliminar(indice);
            return true;
        }
        return false;
    }
    
    Cancion obtenerCancion(int indice) const {
        return canciones.obtener(indice);
    }
    
    int obtenerNumCanciones() const {
        return canciones.obtenerTamanio();
    }
    
    // Métodos para búsqueda de canciones
    Lista<int> buscarCancionesPorTitulo(const std::string& titulo) const {
        Lista<int> resultados;
        
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion cancion = canciones.obtener(i);
            if (Busqueda<Cancion>::contieneCadenaInsensible(cancion.titulo, titulo)) {
                resultados.agregar(i);
            }
        }
        
        return resultados;
    }
    
    Lista<int> buscarCancionesPorArtista(const std::string& artista) const {
        Lista<int> resultados;
        
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion cancion = canciones.obtener(i);
            if (Busqueda<Cancion>::contieneCadenaInsensible(cancion.artista, artista)) {
                resultados.agregar(i);
            }
        }
        
        return resultados;
    }
    
    Lista<int> buscarCancionesPorAlbum(const std::string& album) const {
        Lista<int> resultados;
        
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion cancion = canciones.obtener(i);
            if (Busqueda<Cancion>::contieneCadenaInsensible(cancion.album, album)) {
                resultados.agregar(i);
            }
        }
        
        return resultados;
    }
    
    bool contieneGenero(const Cancion& cancion, const std::string& genero) const {
        for (int i = 0; i < cancion.generos.obtenerTamanio(); i++) {
            if (Busqueda<Cancion>::contieneCadenaInsensible(cancion.generos.obtener(i), genero)) {
                return true;
            }
        }
        return false;
    }
    
    Lista<int> buscarCancionesPorGenero(const std::string& genero) const {
        Lista<int> resultados;
        
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion cancion = canciones.obtener(i);
            if (contieneGenero(cancion, genero)) {
                resultados.agregar(i);
            }
        }
        
        return resultados;
    }
    
    // Métodos para ordenamiento
    void ordenarPorTitulo(bool ascendente = true) {
        Ordenamiento<Cancion>::ordenarPorCampo(canciones, 
            [](const Cancion& a, const Cancion& b) -> bool {
                return a.compararPorTitulo(b);
            }, ascendente);
    }
    
    void ordenarPorArtista(bool ascendente = true) {
        Ordenamiento<Cancion>::ordenarPorCampo(canciones, 
            [](const Cancion& a, const Cancion& b) -> bool {
                return a.compararPorArtista(b);
            }, ascendente);
    }
    
    void ordenarPorAlbum(bool ascendente = true) {
        Ordenamiento<Cancion>::ordenarPorCampo(canciones, 
            [](const Cancion& a, const Cancion& b) -> bool {
                return a.compararPorAlbum(b);
            }, ascendente);
    }
    
    void ordenarPorAnio(bool ascendente = true) {
        Ordenamiento<Cancion>::ordenarPorCampo(canciones, 
            [](const Cancion& a, const Cancion& b) -> bool {
                return a.compararPorAnio(b);
            }, ascendente);
    }
    
    // Métodos para reproducción
    bool reproducir(int indice) {
        if (indice >= 0 && indice < canciones.obtenerTamanio()) {
            if (cancionActual >= 0) {
                historial.apilar(cancionActual);
            }
            cancionActual = indice;
            reproduciendo = true;
            return true;
        }
        return false;
    }
    
    bool pausar() {
        if (reproduciendo) {
            reproduciendo = false;
            return true;
        }
        return false;
    }
    
    bool reanudar() {
        if (cancionActual >= 0 && !reproduciendo) {
            reproduciendo = true;
            return true;
        }
        return false;
    }
    
    bool siguiente() {
        if (!colaReproduccion.estaVacia()) {
            if (cancionActual >= 0) {
                historial.apilar(cancionActual);
            }
            cancionActual = colaReproduccion.desencolar();
            reproduciendo = true;
            return true;
        } else if (cancionActual >= 0 && cancionActual < canciones.obtenerTamanio() - 1) {
            historial.apilar(cancionActual);
            cancionActual++;
            reproduciendo = true;
            return true;
        }
        return false;
    }
    
    bool anterior() {
        if (!historial.estaVacia()) {
            if (cancionActual >= 0) {
                colaReproduccion.encolar(cancionActual);
            }
            cancionActual = historial.desapilar();
            reproduciendo = true;
            return true;
        }
        return false;
    }
    
    int obtenerCancionActual() const {
        return cancionActual;
    }
    
    bool estaReproduciendo() const {
        return reproduciendo;
    }
    
    // Métodos para la cola de reproducción
    void encolarCancion(int indice) {
        if (indice >= 0 && indice < canciones.obtenerTamanio()) {
            colaReproduccion.encolar(indice);
        }
    }
    
    bool desencolarCancion() {
        if (!colaReproduccion.estaVacia()) {
            colaReproduccion.desencolar();
            return true;
        }
        return false;
    }
    
    int obtenerSiguienteEnCola() const {
        if (!colaReproduccion.estaVacia()) {
            return colaReproduccion.frente();
        }
        return -1;
    }
    
    int obtenerTamanioCola() const {
        return colaReproduccion.obtenerTamanio();
    }
    
    // Métodos para el historial
    int obtenerUltimaCancionHistorial() const {
        if (!historial.estaVacia()) {
            return historial.cima();
        }
        return -1;
    }
    
    int obtenerTamanioHistorial() const {
        return historial.obtenerTamanio();
    }
    
    void limpiarHistorial() {
        while (!historial.estaVacia()) {
            historial.desapilar();
        }
    }
    
    // Métodos para listas de reproducción
    void crearListaReproduccion(const std::string& nombre) {
        ListaReproduccion nuevaLista(nombre);
        listasReproduccion.agregar(nuevaLista);
    }
    
    bool eliminarListaReproduccion(int indice) {
        if (indice >= 0 && indice < listasReproduccion.obtenerTamanio()) {
            listasReproduccion.eliminar(indice);
            return true;
        }
        return false;
    }
    
    bool renombrarListaReproduccion(int indice, const std::string& nuevoNombre) {
        if (indice >= 0 && indice < listasReproduccion.obtenerTamanio()) {
            ListaReproduccion lista = listasReproduccion.obtener(indice);
            lista.nombre = nuevoNombre;
            listasReproduccion.modificar(indice, lista);
            return true;
        }
        return false;
    }
    
    bool agregarCancionALista(int indiceCancion, int indiceLista) {
        if (indiceCancion >= 0 && indiceCancion < canciones.obtenerTamanio() &&
            indiceLista >= 0 && indiceLista < listasReproduccion.obtenerTamanio()) {
            
            ListaReproduccion lista = listasReproduccion.obtener(indiceLista);
            lista.agregarCancion(indiceCancion);
            listasReproduccion.modificar(indiceLista, lista);
            return true;
        }
        return false;
    }
    
    bool eliminarCancionDeLista(int indiceCancion, int indiceLista) {
        if (indiceLista >= 0 && indiceLista < listasReproduccion.obtenerTamanio()) {
            ListaReproduccion lista = listasReproduccion.obtener(indiceLista);
            bool resultado = lista.eliminarCancion(indiceCancion);
            if (resultado) {
                listasReproduccion.modificar(indiceLista, lista);
            }
            return resultado;
        }
        return false;
    }
    
    ListaReproduccion obtenerListaReproduccion(int indice) const {
        return listasReproduccion.obtener(indice);
    }
    
    int obtenerNumListasReproduccion() const {
        return listasReproduccion.obtenerTamanio();
    }
    
    // Métodos para recomendaciones
    Lista<int> obtenerRecomendaciones(int indiceCancion, int cantidad) const {
        Lista<int> recomendaciones;
        
        if (indiceCancion < 0 || indiceCancion >= canciones.obtenerTamanio()) {
            return recomendaciones;
        }
        
        Cancion cancion = canciones.obtener(indiceCancion);
        
        // Obtener artistas y géneros similares
        Lista<std::string> artistasSimilares = grafoAfinidad.obtenerVecinosDFS(cancion.artista);
        
        Lista<std::string> generosSimilares;
        for (int i = 0; i < cancion.generos.obtenerTamanio(); i++) {
            std::string genero = cancion.generos.obtener(i);
            Lista<std::string> vecinos = grafoAfinidad.obtenerVecinosBFS(genero);
            for (int j = 0; j < vecinos.obtenerTamanio(); j++) {
                generosSimilares.agregar(vecinos.obtener(j));
            }
        }
        
        // Buscar canciones con artistas o géneros similares
        for (int i = 0; i < canciones.obtenerTamanio() && recomendaciones.obtenerTamanio() < cantidad; i++) {
            if (i != indiceCancion) {
                Cancion candidata = canciones.obtener(i);
                
                // Verificar si el artista es similar
                bool artistaSimilar = false;
                for (int j = 0; j < artistasSimilares.obtenerTamanio(); j++) {
                    if (candidata.artista == artistasSimilares.obtener(j)) {
                        artistaSimilar = true;
                        break;
                    }
                }
                
                // Verificar si algún género es similar
                bool generoSimilar = false;
                for (int j = 0; j < candidata.generos.obtenerTamanio(); j++) {
                    std::string generoCandidata = candidata.generos.obtener(j);
                    for (int k = 0; k < generosSimilares.obtenerTamanio(); k++) {
                        if (generoCandidata == generosSimilares.obtener(k)) {
                            generoSimilar = true;
                            break;
                        }
                    }
                    if (generoSimilar) break;
                }
                
                if (artistaSimilar || generoSimilar) {
                    recomendaciones.agregar(i);
                }
            }
        }
        
        return recomendaciones;
    }
    
private:
    // Métodos privados para el grafo de afinidad
    void construirGrafoAfinidad() {
        grafoAfinidad.vaciar();
        
        // Agregar todos los artistas y géneros como vértices
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion cancion = canciones.obtener(i);
            
            if (!grafoAfinidad.existeVertice(cancion.artista)) {
                grafoAfinidad.agregarVertice(cancion.artista);
            }
            
            for (int j = 0; j < cancion.generos.obtenerTamanio(); j++) {
                std::string genero = cancion.generos.obtener(j);
                if (!grafoAfinidad.existeVertice(genero)) {
                    grafoAfinidad.agregarVertice(genero);
                }
            }
        }
        
        // Conectar artistas con sus géneros
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion cancion = canciones.obtener(i);
            
            for (int j = 0; j < cancion.generos.obtenerTamanio(); j++) {
                std::string genero = cancion.generos.obtener(j);
                grafoAfinidad.agregarArista(cancion.artista, genero);
            }
        }
        
        // Conectar artistas que comparten géneros
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion cancion1 = canciones.obtener(i);
            
            for (int j = i + 1; j < canciones.obtenerTamanio(); j++) {
                Cancion cancion2 = canciones.obtener(j);
                
                if (cancion1.artista != cancion2.artista) {
                    bool compartenGenero = false;
                    
                    for (int k = 0; k < cancion1.generos.obtenerTamanio() && !compartenGenero; k++) {
                        std::string genero1 = cancion1.generos.obtener(k);
                        
                        for (int l = 0; l < cancion2.generos.obtenerTamanio() && !compartenGenero; l++) {
                            std::string genero2 = cancion2.generos.obtener(l);
                            
                            if (genero1 == genero2) {
                                compartenGenero = true;
                            }
                        }
                    }
                    
                    if (compartenGenero) {
                        grafoAfinidad.agregarArista(cancion1.artista, cancion2.artista);
                    }
                }
            }
        }
    }
    
    void actualizarGrafoAfinidad(const Cancion& cancion) {
        // Agregar artista si no existe
        if (!grafoAfinidad.existeVertice(cancion.artista)) {
            grafoAfinidad.agregarVertice(cancion.artista);
        }
        
        // Agregar géneros si no existen y conectarlos con el artista
        for (int i = 0; i < cancion.generos.obtenerTamanio(); i++) {
            std::string genero = cancion.generos.obtener(i);
            
            if (!grafoAfinidad.existeVertice(genero)) {
                grafoAfinidad.agregarVertice(genero);
            }
            
            grafoAfinidad.agregarArista(cancion.artista, genero);
        }
        
        // Conectar con otros artistas que comparten géneros
        for (int i = 0; i < canciones.obtenerTamanio(); i++) {
            Cancion otraCancion = canciones.obtener(i);
            
            if (otraCancion.artista != cancion.artista) {
                bool compartenGenero = false;
                
                for (int j = 0; j < cancion.generos.obtenerTamanio() && !compartenGenero; j++) {
                    std::string genero1 = cancion.generos.obtener(j);
                    
                    for (int k = 0; k < otraCancion.generos.obtenerTamanio() && !compartenGenero; k++) {
                        std::string genero2 = otraCancion.generos.obtener(k);
                        
                        if (genero1 == genero2) {
                            compartenGenero = true;
                        }
                    }
                }
                
                if (compartenGenero) {
                    grafoAfinidad.agregarArista(cancion.artista, otraCancion.artista);
                }
            }
        }
    }
};

#endif // BIBLIOTECA_MUSICAL_H