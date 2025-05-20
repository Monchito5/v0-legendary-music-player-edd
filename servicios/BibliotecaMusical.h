/**
 * @file BibliotecaMusical.h
 * @brief Definición de la clase BibliotecaMusical para gestionar la biblioteca de música
 * @author v0
 * @date Mayo 2025
 */

#ifndef BIBLIOTECA_MUSICAL_H
#define BIBLIOTECA_MUSICAL_H

#include <string>
#include <fstream>
#include <sstream>
//#include <filesystem> // Para la función std::filesystem::path
#include "../estructuras/Lista.h"
#include "../estructuras/Grafo.h"
#include "../modelos/Cancion.h"
#include "../modelos/Playlist.h"
#include "../algoritmos/Ordenamiento.h"
#include "../algoritmos/Busqueda.h"

namespace fs = std::filesystem;

/**
 * @brief Clase que gestiona la biblioteca musical
 */
class BibliotecaMusical {
private:
    Lista<Cancion> canciones;           ///< Lista de canciones en la biblioteca
    Lista<Playlist> playlists;          ///< Lista de playlists
    Grafo<std::string> grafoAfinidad;   ///< Grafo de afinidad para recomendaciones
    std::string directorioMusica;       ///< Directorio donde se almacena la música
    std::string archivoBiblioteca;      ///< Archivo para guardar la biblioteca
    std::string archivoPlaylists;       ///< Archivo para guardar las playlists

public:
    /**
     * @brief Constructor con parámetros
     * @param _directorioMusica Directorio donde se almacena la música
     * @param _archivoBiblioteca Archivo para guardar la biblioteca
     * @param _archivoPlaylists Archivo para guardar las playlists
     */
    BibliotecaMusical(const std::string& _directorioMusica = "./musica",
                     const std::string& _archivoBiblioteca = "./datos/biblioteca.dat",
                     const std::string& _archivoPlaylists = "./datos/playlists.dat")
        : directorioMusica(_directorioMusica),
          archivoBiblioteca(_archivoBiblioteca),
          archivoPlaylists(_archivoPlaylists) {

        // Crear directorios si no existen
        fs::create_directories(directorioMusica);
        fs::create_directories(fs::path(archivoBiblioteca).parent_path());
    }

    /**
     * @brief Carga la biblioteca desde el disco
     * @return true si se cargó correctamente, false en caso contrario
     */
    bool cargarBiblioteca() {
        // Primero intentamos cargar desde el archivo de biblioteca
        bool cargadoDesdeArchivo = cargarBibliotecaDesdeArchivo();

        // Si no hay archivo o falló la carga, escaneamos el directorio
        if (!cargadoDesdeArchivo) {
            escanearDirectorioMusica();
            guardarBibliotecaEnArchivo();
        }

        // Cargar playlists
        cargarPlaylistsDesdeArchivo();

        // Construir grafo de afinidad
        construirGrafoAfinidad();

        return true;
    }

    /**
     * @brief Guarda la biblioteca en el disco
     * @return true si se guardó correctamente, false en caso contrario
     */
    bool guardarBiblioteca() {
        return guardarBibliotecaEnArchivo() && guardarPlaylistsEnArchivo();
    }

    /**
     * @brief Agrega una canción a la biblioteca
     * @param cancion Canción a agregar
     */
    void agregarCancion(const Cancion& cancion) {
        canciones.agregar(cancion);
        actualizarGrafoAfinidad(cancion);
    }

    /**
     * @brief Elimina una canción de la biblioteca por su posición
     * @param posicion Posición de la canción (0-indexado)
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminarCancion(int posicion) {
        Cancion cancion;
        if (canciones.obtener(posicion, cancion)) {
            // Eliminar de todas las playlists
            for (int i = 0; i < playlists.obtenerTamano(); i++) {
                Playlist playlist;
                playlists.obtener(i, playlist);
                playlist.eliminarCancionPorTitulo(cancion.obtenerTitulo());
                playlists.eliminar(i);
                playlists.insertar(playlist, i);
            }

            return canciones.eliminar(posicion);
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
     * @brief Busca canciones por título (búsqueda lineal)
     * @param titulo Título a buscar
     * @return Lista con las posiciones de las canciones encontradas
     */
    Lista<int> buscarCancionesPorTitulo(const std::string& titulo) const {
        return Busqueda<Cancion>::busquedaPorCriterio(canciones, [&titulo](const Cancion& c) {
            return c.obtenerTitulo().find(titulo) != std::string::npos;
        });
    }

