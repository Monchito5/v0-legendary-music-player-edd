#include "BibliotecaMusical.h"
#include "FileSystem.h"
#include "UTF8Util.h"
#include <iostream>

// Constructor de la biblioteca musical
BibliotecaMusical::BibliotecaMusical() {
    // Inicialización de la biblioteca vacía
}

// Destructor
BibliotecaMusical::~BibliotecaMusical() {
    // Liberar memoria si es necesario
}

// Cargar canciones desde un directorio
bool BibliotecaMusical::cargarCancionesDesdeDirectorio(const std::string& rutaDirectorio) {
    // Verificar si el directorio existe
    if (!FileSystem::existeRuta(rutaDirectorio) || !FileSystem::esDirectorio(rutaDirectorio)) {
        std::cout << "Error: El directorio especificado no existe o no es válido." << std::endl;
        return false;
    }
    
    // Obtener todos los archivos MP3 del directorio
    std::vector<std::string> archivosMp3 = FileSystem::obtenerArchivosPorExtension(rutaDirectorio, "mp3");
    
    if (archivosMp3.empty()) {
        std::cout << "No se encontraron archivos MP3 en el directorio." << std::endl;
        return false;
    }
    
    // Procesar cada archivo MP3 encontrado
    for (const auto& rutaArchivo : archivosMp3) {
        Cancion nuevaCancion;
        
        // Aquí iría el código para extraer metadatos del archivo MP3
        // Por ejemplo, usando una biblioteca como TagLib o implementación propia
        
        // Por ahora, simplemente extraemos el nombre del archivo como título
        size_t ultimaBarra = rutaArchivo.find_last_of("/\\");
        size_t ultimoPunto = rutaArchivo.find_last_of(".");
        
        if (ultimaBarra != std::string::npos && ultimoPunto != std::string::npos) {
            nuevaCancion.titulo = rutaArchivo.substr(ultimaBarra + 1, ultimoPunto - ultimaBarra - 1);
            nuevaCancion.rutaArchivo = rutaArchivo;
            
            // Valores por defecto para los demás campos
            nuevaCancion.artista = "Desconocido";
            nuevaCancion.album = "Desconocido";
            nuevaCancion.anio = 0;
            nuevaCancion.genero = "Desconocido";
            
            // Agregar la canción a la biblioteca
            agregarCancion(nuevaCancion);
        }
    }
    
    std::cout << "Se cargaron " << archivosMp3.size() << " canciones a la biblioteca." << std::endl;
    return true;
}

// Agregar una canción a la biblioteca
void BibliotecaMusical::agregarCancion(const Cancion& cancion) {
    canciones.agregar(cancion);
}

// Mostrar todas las canciones en la biblioteca
void BibliotecaMusical::mostrarCanciones() const {
    std::cout << UTF8Util::formatearTitulo("BIBLIOTECA MUSICAL") << std::endl;
    std::cout << UTF8Util::formatearLinea(80) << std::endl;
    
    if (canciones.estaVacia()) {
        std::cout << "La biblioteca está vacía." << std::endl;
        return;
    }
    
    // Mostrar encabezados de columnas
    std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
    std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
    std::cout << UTF8Util::formatearTexto("Álbum", 20) << " | ";
    std::cout << UTF8Util::formatearTexto("Año", 6) << " | ";
    std::cout << UTF8Util::formatearTexto("Género", 15) << std::endl;
    
    std::cout << UTF8Util::formatearLinea(80) << std::endl;
    
    // Recorrer y mostrar cada canción
    for (int i = 0; i < canciones.obtenerTamanio(); i++) {
        Cancion cancion = canciones.obtener(i);
        
        std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
        std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
        std::cout << UTF8Util::formatearTexto(cancion.album, 20) << " | ";
        std::cout << UTF8Util::formatearTexto(std::to_string(cancion.anio), 6) << " | ";
        std::cout << UTF8Util::formatearTexto(cancion.genero, 15) << std::endl;
    }
}