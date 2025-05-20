#ifndef INTERFAZ_CONSOLA_H
#define INTERFAZ_CONSOLA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "../servicios/BibliotecaMusical.h"
#include "../servicios/UTF8Util.h"

class InterfazConsola {
private:
    BibliotecaMusical& biblioteca;
    bool ejecutando;
    
public:
    InterfazConsola(BibliotecaMusical& _biblioteca) 
        : biblioteca(_biblioteca), ejecutando(true) {}
    
    void iniciar() {
        mostrarBienvenida();
        
        while (ejecutando) {
            mostrarMenuPrincipal();
            int opcion = leerOpcion();
            
            switch (opcion) {
                case 1:
                    mostrarBiblioteca();
                    break;
                case 2:
                    mostrarListasReproduccion();
                    break;
                case 3:
                    buscarCanciones();
                    break;
                case 4:
                    reproducirCancion();
                    break;
                case 5:
                    mostrarReproduccionActual();
                    break;
                case 6:
                    mostrarColaReproduccion();
                    break;
                case 7:
                    mostrarHistorial();
                    break;
                case 8:
                    mostrarRecomendaciones();
                    break;
                case 0:
                    ejecutando = false;
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                    break;
            }
            
            if (ejecutando) {
                std::cout << "\nPresione Enter para continuar...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                limpiarPantalla();
            }
        }
        
        mostrarDespedida();
    }
    
private:
    void mostrarBienvenida() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("REPRODUCTOR DE M" + UTF8Util::U_ACENTO() + "SICA") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Bienvenido al reproductor de música didáctico." << std::endl;
        std::cout << "Este programa utiliza estructuras de datos como listas, pilas, colas y grafos." << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get();
        limpiarPantalla();
    }
    
    void mostrarDespedida() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("GRACIAS POR USAR EL REPRODUCTOR DE M" + UTF8Util::U_ACENTO() + "SICA") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Hasta pronto!" << std::endl;
    }
    
    void mostrarMenuPrincipal() {
        std::cout << UTF8Util::formatearTitulo("MEN" + UTF8Util::U_ACENTO() + " PRINCIPAL") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar información de reproducción actual
        if (biblioteca.obtenerCancionActual() != -1) {
            Cancion cancionActual = biblioteca.obtenerCancion(biblioteca.obtenerCancionActual());
            std::cout << "Reproduciendo: " << cancionActual.titulo << " - " << cancionActual.artista;
            if (biblioteca.estaReproduciendo()) {
                std::cout << " [▶]";
            } else {
                std::cout << " [⏸]";
            }
            std::cout << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;
        }
        
        std::cout << "1. Ver biblioteca de canciones" << std::endl;
        std::cout << "2. Ver listas de reproducción" << std::endl;
        std::cout << "3. Buscar canciones" << std::endl;
        std::cout << "4. Reproducir canción" << std::endl;
        std::cout << "5. Control de reproducción" << std::endl;
        std::cout << "6. Ver cola de reproducción" << std::endl;
        std::cout << "7. Ver historial" << std::endl;
        std::cout << "8. Obtener recomendaciones" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Ingrese una opción: ";
    }
    
    int leerOpcion() {
        int opcion;
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return opcion;
    }
    
    void limpiarPantalla() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void mostrarBiblioteca() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("BIBLIOTECA DE CANCIONES") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (biblioteca.obtenerNumCanciones() == 0) {
            std::cout << "La biblioteca está vacía." << std::endl;
            return;
        }
        
        std::cout << "Ordenar por:" << std::endl;
        std::cout << "1. Título" << std::endl;
        std::cout << "2. Artista" << std::endl;
        std::cout << "3. Álbum" << std::endl;
        std::cout << "4. Año" << std::endl;
        std::cout << "0. Volver sin ordenar" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcionOrden = leerOpcion();
        bool ascendente = true;
        
        if (opcionOrden >= 1 && opcionOrden <= 4) {
            std::cout << "Orden:" << std::endl;
            std::cout << "1. Ascendente" << std::endl;
            std::cout << "2. Descendente" << std::endl;
            std::cout << "Ingrese una opción: ";
            
            int opcionDireccion = leerOpcion();
            ascendente = (opcionDireccion != 2);
            
            switch (opcionOrden) {
                case 1:
                    biblioteca.ordenarPorTitulo(ascendente);
                    break;
                case 2:
                    biblioteca.ordenarPorArtista(ascendente);
                    break;
                case 3:
                    biblioteca.ordenarPorAlbum(ascendente);
                    break;
                case 4:
                    biblioteca.ordenarPorAnio(ascendente);
                    break;
            }
        }
        
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("BIBLIOTECA DE CANCIONES") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar encabezados de columnas
        std::cout << UTF8Util::formatearTexto("Índice", 8) << " | ";
        std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
        std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
        std::cout << UTF8Util::formatearTexto("Álbum", 20) << " | ";
        std::cout << UTF8Util::formatearTexto("Año", 6) << " | ";
        std::cout << UTF8Util::formatearTexto("Duración", 10) << std::endl;
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar canciones
        for (int i = 0; i < biblioteca.obtenerNumCanciones(); i++) {
            Cancion cancion = biblioteca.obtenerCancion(i);
            
            std::cout << UTF8Util::formatearTexto(std::to_string(i), 8) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.album, 20) << " | ";
            std::cout << UTF8Util::formatearTexto(std::to_string(cancion.anio), 6) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.obtenerDuracionFormateada(), 10) << std::endl;
        }
    }
    
    void mostrarListasReproduccion() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("LISTAS DE REPRODUCCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (biblioteca.obtenerNumListasReproduccion() == 0) {
            std::cout << "No hay listas de reproducción." << std::endl;
            return;
        }
        
        // Mostrar listas de reproducción
        for (int i = 0; i < biblioteca.obtenerNumListasReproduccion(); i++) {
            ListaReproduccion lista = biblioteca.obtenerListaReproduccion(i);
            
            std::cout << i << ". " << lista.nombre << " (" << lista.obtenerNumCanciones() << " canciones)" << std::endl;
        }
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Ingrese el índice de la lista para ver su contenido (o -1 para volver): ";
        
        int indice = leerOpcion();
        
        if (indice >= 0 && indice < biblioteca.obtenerNumListasReproduccion()) {
            mostrarContenidoLista(indice);
        }
    }
    
    void mostrarContenidoLista(int indiceLista) {
        limpiarPantalla();
        ListaReproduccion lista = biblioteca.obtenerListaReproduccion(indiceLista);
        
        std::cout << UTF8Util::formatearTitulo("LISTA: " + lista.nombre) << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (lista.descripcion != "") {
            std::cout << "Descripción: " << lista.descripcion << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;
        }
        
        if (lista.obtenerNumCanciones() == 0) {
            std::cout << "Esta lista está vacía." << std::endl;
            return;
        }
        
        // Mostrar encabezados de columnas
        std::cout << UTF8Util::formatearTexto("Nº", 4) << " | ";
        std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
        std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
        std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar canciones de la lista
        for (int i = 0; i < lista.canciones.obtenerTamanio(); i++) {
            int indiceCancion = lista.canciones.obtener(i);
            Cancion cancion = biblioteca.obtenerCancion(indiceCancion);
            
            std::cout << UTF8Util::formatearTexto(std::to_string(i + 1), 4) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
        }
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Opciones:" << std::endl;
        std::cout << "1. Reproducir lista" << std::endl;
        std::cout << "2. Agregar canción a la lista" << std::endl;
        std::cout << "3. Eliminar canción de la lista" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcion = leerOpcion();
        
        switch (opcion) {
            case 1:
                reproducirLista(indiceLista);
                break;
            case 2:
                agregarCancionALista(indiceLista);
                break;
            case 3:
                eliminarCancionDeLista(indiceLista);
                break;
        }
    }
    
    void reproducirLista(int indiceLista) {
        ListaReproduccion lista = biblioteca.obtenerListaReproduccion(indiceLista);
        
        if (lista.obtenerNumCanciones() == 0) {
            std::cout << "Esta lista está vacía." << std::endl;
            return;
        }
        
        // Reproducir la primera canción
        int indiceCancion = lista.canciones.obtener(0);
        biblioteca.reproducir(indiceCancion);
        
        // Encolar el resto de canciones
        for (int i = 1; i < lista.canciones.obtenerTamanio(); i++) {
            indiceCancion = lista.canciones.obtener(i);
            biblioteca.encolarCancion(indiceCancion);
        }
        
        std::cout << "Reproduciendo lista: " << lista.nombre << std::endl;
        mostrarReproduccionActual();
    }
    
    void agregarCancionALista(int indiceLista) {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("AGREGAR CANCI" + UTF8Util::O_ACENTO() + "N A LISTA") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar canciones de la biblioteca
        mostrarBiblioteca();
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Ingrese el índice de la canción a agregar: ";
        
        int indiceCancion = leerOpcion();
        
        if (indiceCancion >= 0 && indiceCancion < biblioteca.obtenerNumCanciones()) {
            if (biblioteca.agregarCancionALista(indiceCancion, indiceLista)) {
                std::cout << "Canción agregada a la lista." << std::endl;
            } else {
                std::cout << "La canción ya está en la lista." << std::endl;
            }
        } else {
            std::cout << "Índice de canción inválido." << std::endl;
        }
    }
    
    void eliminarCancionDeLista(int indiceLista) {
        limpiarPantalla();
        ListaReproduccion lista = biblioteca.obtenerListaReproduccion(indiceLista);
        
        std::cout << UTF8Util::formatearTitulo("ELIMINAR CANCI" + UTF8Util::O_ACENTO() + "N DE LISTA") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (lista.obtenerNumCanciones() == 0) {
            std::cout << "Esta lista está vacía." << std::endl;
            return;
        }
        
        // Mostrar canciones de la lista
        for (int i = 0; i < lista.canciones.obtenerTamanio(); i++) {
            int indiceCancion = lista.canciones.obtener(i);
            Cancion cancion = biblioteca.obtenerCancion(indiceCancion);
            
            std::cout << i << ". " << cancion.titulo << " - " << cancion.artista << std::endl;
        }
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Ingrese el índice de la canción a eliminar: ";
        
        int indice = leerOpcion();
        
        if (indice >= 0 && indice < lista.canciones.obtenerTamanio()) {
            int indiceCancion = lista.canciones.obtener(indice);
            
            if (biblioteca.eliminarCancionDeLista(indiceCancion, indiceLista)) {
                std::cout << "Canción eliminada de la lista." << std::endl;
            } else {
                std::cout << "Error al eliminar la canción." << std::endl;
            }
        } else {
            std::cout << "Índice inválido." << std::endl;
        }
    }
    
    void buscarCanciones() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("BUSCAR CANCIONES") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        std::cout << "Buscar por:" << std::endl;
        std::cout << "1. Título" << std::endl;
        std::cout << "2. Artista" << std::endl;
        std::cout << "3. Álbum" << std::endl;
        std::cout << "4. Género" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcion = leerOpcion();
        
        if (opcion >= 1 && opcion <= 4) {
            std::cout << "Ingrese el término de búsqueda: ";
            std::string termino;
            std::getline(std::cin, termino);
            
            Lista<int> resultados;
            
            switch (opcion) {
                case 1:
                    resultados = biblioteca.buscarCancionesPorTitulo(termino);
                    break;
                case 2:
                    resultados = biblioteca.buscarCancionesPorArtista(termino);
                    break;
                case 3:
                    resultados = biblioteca.buscarCancionesPorAlbum(termino);
                    break;
                case 4:
                    resultados = biblioteca.buscarCancionesPorGenero(termino);
                    break;
            }
            
            mostrarResultadosBusqueda(resultados);
        }
    }
    
    void mostrarResultadosBusqueda(const Lista<int>& resultados) {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("RESULTADOS DE B" + UTF8Util::U_ACENTO() + "SQUEDA") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (resultados.obtenerTamanio() == 0) {
            std::cout << "No se encontraron resultados." << std::endl;
            return;
        }
        
        std::cout << "Se encontraron " << resultados.obtenerTamanio() << " resultados:" << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar encabezados de columnas
        std::cout << UTF8Util::formatearTexto("Índice", 8) << " | ";
        std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
        std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
        std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar resultados
        for (int i = 0; i < resultados.obtenerTamanio(); i++) {
            int indice = resultados.obtener(i);
            Cancion cancion = biblioteca.obtenerCancion(indice);
            
            std::cout << UTF8Util::formatearTexto(std::to_string(indice), 8) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
        }
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Opciones:" << std::endl;
        std::cout << "1. Reproducir una canción" << std::endl;
        std::cout << "2. Agregar una canción a la cola" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcion = leerOpcion();
        
        if (opcion == 1 || opcion == 2) {
            std::cout << "Ingrese el índice de la canción: ";
            int indice = leerOpcion();
            
            if (indice >= 0 && indice < biblioteca.obtenerNumCanciones()) {
                if (opcion == 1) {
                    biblioteca.reproducir(indice);
                    std::cout << "Reproduciendo canción." << std::endl;
                } else {
                    biblioteca.encolarCancion(indice);
                    std::cout << "Canción agregada a la cola." << std::endl;
                }
            } else {
                std::cout << "Índice inválido." << std::endl;
            }
        }
    }
    
    void reproducirCancion() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("REPRODUCIR CANCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar canciones de la biblioteca
        mostrarBiblioteca();
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Ingrese el índice de la canción a reproducir: ";
        
        int indice = leerOpcion();
        
        if (indice >= 0 && indice < biblioteca.obtenerNumCanciones()) {
            biblioteca.reproducir(indice);
            std::cout << "Reproduciendo canción." << std::endl;
            mostrarReproduccionActual();
        } else {
            std::cout << "Índice inválido." << std::endl;
        }
    }
    
    void mostrarReproduccionActual() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("REPRODUCCI" + UTF8Util::O_ACENTO() + "N ACTUAL") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (biblioteca.obtenerCancionActual() == -1) {
            std::cout << "No hay ninguna canción reproduciéndose." << std::endl;
            return;
        }
        
        Cancion cancion = biblioteca.obtenerCancion(biblioteca.obtenerCancionActual());
        
        std::cout << "Título: " << cancion.titulo << std::endl;
        std::cout << "Artista: " << cancion.artista << std::endl;
        std::cout << "Álbum: " << cancion.album << std::endl;
        std::cout << "Año: " << cancion.anio << std::endl;
        std::cout << "Duración: " << cancion.obtenerDuracionFormateada() << std::endl;
        
        std::cout << "Géneros: ";
        for (int i = 0; i < cancion.generos.obtenerTamanio(); i++) {
            std::cout << cancion.generos.obtener(i);
            if (i < cancion.generos.obtenerTamanio() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        
        std::cout << "Estado: " << (biblioteca.estaReproduciendo() ? "Reproduciendo" : "Pausado") << std::endl;
        
        // Simulación de barra de progreso
        int duracionTotal = cancion.duracion;
        int progreso = rand() % duracionTotal;
        int porcentaje = (progreso * 100) / duracionTotal;
        
        std::cout << "\nProgreso: [";
        for (int i = 0; i < 50; i++) {
            if (i < (porcentaje / 2)) {
                std::cout << "=";
            } else if (i == (porcentaje / 2)) {
                std::cout << ">";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "] " << porcentaje << "%" << std::endl;
        
        int minutos = progreso / 60;
        int segundos = progreso % 60;
        int minutosTotal = duracionTotal / 60;
        int segundosTotal = duracionTotal % 60;
        
        printf("%02d:%02d / %02d:%02d\n", minutos, segundos, minutosTotal, segundosTotal);
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Controles:" << std::endl;
        std::cout << "1. " << (biblioteca.estaReproduciendo() ? "Pausar" : "Reanudar") << std::endl;
        std::cout << "2. Anterior" << std::endl;
        std::cout << "3. Siguiente" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcion = leerOpcion();
        
        switch (opcion) {
            case 1:
                if (biblioteca.estaReproduciendo()) {
                    biblioteca.pausar();
                    std::cout << "Reproducción pausada." << std::endl;
                } else {
                    biblioteca.reanudar();
                    std::cout << "Reproducción reanudada." << std::endl;
                }
                mostrarReproduccionActual();
                break;
            case 2:
                if (biblioteca.anterior()) {
                    std::cout << "Reproduciendo canción anterior." << std::endl;
                } else {
                    std::cout << "No hay canciones anteriores en el historial." << std::endl;
                }
                mostrarReproduccionActual();
                  << std::endl;
                }
                mostrarReproduccionActual();
                break;
            case 3:
                if (biblioteca.siguiente()) {
                    std::cout << "Reproduciendo siguiente canción." << std::endl;
                } else {
                    std::cout << "No hay más canciones en la cola." << std::endl;
                }
                mostrarReproduccionActual();
                break;
        }
    }
    
    void mostrarColaReproduccion() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("COLA DE REPRODUCCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (biblioteca.obtenerTamanioCola() == 0) {
            std::cout << "La cola de reproducción está vacía." << std::endl;
            return;
        }
        
        std::cout << "Próximas canciones:" << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar encabezados de columnas
        std::cout << UTF8Util::formatearTexto("Posición", 10) << " | ";
        std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
        std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
        std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Simulación de mostrar la cola (no podemos acceder directamente a los elementos de la cola)
        int siguienteEnCola = biblioteca.obtenerSiguienteEnCola();
        if (siguienteEnCola != -1) {
            Cancion cancion = biblioteca.obtenerCancion(siguienteEnCola);
            
            std::cout << UTF8Util::formatearTexto("Siguiente", 10) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
            
            // Simulación de más elementos en la cola
            for (int i = 1; i < biblioteca.obtenerTamanioCola(); i++) {
                // Esto es una simulación, ya que no podemos acceder a los elementos de la cola directamente
                int indiceAleatorio = rand() % biblioteca.obtenerNumCanciones();
                Cancion cancionSimulada = biblioteca.obtenerCancion(indiceAleatorio);
                
                std::cout << UTF8Util::formatearTexto(std::to_string(i + 1), 10) << " | ";
                std::cout << UTF8Util::formatearTexto(cancionSimulada.titulo, 30) << " | ";
                std::cout << UTF8Util::formatearTexto(cancionSimulada.artista, 20) << " | ";
                std::cout << UTF8Util::formatearTexto(cancionSimulada.album, 20) << std::endl;
            }
        }
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Opciones:" << std::endl;
        std::cout << "1. Desencolar siguiente canción" << std::endl;
        std::cout << "2. Agregar canción a la cola" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcion = leerOpcion();
        
        switch (opcion) {
            case 1:
                if (biblioteca.desencolarCancion()) {
                    std::cout << "Canción desencolada." << std::endl;
                } else {
                    std::cout << "La cola está vacía." << std::endl;
                }
                mostrarColaReproduccion();
                break;
            case 2:
                agregarCancionACola();
                break;
        }
    }
    
    void agregarCancionACola() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("AGREGAR CANCI" + UTF8Util::O_ACENTO() + "N A LA COLA") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar canciones de la biblioteca
        mostrarBiblioteca();
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Ingrese el índice de la canción a agregar: ";
        
        int indice = leerOpcion();
        
        if (indice >= 0 && indice < biblioteca.obtenerNumCanciones()) {
            biblioteca.encolarCancion(indice);
            std::cout << "Canción agregada a la cola." << std::endl;
        } else {
            std::cout << "Índice inválido." << std::endl;
        }
    }
    
    void mostrarHistorial() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("HISTORIAL DE REPRODUCCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (biblioteca.obtenerTamanioHistorial() == 0) {
            std::cout << "El historial está vacío." << std::endl;
            return;
        }
        
        std::cout << "Últimas canciones reproducidas:" << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar encabezados de columnas
        std::cout << UTF8Util::formatearTexto("Posición", 10) << " | ";
        std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
        std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
        std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Simulación de mostrar el historial (no podemos acceder directamente a los elementos de la pila)
        int ultimaCancion = biblioteca.obtenerUltimaCancionHistorial();
        if (ultimaCancion != -1) {
            Cancion cancion = biblioteca.obtenerCancion(ultimaCancion);
            
            std::cout << UTF8Util::formatearTexto("Última", 10) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
            
            // Simulación de más elementos en el historial
            for (int i = 1; i < biblioteca.obtenerTamanioHistorial(); i++) {
                // Esto es una simulación, ya que no podemos acceder a los elementos de la pila directamente
                int indiceAleatorio = rand() % biblioteca.obtenerNumCanciones();
                Cancion cancionSimulada = biblioteca.obtenerCancion(indiceAleatorio);
                
                std::cout << UTF8Util::formatearTexto(std::to_string(i + 1), 10) << " | ";
                std::cout << UTF8Util::formatearTexto(cancionSimulada.titulo, 30) << " | ";
                std::cout << UTF8Util::formatearTexto(cancionSimulada.artista, 20) << " | ";
                std::cout << UTF8Util::formatearTexto(cancionSimulada.album, 20) << std::endl;
            }
        }
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Opciones:" << std::endl;
        std::cout << "1. Limpiar historial" << std::endl;
        std::cout << "2. Volver a la última canción" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcion = leerOpcion();
        
        switch (opcion) {
            case 1:
                biblioteca.limpiarHistorial();
                std::cout << "Historial limpiado." << std::endl;
                break;
            case 2:
                if (biblioteca.anterior()) {
                    std::cout << "Reproduciendo canción anterior." << std::endl;
                    mostrarReproduccionActual();
                } else {
                    std::cout << "No hay canciones anteriores en el historial." << std::endl;
                }
                break;
        }
    }
    
    void mostrarRecomendaciones() {
        limpiarPantalla();
        std::cout << UTF8Util::formatearTitulo("RECOMENDACIONES") << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        if (biblioteca.obtenerCancionActual() == -1) {
            std::cout << "No hay ninguna canción reproduciéndose. Reproduzca una canción para obtener recomendaciones." << std::endl;
            return;
        }
        
        Cancion cancionActual = biblioteca.obtenerCancion(biblioteca.obtenerCancionActual());
        std::cout << "Basado en: " << cancionActual.titulo << " - " << cancionActual.artista << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        Lista<int> recomendaciones = biblioteca.obtenerRecomendaciones(biblioteca.obtenerCancionActual(), 5);
        
        if (recomendaciones.obtenerTamanio() == 0) {
            std::cout << "No se encontraron recomendaciones." << std::endl;
            return;
        }
        
        std::cout << "Canciones recomendadas:" << std::endl;
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar encabezados de columnas
        std::cout << UTF8Util::formatearTexto("Índice", 8) << " | ";
        std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
        std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
        std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        
        // Mostrar recomendaciones
        for (int i = 0; i < recomendaciones.obtenerTamanio(); i++) {
            int indice = recomendaciones.obtener(i);
            Cancion cancion = biblioteca.obtenerCancion(indice);
            
            std::cout << UTF8Util::formatearTexto(std::to_string(indice), 8) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
            std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
        }
        
        std::cout << UTF8Util::formatearLinea(80) << std::endl;
        std::cout << "Opciones:" << std::endl;
        std::cout << "1. Reproducir una recomendación" << std::endl;
        std::cout << "2. Agregar todas las recomendaciones a la cola" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Ingrese una opción: ";
        
        int opcion = leerOpcion();
        
        switch (opcion) {
            case 1:
                std::cout << "Ingrese el índice de la canción a reproducir: ";
                int indice = leerOpcion();
                
                if (indice >= 0 && indice < biblioteca.obtenerNumCanciones()) {
                    biblioteca.reproducir(indice);
                    std::cout << "Reproduciendo canción." << std::endl;
                    mostrarReproduccionActual();
                } else {
                    std::cout << "Índice inválido." << std::endl;
                }
                break;
            case 2:
                for (int i = 0; i < recomendaciones.obtenerTamanio(); i++) {
                    int indice = recomendaciones.obtener(i);
                    biblioteca.encolarCancion(indice);
                }
                std::cout << "Recomendaciones agregadas a la cola." << std::endl;
                break;
        }
    }
};

#endif // INTERFAZ_CONSOLA_H