#include <iostream>
#include <string>
#include <locale>
#include <cstdlib>
#include <ctime>

#include "servicios/UTF8Util.h"
#include "servicios/BibliotecaMusical.h"
#include "ui/InterfazConsola.h"

int main() {
    // Inicializar generador de números aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Configurar la consola para mostrar caracteres UTF-8
    UTF8Util::configurarConsola();
    
    // Crear la biblioteca musical con datos ficticios
    BibliotecaMusical biblioteca;
    
    // Crear la interfaz de consola
    InterfazConsola interfaz(biblioteca);
    
    // Iniciar la interfaz
    interfaz.iniciar();
    
    return 0;
}