    /**
     * @brief Busca canciones por artista (búsqueda lineal)
     * @param artista Artista a buscar
     * @return Lista con las posiciones de las canciones encontradas
     */
    Lista<int> buscarCancionesPorArtista(const std::string& artista) const {
        return Busqueda<Cancion>::busquedaPorCriterio(canciones, [&artista](const Cancion& c) {
            return c.obtenerArtista().find(artista) != std::string::npos;
        });
    }

    /**
     * @brief Busca canciones por álbum (búsqueda lineal)
     * @param album Álbum a buscar
     * @return Lista con las posiciones de las canciones encontradas
     */
    Lista<int> buscarCancionesPorAlbum(const std::string& album) const {
        return Busqueda<Cancion>::busquedaPorCriterio(canciones, [&album](const Cancion& c) {
            return c.obtenerAlbum().find(album) != std::string::npos;
        });
    }

    /**
     * @brief Busca canciones por género (búsqueda lineal)
     * @param genero Género a buscar
     * @return Lista con las posiciones de las canciones encontradas
     */
    Lista<int> buscarCancionesPorGenero(const std::string& genero) const {
        return Busqueda<Cancion>::busquedaPorCriterio(canciones, [&genero](const Cancion& c) {
            const Lista<std::string>& generos = c.obtenerGeneros();
            for (auto it = generos.inicio(); it != generos.fin(); ++it) {
                if ((*it).find(genero) != std::string::npos) {
                    return true;
                }
            }
            return false;
        });
    }

    /**
     * @brief Ordena las canciones por título
     * @param ascendente true para ordenar ascendentemente, false para descendentemente
     * @param metodo Método de ordenamiento a utilizar (1: bubble, 2: insertion, 3: quick, 4: merge)
     */
    void ordenarCancionesPorTitulo(bool ascendente = true, int metodo = 3) {
        switch (metodo) {
            case 1:
                Ordenamiento<Cancion>::bubbleSort(canciones, ascendente);
                break;
            case 2:
                Ordenamiento<Cancion>::insertionSort(canciones, ascendente);
                break;
            case 3:
                Ordenamiento<Cancion>::quickSort(canciones, ascendente);
                break;
            case 4:
                Ordenamiento<Cancion>::mergeSort(canciones, ascendente);
                break;
            default:
                Ordenamiento<Cancion>::quickSort(canciones, ascendente);
        }
    }

    /**
     * @brief Crea una nueva playlist
     * @param nombre Nombre de la playlist
     * @return true si se creó correctamente, false si ya existe una con ese nombre
     */
    bool crearPlaylist(const std::string& nombre) {
        // Verificar si ya existe una playlist con ese nombre
        for (auto it = playlists.inicio(); it != playlists.fin(); ++it) {
            if ((*it).obtenerNombre() == nombre) {
                return false;
            }
        }

        playlists.agregar(Playlist(nombre));
        return true;
    }

    /**
     * @brief Elimina una playlist por su posición
     * @param posicion Posición de la playlist (0-indexado)
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminarPlaylist(int posicion) {
        return playlists.eliminar(posicion);
    }

    /**
     * @brief Renombra una playlist
     * @param posicion Posición de la playlist (0-indexado)
     * @param nuevoNombre Nuevo nombre para la playlist
     * @return true si se renombró correctamente, false en caso contrario
     */
    bool renombrarPlaylist(int posicion, const std::string& nuevoNombre) {
        Playlist playlist;
        if (playlists.obtener(posicion, playlist)) {
            playlist.establecerNombre(nuevoNombre);
            playlists.eliminar(posicion);
            playlists.insertar(playlist, posicion);
            return true;
        }
        return false;
    }

