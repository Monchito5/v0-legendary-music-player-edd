/**
 * @file InterfazConsola.h
 * @brief Definición de la clase InterfazConsola para la interfaz de usuario en consola
 * @author v0
 * @date Mayo 2025
 */

#ifndef INTERFAZ_CONSOLA_H
#define INTERFAZ_CONSOLA_H

#include <iostream>
#include <string>
#include <iomanip>
#include "../servicios/BibliotecaMusical.h"
#include "../servicios/ReproductorMusica.h"

/**
 * @brief Clase que implementa la interfaz de usuario en consola
 */
class InterfazConsola {
private:
    BibliotecaMusical* biblioteca;     ///< Puntero a la biblioteca musical
    ReproductorMusica* reproductor;    ///< Puntero a el reproductor de música
    bool ejecutando;                   ///< Indica si la aplicación está en ejecución
    
public:
    /**
     * @brief Constructor con parámetros
     * @param _biblioteca Puntero a la biblioteca musical
     * @param _reproductor Puntero a el reproductor de música
     */
    InterfazConsola(BibliotecaMusical* _biblioteca, ReproductorMusica* _reproductor)
        : biblioteca(_biblioteca), reproductor(_reproductor), ejecutando(false) {}
    
    /**
     * @brief Inicia la interfaz de usuario
     */
    void iniciar() {
        ejecutando = true;
        
        while (ejecutando) {
            mostrarMenuPrincipal();
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1:
                    menuBiblioteca();
                    break;
                case 2:
                    menuPlaylists();
                    break;
                case 3:
                    menuReproduccion();
                    break;
                case 4:
                    menuBusqueda();
                    break;
                case 5:
                    menuOrdenamiento();
                    break;
                case 0:
                    ejecutando = false;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
            }
        }
        
        // Guardar la biblioteca antes de salir
        biblioteca->guardarBiblioteca();
        std::cout << "¡Hasta pronto!" << std::endl;
    }
    
