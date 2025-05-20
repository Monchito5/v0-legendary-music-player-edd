/**
 * @file main.cpp
 * @brief Archivo principal del reproductor de música
 * @author v0
 * @date Mayo 2025
 */

#include <iostream>
#include <string>
#include "servicios/BibliotecaMusical.h"
#include "servicios/ReproductorMusica.h"
#include "ui/InterfazConsola.h"

/**
 * @brief Función principal
 * @return Código de salida
 */
int main() {
    // Crear directorios necesarios
    std::filesystem::create_directories("./musica");
    std::filesystem::create_directories("./datos");
    
    // Inicializar la biblioteca musical
    BibliotecaMusical biblioteca("./musica", "./datos/biblioteca.dat", "./datos/playlists.dat");
    
    // Cargar la biblioteca
    std::cout << "Cargando biblioteca musical..." << std::endl;
    biblioteca.cargarBiblioteca();
    
    // Inicializar el reproductor
    ReproductorMusica reproductor(&biblioteca);
    
    // Inicializar la interfaz de consola
    InterfazConsola interfaz(&biblioteca, &reproductor);
    
    // Iniciar la aplicación
    interfaz.iniciar();
    
    return 0;
}