    /**
     * @brief Agrega una canción a una playlist
     * @param posicionPlaylist Posición de la playlist (0-indexado)
     * @param posicionCancion Posición de la canción en la biblioteca (0-indexado)
     * @return true si se agregó correctamente, false en caso contrario
     */
    bool agregarCancionAPlaylist(int posicionPlaylist, int posicionCancion) {
        Playlist playlist;
        Cancion cancion;

        if (playlists.obtener(posicionPlaylist, playlist) &&
            canciones.obtener(posicionCancion, cancion)) {

            playlist.agregarCancion(cancion);
            playlists.eliminar(posicionPlaylist);
            playlists.insertar(playlist, posicionPlaylist);
            return true;
        }

        return false;
    }

    /**
     * @brief Elimina una canción de una playlist
     * @param posicionPlaylist Posición de la playlist (0-indexado)
     * @param posicionCancion Posición de la canción en la playlist (0-indexado)
     * @return true si se eliminó correctamente, false en caso contrario
     */
    bool eliminarCancionDePlaylist(int posicionPlaylist, int posicionCancion) {
        Playlist playlist;

        if (playlists.obtener(posicionPlaylist, playlist)) {
            if (playlist.eliminarCancion(posicionCancion)) {
                playlists.eliminar(posicionPlaylist);
                playlists.insertar(playlist, posicionPlaylist);
                return true;
            }
        }

        return false;
    }

    /**
     * @brief Obtiene una playlist por su posición
     * @param posicion Posición de la playlist (0-indexado)
     * @param resultado Variable donde se almacenará el resultado
     * @return true si se obtuvo correctamente, false en caso contrario
     */
    bool obtenerPlaylist(int posicion, Playlist& resultado) const {
        return playlists.obtener(posicion, resultado);
    }

    /**
     * @brief Obtiene el número de canciones en la biblioteca
     * @return Número de canciones
     */
    int obtenerNumeroCanciones() const {
        return canciones.obtenerTamano();
    }

    /**
     * @brief Obtiene el número de playlists
     * @return Número de playlists
     */
    int obtenerNumeroPlaylists() const {
        return playlists.obtenerTamano();
    }

