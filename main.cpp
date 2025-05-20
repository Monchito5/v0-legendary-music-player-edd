/**
 * @file main.cpp
 * @brief Archivo principal del reproductor de música
 * @author v0
 * @date Mayo 2025
 */

#include <iostream>
#include <string>
#include "servicios/BibliotecaMusical.h"
#include "servicios/UTF8Util.h"
#include "servicios/ReproductorMusica.h"
#include "ui/InterfazConsola.h"

using namespace std;
/**
 * @brief Función principal
 * @return Código de salida
 */
int main() {
    // Configurar la consola para mostrar caracteres UTF-8
    UTF8Util::configurarConsola();

    // Mostrar título del programa
    std::cout << UTF8Util::formatearTitulo("REPRODUCTOR DE M" + UTF8Util::U_ACENTO() + "SICA") << std::endl;
    std::cout << UTF8Util::formatearLinea(80) << std::endl;

    // Cargar canciones desde un directorio
    std::string rutaDirectorio = "./musica";
    if (biblioteca.cargarCancionesDesdeDirectorio(rutaDirectorio)) {
        UTF8Util::mostrarMensaje("Canciones cargadas con " + UTF8Util::E_ACENTO() + "xito.");
    } else {
        UTF8Util::mostrarMensaje("Error al cargar las canciones. " + UTF8Util::EXCLAMACION_INICIAL() + "Verifique la ruta!");
    }
    
    // Mostrar las canciones cargadas
    biblioteca.mostrarCanciones();

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
