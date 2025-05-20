#ifndef UTF8UTIL_H
#define UTF8UTIL_H

#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <iomanip>

class UTF8Util {
public:
    // Configura la consola para mostrar caracteres UTF-8
    static void configurarConsola() {
        #ifdef _WIN32
            // En Windows, configurar la consola para UTF-8
            system("chcp 65001 > nul");
        #else
            // En sistemas Unix/Linux, configurar locale
            std::locale::global(std::locale(""));
        #endif

        // Configurar cout para usar UTF-8
        std::cout.imbue(std::locale());
    }

    // Convierte una cadena a UTF-8 (útil para Windows)
    static std::string aUTF8(const std::string& texto) {
        return texto; // En la mayoría de los casos, no necesitamos conversión
    }

    // Formatea un texto para que tenga un ancho específico
    static std::string formatearTexto(const std::string& texto, int ancho) {
        if (texto.length() > ancho) {
            return texto.substr(0, ancho - 3) + "...";
        }

        return texto + std::string(ancho - texto.length(), ' ');
    }

    // Crea una línea de separación
    static std::string formatearLinea(int longitud) {
        return std::string(longitud, '-');
    }

    // Formatea un título centrado
    static std::string formatearTitulo(const std::string& titulo) {
        const int ancho = 80;
        int espacios = (ancho - titulo.length()) / 2;

        if (espacios < 0) espacios = 0;

        return std::string(espacios, ' ') + titulo;
    }

    // Caracteres especiales en español
    static const std::string A_ACENTO() { return "á"; }
    static const std::string E_ACENTO() { return "é"; }
    static const std::string I_ACENTO() { return "í"; }
    static const std::string O_ACENTO() { return "ó"; }
    static const std::string U_ACENTO() { return "ú"; }
    static const std::string U_DIERESIS() { return "ü"; }
    static const std::string N_TILDE() { return "ñ"; }
    static const std::string EXCLAMACION_INICIAL() { return "¡"; }
    static const std::string INTERROGACION_INICIAL() { return "¿"; }

    // Método para mostrar un mensaje con caracteres especiales
    static void mostrarMensaje(const std::string& mensaje) {
        std::cout << aUTF8(mensaje) << std::endl;
    }
};

#endif // UTF8UTIL_H