private:
    /**
     * @brief Muestra el menú principal
     */
    void mostrarMenuPrincipal() const {
        limpiarPantalla();
        mostrarCabecera("REPRODUCTOR DE MÚSICA LEGENDARIO");
        
        // Mostrar información de reproducción actual
        mostrarInfoReproduccion();
        
        std::cout << "\nMENÚ PRINCIPAL\n";
        std::cout << "1. Biblioteca\n";
        std::cout << "2. Playlists\n";
        std::cout << "3. Reproducción\n";
        std::cout << "4. Búsqueda\n";
        std::cout << "5. Ordenamiento\n";
        std::cout << "0. Salir\n";
        std::cout << "\nSeleccione una opción: ";
    }
    
    /**
     * @brief Muestra el menú de biblioteca
     */
    void menuBiblioteca() {
        bool regresarMenuPrincipal = false;
        
        while (!regresarMenuPrincipal) {
            limpiarPantalla();
            mostrarCabecera("BIBLIOTECA MUSICAL");
            
            // Mostrar información de reproducción actual
            mostrarInfoReproduccion();
            
            // Mostrar canciones
            mostrarCanciones();
            
            std::cout << "\nOPCIONES DE BIBLIOTECA\n";
            std::cout << "1. Reproducir canción\n";
            std::cout << "2. Encolar canción\n";
            std::cout << "3. Agregar canción a playlist\n";
            std::cout << "0. Volver al menú principal\n";
            std::cout << "\nSeleccione una opción: ";
            
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1: {
                    std::cout << "Ingrese el número de la canción a reproducir: ";
                    int numCancion = leerOpcion();
                    
                    if (numCancion >= 0 && numCancion < biblioteca->obtenerNumeroCanciones()) {
                        reproductor->reproducir(numCancion);
                        std::cout << "Reproduciendo canción..." << std::endl;
                    } else {
                        std::cout << "Número de canción inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 2: {
                    std::cout << "Ingrese el número de la canción a encolar: ";
                    int numCancion = leerOpcion();
                    
                    if (numCancion >= 0 && numCancion < biblioteca->obtenerNumeroCanciones()) {
                        reproductor->encolarCancion(numCancion);
                        std::cout << "Canción encolada." << std::endl;
                    } else {
                        std::cout << "Número de canción inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 3: {
                    if (biblioteca->obtenerNumeroPlaylists() == 0) {
                        std::cout << "No hay playlists disponibles. Cree una primero." << std::endl;
                        pausar();
                        break;
                    }
                    
                    // Mostrar playlists disponibles
                    std::cout << "\nPlaylists disponibles:\n";
                    for (int i = 0; i < biblioteca->obtenerNumeroPlaylists(); i++) {
                        Playlist playlist;
                        biblioteca->obtenerPlaylist(i, playlist);
                        std::cout << i << ". " << playlist.obtenerNombre() << std::endl;
                    }
                    
                    std::cout << "Ingrese el número de la playlist: ";
                    int numPlaylist = leerOpcion();
                    
                    if (numPlaylist >= 0 && numPlaylist < biblioteca->obtenerNumeroPlaylists()) {
                        std::cout << "Ingrese el número de la canción a agregar: ";
                        int numCancion = leerOpcion();
                        
                        if (numCancion >= 0 && numCancion < biblioteca->obtenerNumeroCanciones()) {
                            biblioteca->agregarCancionAPlaylist(numPlaylist, numCancion);
                            std::cout << "Canción agregada a la playlist." << std::endl;
                        } else {
                            std::cout << "Número de canción inválido." << std::endl;
                        }
                    } else {
                        std::cout << "Número de playlist inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 0:
                    regresarMenuPrincipal = true;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                    pausar();
            }
        }
    }
    
    /**
     * @brief Muestra el menú de playlists
     */
    void menuPlaylists() {
        bool regresarMenuPrincipal = false;
        
        while (!regresarMenuPrincipal) {
            limpiarPantalla();
            mostrarCabecera("PLAYLISTS");
            
            // Mostrar información de reproducción actual
            mostrarInfoReproduccion();
            
            // Mostrar playlists
            mostrarPlaylists();
            
            std::cout << "\nOPCIONES DE PLAYLISTS\n";
            std::cout << "1. Crear playlist\n";
            std::cout << "2. Renombrar playlist\n";
            std::cout << "3. Eliminar playlist\n";
            std::cout << "4. Ver contenido de playlist\n";
            std::cout << "5. Reproducir playlist\n";
            std::cout << "6. Encolar playlist\n";
            std::cout << "0. Volver al menú principal\n";
            std::cout << "\nSeleccione una opción: ";
            
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1: {
                    std::cout << "Ingrese el nombre de la nueva playlist: ";
                    std::string nombre;
                    std::cin.ignore();
                    std::getline(std::cin, nombre);
                    
                    if (biblioteca->crearPlaylist(nombre)) {
                        std::cout << "Playlist creada correctamente." << std::endl;
                    } else {
                        std::cout << "Error al crear la playlist. El nombre ya existe." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 2: {
                    if (biblioteca->obtenerNumeroPlaylists() == 0) {
                        std::cout << "No hay playlists disponibles." << std::endl;
                        pausar();
                        break;
                    }
                    
                    std::cout << "Ingrese el número de la playlist a renombrar: ";
                    int numPlaylist = leerOpcion();
                    
                    if (numPlaylist >= 0 && numPlaylist < biblioteca->obtenerNumeroPlaylists()) {
                        std::cout << "Ingrese el nuevo nombre: ";
                        std::string nombre;
                        std::cin.ignore();
                        std::getline(std::cin, nombre);
                        
                        if (biblioteca->renombrarPlaylist(numPlaylist, nombre)) {
                            std::cout << "Playlist renombrada correctamente." << std::endl;
                        } else {
                            std::cout << "Error al renombrar la playlist." << std::endl;
                        }
                    } else {
                        std::cout << "Número de playlist inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 3: {
                    if (biblioteca->obtenerNumeroPlaylists() == 0) {
                        std::cout << "No hay playlists disponibles." << std::endl;
                        pausar();
                        break;
                    }
                    
                    std::cout << "Ingrese el número de la playlist a eliminar: ";
                    int numPlaylist = leerOpcion();
                    
                    if (numPlaylist >= 0 && numPlaylist < biblioteca->obtenerNumeroPlaylists()) {
                        if (biblioteca->eliminarPlaylist(numPlaylist)) {
                            std::cout << "Playlist eliminada correctamente." << std::endl;
                        } else {
                            std::cout << "Error al eliminar la playlist." << std::endl;
                        }
                    } else {
                        std::cout << "Número de playlist inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 4: {
                    if (biblioteca->obtenerNumeroPlaylists() == 0) {
                        std::cout << "No hay playlists disponibles." << std::endl;
                        pausar();
                        break;
                    }
                    
                    std::cout << "Ingrese el número de la playlist a ver: ";
                    int numPlaylist = leerOpcion();
                    
                    if (numPlaylist >= 0 && numPlaylist < biblioteca->obtenerNumeroPlaylists()) {
                        mostrarContenidoPlaylist(numPlaylist);
                    } else {
                        std::cout << "Número de playlist inválido." << std::endl;
                        pausar();
                    }
                    
                    break;
                }
                case 5: {
                    if (biblioteca->obtenerNumeroPlaylists() == 0) {
                        std::cout << "No hay playlists disponibles." << std::endl;
                        pausar();
                        break;
                    }
                    
                    std::cout << "Ingrese el número de la playlist a reproducir: ";
                    int numPlaylist = leerOpcion();
                    
                    if (numPlaylist >= 0 && numPlaylist < biblioteca->obtenerNumeroPlaylists()) {
                        Playlist playlist;
                        biblioteca->obtenerPlaylist(numPlaylist, playlist);
                        
                        if (playlist.obtenerNumeroCanciones() > 0) {
                            reproductor->reproducirDePlaylist(numPlaylist, 0);
                            std::cout << "Reproduciendo primera canción de la playlist..." << std::endl;
                        } else {
                            std::cout << "La playlist está vacía." << std::endl;
                        }
                    } else {
                        std::cout << "Número de playlist inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 6: {
                    if (biblioteca->obtenerNumeroPlaylists() == 0) {
                        std::cout << "No hay playlists disponibles." << std::endl;
                        pausar();
                        break;
                    }
                    
                    std::cout << "Ingrese el número de la playlist a encolar: ";
                    int numPlaylist = leerOpcion();
                    
                    if (numPlaylist >= 0 && numPlaylist < biblioteca->obtenerNumeroPlaylists()) {
                        reproductor->encolarPlaylist(numPlaylist);
                        std::cout << "Playlist encolada." << std::endl;
                    } else {
                        std::cout << "Número de playlist inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 0:
                    regresarMenuPrincipal = true;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                    pausar();
            }
        }
    }
    
    /**
     * @brief Muestra el menú de reproducción
     */
    void menuReproduccion() {
        bool regresarMenuPrincipal = false;
        
        while (!regresarMenuPrincipal) {
            limpiarPantalla();
            mostrarCabecera("REPRODUCCIÓN");
            
            // Mostrar información de reproducción actual
            mostrarInfoReproduccion();
            
            // Mostrar cola de reproducción
            mostrarColaReproduccion();
            
            std::cout << "\nOPCIONES DE REPRODUCCIÓN\n";
            std::cout << "1. Reproducir/Pausar\n";
            std::cout << "2. Detener\n";
            std::cout << "3. Siguiente\n";
            std::cout << "4. Anterior\n";
            std::cout << "5. Ajustar volumen\n";
            std::cout << "6. Ajustar posición\n";
            std::cout << "7. Vaciar cola\n";
            std::cout << "8. Ver recomendaciones\n";
            std::cout << "0. Volver al menú principal\n";
            std::cout << "\nSeleccione una opción: ";
            
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1: {
                    if (reproductor->obtenerCancionActual()) {
                        reproductor->pausarReanudar();
                        std::cout << (reproductor->estaPausado() ? "Pausado." : "Reproduciendo.") << std::endl;
                    } else {
                        std::cout << "No hay canción en reproducción." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 2: {
                    if (reproductor->obtenerCancionActual()) {
                        reproductor->detener();
                        std::cout << "Reproducción detenida." << std::endl;
                    } else {
                        std::cout << "No hay canción en reproducción." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 3: {
                    if (reproductor->siguiente()) {
                        std::cout << "Reproduciendo siguiente canción." << std::endl;
                    } else {
                        std::cout << "No hay más canciones en la cola." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 4: {
                    if (reproductor->anterior()) {
                        std::cout << "Reproduciendo canción anterior." << std::endl;
                    } else {
                        std::cout << "No hay canciones anteriores en el historial." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 5: {
                    std::cout << "Volumen actual: " << reproductor->obtenerVolumen() << std::endl;
                    std::cout << "Ingrese el nuevo volumen (0-100): ";
                    int volumen = leerOpcion();
                    
                    if (reproductor->establecerVolumen(volumen)) {
                        std::cout << "Volumen ajustado a " << volumen << "." << std::endl;
                    } else {
                        std::cout << "Valor de volumen inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 6: {
                    if (!reproductor->obtenerCancionActual()) {
                        std::cout << "No hay canción en reproducción." << std::endl;
                        pausar();
                        break;
                    }
                    
                    int duracion = reproductor->obtenerCancionActual()->obtenerDuracionSegundos();
                    std::cout << "Posición actual: " << reproductor->obtenerPosicionActual() 
                              << " / " << duracion << " segundos" << std::endl;
                    
                    std::cout << "Ingrese la nueva posición (0-" << duracion << "): ";
                    int posicion = leerOpcion();
                    
                    if (reproductor->establecerPosicion(posicion)) {
                        std::cout << "Posición ajustada a " << posicion << " segundos." << std::endl;
                    } else {
                        std::cout << "Valor de posición inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 7: {
                    reproductor->vaciarCola();
                    std::cout << "Cola de reproducción vaciada." << std::endl;
                    pausar();
                    break;
                }
                case 8: {
                    mostrarRecomendaciones();
                    break;
                }
                case 0:
                    regresarMenuPrincipal = true;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                    pausar();
            }
        }
    }
    
    /**
     * @brief Muestra el menú de búsqueda
     */
    void menuBusqueda() {
        bool regresarMenuPrincipal = false;
        
        while (!regresarMenuPrincipal) {
            limpiarPantalla();
            mostrarCabecera("BÚSQUEDA");
            
            // Mostrar información de reproducción actual
            mostrarInfoReproduccion();
            
            std::cout << "\nOPCIONES DE BÚSQUEDA\n";
            std::cout << "1. Buscar por título\n";
            std::cout << "2. Buscar por artista\n";
            std::cout << "3. Buscar por álbum\n";
            std::cout << "4. Buscar por género\n";
            std::cout << "0. Volver al menú principal\n";
            std::cout << "\nSeleccione una opción: ";
            
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1: {
                    std::cout << "Ingrese el título a buscar: ";
                    std::string titulo;
                    std::cin.ignore();
                    std::getline(std::cin, titulo);
                    
                    Lista<int> resultados = biblioteca->buscarCancionesPorTitulo(titulo);
                    mostrarResultadosBusqueda(resultados);
                    break;
                }
                case 2: {
                    std::cout << "Ingrese el artista a buscar: ";
                    std::string artista;
                    std::cin.ignore();
                    std::getline(std::cin, artista);
                    
                    Lista<int> resultados = biblioteca->buscarCancionesPorArtista(artista);
                    mostrarResultadosBusqueda(resultados);
                    break;
                }
                case 3: {
                    std::cout << "Ingrese el álbum a buscar: ";
                    std::string album;
                    std::cin.ignore();
                    std::getline(std::cin, album);
                    
                    Lista<int> resultados = biblioteca->buscarCancionesPorAlbum(album);
                    mostrarResultadosBusqueda(resultados);
                    break;
                }
                case 4: {
                    std::cout << "Ingrese el género a buscar: ";
                    std::string genero;
                    std::cin.ignore();
                    std::getline(std::cin, genero);
                    
                    Lista<int> resultados = biblioteca->buscarCancionesPorGenero(genero);
                    mostrarResultadosBusqueda(resultados);
                    break;
                }
                case 0:
                    regresarMenuPrincipal = true;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                    pausar();
            }
        }
    }
    
    /**
     * @brief Muestra el menú de ordenamiento
     */
    void menuOrdenamiento() {
        bool regresarMenuPrincipal = false;
        
        while (!regresarMenuPrincipal) {
            limpiarPantalla();
            mostrarCabecera("ORDENAMIENTO");
            
            // Mostrar información de reproducción actual
            mostrarInfoReproduccion();
            
            std::cout << "\nOPCIONES DE ORDENAMIENTO\n";
            std::cout << "1. Ordenar por título (Bubble Sort)\n";
            std::cout << "2. Ordenar por título (Insertion Sort)\n";
            std::cout << "3. Ordenar por título (Quick Sort)\n";
            std::cout << "4. Ordenar por título (Merge Sort)\n";
            std::cout << "0. Volver al menú principal\n";
            std::cout << "\nSeleccione una opción: ";
            
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1: {
                    std::cout << "Ordenando por título (Bubble Sort)..." << std::endl;
                    biblioteca->ordenarCancionesPorTitulo(true, 1);
                    std::cout << "Ordenamiento completado." << std::endl;
                    pausar();
                    break;
                }
                case 2: {
                    std::cout << "Ordenando por título (Insertion Sort)..." << std::endl;
                    biblioteca->ordenarCancionesPorTitulo(true, 2);
                    std::cout << "Ordenamiento completado." << std::endl;
                    pausar();
                    break;
                }
                case 3: {
                    std::cout << "Ordenando por título (Quick Sort)..." << std::endl;
                    biblioteca->ordenarCancionesPorTitulo(true, 3);
                    std::cout << "Ordenamiento completado." << std::endl;
                    pausar();
                    break;
                }
                case 4: {
                    std::cout << "Ordenando por título (Merge Sort)..." << std::endl;
                    biblioteca->ordenarCancionesPorTitulo(true, 4);
                    std::cout << "Ordenamiento completado." << std::endl;
                    pausar();
                    break;
                }
                case 0:
                    regresarMenuPrincipal = true;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                    pausar();
            }
        }
    }
    
    /**
     * @brief Muestra las canciones de la biblioteca
     */
    void mostrarCanciones() const {
        int numCanciones = biblioteca->obtenerNumeroCanciones();
        
        if (numCanciones == 0) {
            std::cout << "\nNo hay canciones en la biblioteca." << std::endl;
            return;
        }
        
        std::cout << "\nCANCIONES EN LA BIBLIOTECA (" << numCanciones << ")\n";
        std::cout << std::setw(5) << "ID" << " | "
                  << std::setw(30) << "TÍTULO" << " | "
                  << std::setw(20) << "ARTISTA" << " | "
                  << std::setw(20) << "ÁLBUM" << " | "
                  << std::setw(5) << "AÑO" << " | "
                  << std::setw(8) << "DURACIÓN" << std::endl;
        std::cout << std::string(95, '-') << std::endl;
        
        for (int i = 0; i < numCanciones; i++) {
            Cancion cancion;
            biblioteca->obtenerCancion(i, cancion);
            
            std::cout << std::setw(5) << i << " | "
                      << std::setw(30) << (cancion.obtenerTitulo().length() > 27 ? 
                                          cancion.obtenerTitulo().substr(0, 27) + "..." : 
                                          cancion.obtenerTitulo()) << " | "
                      << std::setw(20) << (cancion.obtenerArtista().length() > 17 ? 
                                          cancion.obtenerArtista().substr(0, 17) + "..." : 
                                          cancion.obtenerArtista()) << " | "
                      << std::setw(20) << (cancion.obtenerAlbum().length() > 17 ? 
                                          cancion.obtenerAlbum().substr(0, 17) + "..." : 
                                          cancion.obtenerAlbum()) << " | "
                      << std::setw(5) << cancion.obtenerAnio() << " | "
                      << std::setw(8) << cancion.obtenerDuracionFormateada() << std::endl;
        }
    }
    
    /**
     * @brief Muestra las playlists
     */
    void mostrarPlaylists() const {
        int numPlaylists = biblioteca->obtenerNumeroPlaylists();
        
        if (numPlaylists == 0) {
            std::cout << "\nNo hay playlists." << std::endl;
            return;
        }
        
        std::cout << "\nPLAYLISTS (" << numPlaylists << ")\n";
        std::cout << std::setw(5) << "ID" << " | "
                  << std::setw(30) << "NOMBRE" << " | "
                  << std::setw(15) << "CANCIONES" << " | "
                  << std::setw(10) << "DURACIÓN" << std::endl;
        std::cout << std::string(65, '-') << std::endl;
        
        for (int i = 0; i < numPlaylists; i++) {
            Playlist playlist;
            biblioteca->obtenerPlaylist(i, playlist);
            
            std::cout << std::setw(5) << i << " | "
                      << std::setw(30) << (playlist.obtenerNombre().length() > 27 ? 
                                          playlist.obtenerNombre().substr(0, 27) + "..." : 
                                          playlist.obtenerNombre()) << " | "
                      << std::setw(15) << playlist.obtenerNumeroCanciones() << " | "
                      << std::setw(10) << playlist.obtenerDuracionTotalFormateada() << std::endl;
        }
    }
    
    /**
     * @brief Muestra el contenido de una playlist
     * @param posicion Posición de la playlist
     */
    void mostrarContenidoPlaylist(int posicion) {
        Playlist playlist;
        if (!biblioteca->obtenerPlaylist(posicion, playlist)) {
            std::cout << "Error al obtener la playlist." << std::endl;
            pausar();
            return;
        }
        
        bool regresarMenuPlaylists = false;
        
        while (!regresarMenuPlaylists) {
            limpiarPantalla();
            mostrarCabecera("PLAYLIST: " + playlist.obtenerNombre());
            
            int numCanciones = playlist.obtenerNumeroCanciones();
            
            if (numCanciones == 0) {
                std::cout << "\nNo hay canciones en esta playlist." << std::endl;
            } else {
                std::cout << "\nCANCIONES EN LA PLAYLIST (" << numCanciones << ")\n";
                std::cout << std::setw(5) << "ID" << " | "
                          << std::setw(30) << "TÍTULO" << " | "
                          << std::setw(20) << "ARTISTA" << " | "
                          << std::setw(20) << "ÁLBUM" << " | "
                          << std::setw(8) << "DURACIÓN" << std::endl;
                std::cout << std::string(85, '-') << std::endl;
                
                for (int i = 0; i < numCanciones; i++) {
                    Cancion cancion;
                    playlist.obtenerCancion(i, cancion);
                    
                    std::cout << std::setw(5) << i << " | "
                              << std::setw(30) << (cancion.obtenerTitulo().length() > 27 ? 
                                                  cancion.obtenerTitulo().substr(0, 27) + "..." : 
                                                  cancion.obtenerTitulo()) << " | "
                              << std::setw(20) << (cancion.obtenerArtista().length() > 17 ? 
                                                  cancion.obtenerArtista().substr(0, 17) + "..." : 
                                                  cancion.obtenerArtista()) << " | "
                              << std::setw(20) << (cancion.obtenerAlbum().length() > 17 ? 
                                                  cancion.obtenerAlbum().substr(0, 17) + "..." : 
                                                  cancion.obtenerAlbum()) << " | "
                              << std::setw(8) << cancion.obtenerDuracionFormateada() << std::endl;
                }
            }
            
            std::cout << "\nOPCIONES DE PLAYLIST\n";
            std::cout << "1. Reproducir canción\n";
            std::cout << "2. Eliminar canción\n";
            std::cout << "0. Volver al menú de playlists\n";
            std::cout << "\nSeleccione una opción: ";
            
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1: {
                    if (numCanciones == 0) {
                        std::cout << "No hay canciones para reproducir." << std::endl;
                        pausar();
                        break;
                    }
                    
                    std::cout << "Ingrese el número de la canción a reproducir: ";
                    int numCancion = leerOpcion();
                    
                    if (numCancion >= 0 && numCancion < numCanciones) {
                        reproductor->reproducirDePlaylist(posicion, numCancion);
                        std::cout << "Reproduciendo canción..." << std::endl;
                    } else {
                        std::cout << "Número de canción inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 2: {
                    if (numCanciones == 0) {
                        std::cout << "No hay canciones para eliminar." << std::endl;
                        pausar();
                        break;
                    }
                    
                    std::cout << "Ingrese el número de la canción a eliminar: ";
                    int numCancion = leerOpcion();
                    
                    if (numCancion >= 0 && numCancion < numCanciones) {
                        if (biblioteca->eliminarCancionDePlaylist(posicion, numCancion)) {
                            std::cout << "Canción eliminada de la playlist." << std::endl;
                        } else {
                            std::cout << "Error al eliminar la canción." << std::endl;
                        }
                    } else {
                        std::cout << "Número de canción inválido." << std::endl;
                    }
                    
                    pausar();
                    break;
                }
                case 0:
                    regresarMenuPlaylists = true;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                    pausar();
            }
        }
    }
    
    /**
     * @brief Muestra la información de reproducción actual
     */
    void mostrarInfoReproduccion() const {
        const Cancion* cancionActual = reproductor->obtenerCancionActual();
        
        std::cout << "\nREPRODUCCIÓN ACTUAL\n";
        
        if (cancionActual) {
            std::cout << "Título: " << cancionActual->obtenerTitulo() << std::endl;
            std::cout << "Artista: " << cancionActual->obtenerArtista() << std::endl;
            std::cout << "Estado: " << (reproductor->estaReproduciendo() ? "Reproduciendo" : 
                                      (reproductor->estaPausado() ? "Pausado" : "Detenido")) << std::endl;
            std::cout << "Volumen: " << reproductor->obtenerVolumen() << "%" << std::endl;
            std::cout << "Posición: " << reproductor->obtenerPosicionActual() << " / " 
                      << cancionActual->obtenerDuracionSegundos() << " segundos" << std::endl;
        } else {
            std::cout << "No hay canción en reproducción." << std::endl;
        }
        
        std::cout << "Cola: " << reproductor->obtenerTamanoCola() << " canciones" << std::endl;
        std::cout << "Historial: " << reproductor->obtenerTamanoHistorial() << " canciones" << std::endl;
    }
    
    /**
     * @brief Muestra la cola de reproducción
     */
    void mostrarColaReproduccion() const {
        int tamanoCola = reproductor->obtenerTamanoCola();
        
        if (tamanoCola == 0) {
            std::cout << "\nNo hay canciones en la cola de reproducción." << std::endl;
            return;
        }
        
        std::cout << "\nCOLA DE REPRODUCCIÓN (" << tamanoCola << " canciones)\n";
        // Nota: No podemos mostrar el contenido de la cola directamente
        // porque no tenemos acceso a los elementos internos de la cola
        // desde esta clase. En una implementación real, podríamos agregar
        // un método en ReproductorMusica para obtener una copia de la cola.
    }
    
    /**
     * @brief Muestra las recomendaciones basadas en la canción actual
     */
    void mostrarRecomendaciones() {
        const Cancion* cancionActual = reproductor->obtenerCancionActual();
        
        if (!cancionActual) {
            std::cout << "No hay canción actual para generar recomendaciones." << std::endl;
            pausar();
            return;
        }
        
        // Buscar la canción actual en la biblioteca
        int posicionCancion = -1;
        for (int i = 0; i < biblioteca->obtenerNumeroCanciones(); i++) {
            Cancion cancion;
            biblioteca->obtenerCancion(i, cancion);
            
            if (cancion.obtenerTitulo() == cancionActual->obtenerTitulo() &&
                cancion.obtenerArtista() == cancionActual->obtenerArtista()) {
                posicionCancion = i;
                break;
            }
        }
        
        if (posicionCancion == -1) {
            std::cout << "No se encontró la canción actual en la biblioteca." << std::endl;
            pausar();
            return;
        }
        
        Lista<int> recomendaciones = biblioteca->obtenerRecomendaciones(posicionCancion, 5);
        
        if (recomendaciones.estaVacia()) {
            std::cout << "No hay recomendaciones disponibles." << std::endl;
            pausar();
            return;
        }
        
        limpiarPantalla();
        mostrarCabecera("RECOMENDACIONES");
        
        std::cout << "\nBasado en: " << cancionActual->obtenerTitulo() 
                  << " - " << cancionActual->obtenerArtista() << std::endl;
        
        std::cout << "\nCANCIONES RECOMENDADAS\n";
        std::cout << std::setw(5) << "ID" << " | "
                  << std::setw(30) << "TÍTULO" << " | "
                  << std::setw(20) << "ARTISTA" << " | "
                  << std::setw(20) << "ÁLBUM" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        
        for (auto it = recomendaciones.inicio(); it != recomendaciones.fin(); ++it) {
            int indice = *it;
            Cancion cancion;
            biblioteca->obtenerCancion(indice, cancion);
            
            std::cout << std::setw(5) << indice << " | "
                      << std::setw(30) << (cancion.obtenerTitulo().length() > 27 ? 
                                          cancion.obtenerTitulo().substr(0, 27) + "..." : 
                                          cancion.obtenerTitulo()) << " | "
                      << std::setw(20) << (cancion.obtenerArtista().length() > 17 ? 
                                          cancion.obtenerArtista().substr(0, 17) + "..." : 
                                          cancion.obtenerArtista()) << " | "
                      << std::setw(20) << (cancion.obtenerAlbum().length() > 17 ? 
                                          cancion.obtenerAlbum().substr(0, 17) + "..." : 
                                          cancion.obtenerAlbum()) << std::endl;
        }
        
        std::cout << "\nOPCIONES\n";
        std::cout << "1. Reproducir una recomendación\n";
        std::cout << "2. Encolar una recomendación\n";
        std::cout << "0. Volver\n";
        std::cout << "\nSeleccione una opción: ";
        
        int opcion = leerOpcion();
        
        switch (opcion) {
            case 1: {
                std::cout << "Ingrese el ID de la canción a reproducir: ";
                int id = leerOpcion();
                
                bool encontrado = false;
                for (auto it = recomendaciones.inicio(); it != recomendaciones.fin(); ++it) {
                    if (*it == id) {
                        encontrado = true;
                        break;
                    }
                }
                
                if (encontrado) {
                    reproductor->reproducir(id);
                    std::cout << "Reproduciendo canción recomendada..." << std::endl;
                } else {
                    std::cout << "ID no válido." << std::endl;
                }
                
                pausar();
                break;
            }
            case 2: {
                std::cout << "Ingrese el ID de la canción a encolar: ";
                int id = leerOpcion();
                
                bool encontrado = false;
                for (auto it = recomendaciones.inicio(); it != recomendaciones.fin(); ++it) {
                    if (*it == id) {
                        encontrado = true;
                        break;
                    }
                }
                
                if (encontrado) {
                    reproductor->encolarCancion(id);
                    std::cout << "Canción recomendada encolada." << std::endl;
                } else {
                    std::cout << "ID no válido." << std::endl;
                }
                
                pausar();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                pausar();
        }
    }
    
    /**
     * @brief Muestra los resultados de una búsqueda
     * @param resultados Lista con las posiciones de las canciones encontradas
     */
    void mostrarResultadosBusqueda(const Lista<int>& resultados) {
        if (resultados.estaVacia()) {
            std::cout << "No se encontraron resultados." << std::endl;
            pausar();
            return;
        }
        
        limpiarPantalla();
        mostrarCabecera("RESULTADOS DE BÚSQUEDA");
        
        std::cout << "\nCANCIONES ENCONTRADAS (" << resultados.obtenerTamano() << ")\n";
        std::cout << std::setw(5) << "ID" << " | "
                  << std::setw(30) << "TÍTULO" << " | "
                  << std::setw(20) << "ARTISTA" << " | "
                  << std::setw(20) << "ÁLBUM" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        
        for (auto it = resultados.inicio(); it != resultados.fin(); ++it) {
            int indice = *it;
            Cancion cancion;
            biblioteca->obtenerCancion(indice, cancion);
            
            std::cout << std::setw(5) << indice << " | "
                      << std::setw(30) << (cancion.obtenerTitulo().length() > 27 ? 
                                          cancion.obtenerTitulo().substr(0, 27) + "..." : 
                                          cancion.obtenerTitulo()) << " | "
                      << std::setw(20) << (cancion.obtenerArtista().length() > 17 ? 
                                          cancion.obtenerArtista().substr(0, 17) + "..." : 
                                          cancion.obtenerArtista()) << " | "
                      << std::setw(20) << (cancion.obtenerAlbum().length() > 17 ? 
                                          cancion.obtenerAlbum().substr(0, 17) + "..." : 
                                          cancion.obtenerAlbum()) << std::endl;
        }
        
        std::cout << "\nOPCIONES\n";
        std::cout << "1. Reproducir una canción\n";
        std::cout << "2. Encolar una canción\n";
        std::cout << "0. Volver\n";
        std::cout << "\nSeleccione una opción: ";
        
        int opcion = leerOpcion();
        
        switch (opcion) {
            case 1: {
                std::cout << "Ingrese el ID de la canción a reproducir: ";
                int id = leerOpcion();
                
                bool encontrado = false;
                for (auto it = resultados.inicio(); it != resultados.fin(); ++it) {
                    if (*it == id) {
                        encontrado = true;
                        break;
                    }
                }
                
                if (encontrado) {
                    reproductor->reproducir(id);
                    std::cout << "Reproduciendo canción..." << std::endl;
                } else {
                    std::cout << "ID no válido." << std::endl;
                }
                
                pausar();
                break;
            }
            case 2: {
                std::cout << "Ingrese el ID de la canción a encolar: ";
                int id = leerOpcion();
                
                bool encontrado = false;
                for (auto it = resultados.inicio(); it != resultados.fin(); ++it) {
                    if (*it == id) {
                        encontrado = true;
                        break;
                    }
                }
                
                if (encontrado) {
                    reproductor->encolarCancion(id);
                    std::cout << "Canción encolada." << std::endl;
                } else {
                    std::cout << "ID no válido." << std::endl;
                }
                
                pausar();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                pausar();
        }
    }
    
    /**
     * @brief Muestra una cabecera con un título
     * @param titulo Título de la cabecera
     */
    void mostrarCabecera(const std::string& titulo) const {
        int ancho = 80;
        int espacios = (ancho - titulo.length()) / 2;
        
        std::cout << std::string(ancho, '=') << std::endl;
        std::cout << std::string(espacios, ' ') << titulo << std::endl;
        std::cout << std::string(ancho, '=') << std::endl;
    }
    
    /**
     * @brief Lee una opción del usuario
     * @return Opción leída
     */
    int leerOpcion() const {
        int opcion;
        std::cin >> opcion;
        
        // Limpiar el buffer de entrada
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return -1;
        }
        
        return opcion;
    }
    
    /**
     * @brief Pausa la ejecución hasta que el usuario presione Enter
     */
    void pausar() const {
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    
    /**
     * @brief Limpia la pantalla de la consola
     */
    void limpiarPantalla() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
};

#endif // INTERFAZ_CONSOLA_H
