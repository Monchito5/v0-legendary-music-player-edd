#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>

// Estructura para metadatos de la canción
struct Metadata {
    std::string title;
    std::string artist;
    std::string album;
    int year;
    std::vector<std::string> genres;
    int durationSecs;
    std::string filePath;
};

// Estructura principal para representar una canción
struct Song {
    int id;
    Metadata metadata;
    int playCount;
    
    // Constructor por defecto
    Song() : id(-1), playCount(0) {}
    
    // Constructor con parámetros
    Song(int _id, const Metadata& _metadata) 
        : id(_id), metadata(_metadata), playCount(0) {}
    
    // Operadores de comparación para ordenamiento
    bool operator==(const Song& other) const {
        return id == other.id;
    }
    
    bool operator<(const Song& other) const {
        return metadata.title < other.metadata.title;
    }
};

// Constantes para tamaños máximos
const int MAX_LIB = 10000;  // Tamaño máximo de la biblioteca
const int MAX_HIST = 100;   // Tamaño máximo del historial
const int MAX_Q = 50;       // Tamaño máximo de la cola de reproducción

#endif // SONG_H
