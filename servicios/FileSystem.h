#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

class FileSystem {
private:
    // Estructura para almacenar información de archivos
    struct FileInfo {
        std::string nombre;
        std::string ruta;
        bool esDirectorio;
    };

public:
    // Verifica si una ruta existe
    static bool existeRuta(const std::string& ruta) {
        struct stat buffer;
        return (stat(ruta.c_str(), &buffer) == 0);
    }

    // Verifica si una ruta es un directorio
    static bool esDirectorio(const std::string& ruta) {
        struct stat buffer;
        if (stat(ruta.c_str(), &buffer) != 0) return false;
        return S_ISDIR(buffer.st_mode);
    }

    // Obtiene la extensión de un archivo
    static std::string obtenerExtension(const std::string& nombreArchivo) {
        size_t pos = nombreArchivo.find_last_of(".");
        if (pos != std::string::npos) {
            return nombreArchivo.substr(pos + 1);
        }
        return "";
    }

    // Lista todos los archivos en un directorio
    static std::vector<FileInfo> listarDirectorio(const std::string& ruta) {
        std::vector<FileInfo> archivos;
        DIR* dir = opendir(ruta.c_str());
        
        if (dir == nullptr) {
            return archivos;
        }
        
        struct dirent* entrada;
        while ((entrada = readdir(dir)) != nullptr) {
            // Ignorar . y ..
            if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
                continue;
            }
            
            std::string nombreArchivo = entrada->d_name;
            std::string rutaCompleta = ruta + "/" + nombreArchivo;
            
            FileInfo info;
            info.nombre = nombreArchivo;
            info.ruta = rutaCompleta;
            info.esDirectorio = esDirectorio(rutaCompleta);
            
            archivos.push_back(info);
        }
        
        closedir(dir);
        return archivos;
    }

    // Obtiene todos los archivos con una extensión específica
    static std::vector<std::string> obtenerArchivosPorExtension(const std::string& ruta, const std::string& extension) {
        std::vector<std::string> resultado;
        std::vector<FileInfo> archivos = listarDirectorio(ruta);
        
        for (const auto& archivo : archivos) {
            if (!archivo.esDirectorio && obtenerExtension(archivo.nombre) == extension) {
                resultado.push_back(archivo.ruta);
            }
        }
        
        return resultado;
    }
};

#endif // FILESYSTEM_H