    /**
     * @brief Obtiene recomendaciones basadas en una canción
     * @param posicionCancion Posición de la canción base (0-indexado)
     * @param cantidad Cantidad de recomendaciones a obtener
     * @return Lista con las posiciones de las canciones recomendadas
     */
    Lista<int> obtenerRecomendaciones(int posicionCancion, int cantidad = 5) const {
        Lista<int> recomendaciones;
        Cancion cancion;

        if (!canciones.obtener(posicionCancion, cancion)) {
            return recomendaciones;
        }

        // Obtener géneros y artista de la canción base
        const Lista<std::string>& generos = cancion.obtenerGeneros();
        std::string artista = cancion.obtenerArtista();

        // Buscar canciones con géneros o artistas similares
        for (int i = 0; i < canciones.obtenerTamano() && recomendaciones.obtenerTamano() < cantidad; i++) {
            if (i == posicionCancion) {
                continue; // Saltar la canción base
            }

            Cancion candidata;
            canciones.obtener(i, candidata);

            // Verificar si comparten artista
            if (candidata.obtenerArtista() == artista) {
                recomendaciones.agregar(i);
                continue;
            }

            // Verificar si comparten al menos un género
            const Lista<std::string>& generosCandidata = candidata.obtenerGeneros();
            for (auto it = generos.inicio(); it != generos.fin(); ++it) {
                for (auto itCand = generosCandidata.inicio(); itCand != generosCandidata.fin(); ++itCand) {
                    if (*it == *itCand) {
                        recomendaciones.agregar(i);
                        break;
                    }
                }
            }
        }

        return recomendaciones;
    }

private:
    /**
     * @brief Escanea el directorio de música para encontrar archivos de audio
     */
    void escanearDirectorioMusica() {
        try {
            for (const auto& entrada : fs::directory_iterator(directorioMusica)) {
                if (entrada.is_regular_file()) {
                    std::string extension = entrada.path().extension().string();

                    // Verificar si es un archivo de audio
                    if (extension == ".mp3" || extension == ".wav" || extension == ".ogg" || extension == ".flac") {
                        // Extraer metadatos del nombre del archivo (simplificado)
                        std::string nombreArchivo = entrada.path().stem().string();
                        std::string titulo = nombreArchivo;
                        std::string artista = "Desconocido";
                        std::string album = "Desconocido";
                        int anio = 0;

                        // Intentar extraer artista y título si el formato es "Artista - Título"
                        size_t separador = nombreArchivo.find(" - ");
                        if (separador != std::string::npos) {
                            artista = nombreArchivo.substr(0, separador);
                            titulo = nombreArchivo.substr(separador + 3);
                        }

                        // Crear la canción y agregarla a la biblioteca
                        Cancion cancion(titulo, artista, album, anio, entrada.path().string(), 0);
                        cancion.agregarGenero("Desconocido");

                        canciones.agregar(cancion);
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al escanear directorio: " << e.what() << std::endl;
        }
    }

    /**
     * @brief Carga la biblioteca desde un archivo
     * @return true si se cargó correctamente, false en caso contrario
     */
    bool cargarBibliotecaDesdeArchivo() {
        std::ifstream archivo(archivoBiblioteca);
        if (!archivo) {
            return false;
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string titulo, artista, album, rutaArchivo, genero;
            int anio, duracionSegundos;

            // Formato: título|artista|álbum|año|duración|ruta|género1,género2,...
            std::getline(ss, titulo, '|');
            std::getline(ss, artista, '|');
            std::getline(ss, album, '|');
            ss >> anio;
            ss.ignore();
            ss >> duracionSegundos;
            ss.ignore();
            std::getline(ss, rutaArchivo, '|');
            std::getline(ss, genero);

            Cancion cancion(titulo, artista, album, anio, rutaArchivo, duracionSegundos);

            // Procesar géneros
            std::istringstream ssGeneros(genero);
            std::string g;
            while (std::getline(ssGeneros, g, ',')) {
                cancion.agregarGenero(g);
            }

            canciones.agregar(cancion);
        }

        archivo.close();
        return true;
    }

    /**
     * @brief Guarda la biblioteca en un archivo
     * @return true si se guardó correctamente, false en caso contrario
     */
    bool guardarBibliotecaEnArchivo() const {
        std::ofstream archivo(archivoBiblioteca);
        if (!archivo) {
            return false;
        }

        for (int i = 0; i < canciones.obtenerTamano(); i++) {
            Cancion cancion;
            canciones.obtener(i, cancion);

            // Formato: título|artista|álbum|año|duración|ruta|género1,género2,...
            archivo << cancion.obtenerTitulo() << "|"
                    << cancion.obtenerArtista() << "|"
                    << cancion.obtenerAlbum() << "|"
                    << cancion.obtenerAnio() << "|"
                    << cancion.obtenerDuracionSegundos() << "|"
                    << cancion.obtenerRutaArchivo() << "|";

            // Escribir géneros
            const Lista<std::string>& generos = cancion.obtenerGeneros();
            bool primero = true;
            for (auto it = generos.inicio(); it != generos.fin(); ++it) {
                if (!primero) {
                    archivo << ",";
                }
                archivo << *it;
                primero = false;
            }

            archivo << std::endl;
        }

        archivo.close();
        return true;
    }

    /**
     * @brief Carga las playlists desde un archivo
     * @return true si se cargó correctamente, false en caso contrario
     */
    bool cargarPlaylistsDesdeArchivo() {
        std::ifstream archivo(archivoPlaylists);
        if (!archivo) {
            return false;
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            if (linea.empty()) {
                continue;
            }

            // La primera línea es el nombre de la playlist
            std::string nombrePlaylist = linea;
            Playlist playlist(nombrePlaylist);

            // La siguiente línea contiene los índices de las canciones
            if (std::getline(archivo, linea)) {
                std::istringstream ss(linea);
                int indiceCancion;

                while (ss >> indiceCancion) {
                    Cancion cancion;
                    if (canciones.obtener(indiceCancion, cancion)) {
                        playlist.agregarCancion(cancion);
                    }
                }
            }

            playlists.agregar(playlist);
        }

        archivo.close();
        return true;
    }

    /**
     * @brief Guarda las playlists en un archivo
     * @return true si se guardó correctamente, false en caso contrario
     */
    bool guardarPlaylistsEnArchivo() const {
        std::ofstream archivo(archivoPlaylists);
        if (!archivo) {
            return false;
        }

        for (int i = 0; i < playlists.obtenerTamano(); i++) {
            Playlist playlist;
            playlists.obtener(i, playlist);

            // Escribir nombre de la playlist
            archivo << playlist.obtenerNombre() << std::endl;

            // Escribir índices de las canciones
            const Lista<Cancion>& cancionesPlaylist = playlist.obtenerCanciones();
            for (int j = 0; j < cancionesPlaylist.obtenerTamano(); j++) {
                Cancion cancionPlaylist;
                cancionesPlaylist.obtener(j, cancionPlaylist);

                // Buscar el índice de la canción en la biblioteca
                for (int k = 0; k < canciones.obtenerTamano(); k++) {
                    Cancion cancionBiblioteca;
                    canciones.obtener(k, cancionBiblioteca);

                    if (cancionPlaylist == cancionBiblioteca) {
                        archivo << k << " ";
                        break;
                    }
                }
            }

            archivo << std::endl;
        }

        archivo.close();
        return true;
    }

    /**
     * @brief Construye el grafo de afinidad para recomendaciones
     */
    void construirGrafoAfinidad() {
        // Agregar vértices para géneros y artistas
        Lista<std::string> generosTotales;
        Lista<std::string> artistasTotales;

        // Recopilar todos los géneros y artistas únicos
        for (int i = 0; i < canciones.obtenerTamano(); i++) {
            Cancion cancion;
            canciones.obtener(i, cancion);

            // Agregar artista si no existe
            std::string artista = cancion.obtenerArtista();
            if (Busqueda<std::string>::busquedaLineal(artistasTotales, artista) == -1) {
                artistasTotales.agregar(artista);
            }

            // Agregar géneros si no existen
            const Lista<std::string>& generos = cancion.obtenerGeneros();
            for (auto it = generos.inicio(); it != generos.fin(); ++it) {
                if (Busqueda<std::string>::busquedaLineal(generosTotales, *it) == -1) {
                    generosTotales.agregar(*it);
                }
            }
        }

        // Agregar vértices al grafo
        for (auto it = generosTotales.inicio(); it != generosTotales.fin(); ++it) {
            grafoAfinidad.agregarVertice(*it);
        }

        for (auto it = artistasTotales.inicio(); it != artistasTotales.fin(); ++it) {
            grafoAfinidad.agregarVertice(*it);
        }

        // Crear aristas entre géneros y artistas
        for (int i = 0; i < canciones.obtenerTamano(); i++) {
            Cancion cancion;
            canciones.obtener(i, cancion);

            std::string artista = cancion.obtenerArtista();
            int indiceArtista = grafoAfinidad.buscarVertice(artista);

            const Lista<std::string>& generos = cancion.obtenerGeneros();
            for (auto it = generos.inicio(); it != generos.fin(); ++it) {
                int indiceGenero = grafoAfinidad.buscarVertice(*it);

                // Crear arista bidireccional entre artista y género
                grafoAfinidad.agregarArista(indiceArtista, indiceGenero, 1);
                grafoAfinidad.agregarArista(indiceGenero, indiceArtista, 1);
            }
        }
    }

    /**
     * @brief Actualiza el grafo de afinidad al agregar una nueva canción
     * @param cancion Canción agregada
     */
    void actualizarGrafoAfinidad(const Cancion& cancion) {
        std::string artista = cancion.obtenerArtista();
        int indiceArtista = grafoAfinidad.buscarVertice(artista);

        // Si el artista no existe, agregarlo
        if (indiceArtista == -1) {
            indiceArtista = grafoAfinidad.agregarVertice(artista);
        }

        // Procesar géneros
        const Lista<std::string>& generos = cancion.obtenerGeneros();
        for (auto it = generos.inicio(); it != generos.fin(); ++it) {
            int indiceGenero = grafoAfinidad.buscarVertice(*it);

            // Si el género no existe, agregarlo
            if (indiceGenero == -1) {
                indiceGenero = grafoAfinidad.agregarVertice(*it);
            }

            // Crear arista bidireccional entre artista y género
            grafoAfinidad.agregarArista(indiceArtista, indiceGenero, 1);
            grafoAfinidad.agregarArista(indiceGenero, indiceArtista, 1);
        }
    }
};

#endif // BIBLIOTECA_MUSICAL_H
