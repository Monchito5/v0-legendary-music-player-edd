#ifndef LIBRARY_H
#define LIBRARY_H

#include "../models/song.h"
#include <string>

class Library {
private:
    Song songs[MAX_LIB];
    int size;

public:
    // Constructor
    Library();
    
    // Métodos básicos
    bool addSong(const Song& song);
    bool removeSong(int id);
    Song* findSongById(int id);
    Song* findSongByTitle(const std::string& title);
    
    // Métodos de búsqueda
    Song* linearSearch(const std::string& query, const std::string& field);
    Song* binarySearch(const std::string& title);
    
    // Métodos de ordenamiento
    void bubbleSort();
    void insertionSort();
    void quickSort();
    void mergeSort();
    
    // Getters
    int getSize() const { return size; }
    Song* getSongs() { return songs; }
    
    // Persistencia
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    bool exportToCSV(const std::string& filename);
    bool importFromCSV(const std::string& filename);
};

#endif // LIBRARY_H
