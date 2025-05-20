#include "library.h"
#include <algorithm>
#include <fstream>
#include <sstream>

Library::Library() : size(0) {}

bool Library::addSong(const Song& song) {
    if (size >= MAX_LIB) {
        return false;
    }
    
    songs[size++] = song;
    return true;
}

bool Library::removeSong(int id) {
    for (int i = 0; i < size; i++) {
        if (songs[i].id == id) {
            // Mover todas las canciones una posición hacia atrás
            for (int j = i; j < size - 1; j++) {
                songs[j] = songs[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

Song* Library::findSongById(int id) {
    for (int i = 0; i < size; i++) {
        if (songs[i].id == id) {
            return &songs[i];
        }
    }
    return nullptr;
}

Song* Library::findSongByTitle(const std::string& title) {
    return linearSearch(title, "title");
}

Song* Library::linearSearch(const std::string& query, const std::string& field) {
    for (int i = 0; i < size; i++) {
        if (field == "title" && songs[i].metadata.title == query) {
            return &songs[i];
        } else if (field == "artist" && songs[i].metadata.artist == query) {
            return &songs[i];
        } else if (field == "album" && songs[i].metadata.album == query) {
            return &songs[i];
        }
    }
    return nullptr;
}

// Implementación de búsqueda binaria (requiere que los datos estén ordenados)
Song* Library::binarySearch(const std::string& title) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (songs[mid].metadata.title == title) {
            return &songs[mid];
        }
        
        if (songs[mid].metadata.title < title) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return nullptr;
}

// Implementación de Bubble Sort
void Library::bubbleSort() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (songs[j].metadata.title > songs[j + 1].metadata.title) {
                std::swap(songs[j], songs[j + 1]);
            }
        }
    }
}

// Implementación de Insertion Sort
void Library::insertionSort() {
    for (int i = 1; i < size; i++) {
        Song key = songs[i];
        int j = i - 1;
        
        while (j >= 0 && songs[j].metadata.title > key.metadata.title) {
            songs[j + 1] = songs[j];
            j--;
        }
        
        songs[j + 1] = key;
    }
}

// Función auxiliar para QuickSort
int partition(Song arr[], int low, int high) {
    Song pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].metadata.title <= pivot.metadata.title) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Función recursiva para QuickSort
void quickSortRecursive(Song arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

// Método QuickSort
void Library::quickSort() {
    quickSortRecursive(songs, 0, size - 1);
}

// Función auxiliar para MergeSort
void merge(Song arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Crear arrays temporales
    Song* L = new Song[n1];
    Song* R = new Song[n2];
    
    // Copiar datos a los arrays temporales
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    
    // Combinar los arrays temporales
    int i = 0;
    int j = 0;
    int k = left;
    
    while (i < n1 && j < n2) {
        if (L[i].metadata.title <= R[j].metadata.title) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copiar los elementos restantes de L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copiar los elementos restantes de R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

// Función recursiva para MergeSort
void mergeSortRecursive(Song arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

// Método MergeSort
void Library::mergeSort() {
    mergeSortRecursive(songs, 0, size - 1);
}

// Persistencia: guardar en archivo binario
bool Library::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }
    
    // Guardar el tamaño de la biblioteca
    file.write(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Guardar cada canción
    for (int i = 0; i < size; i++) {
        // Guardar ID y playCount
        file.write(reinterpret_cast<char*>(&songs[i].id), sizeof(songs[i].id));
        file.write(reinterpret_cast<char*>(&songs[i].playCount), sizeof(songs[i].playCount));
        
        // Guardar metadatos
        int titleLength = songs[i].metadata.title.length();
        file.write(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
        file.write(songs[i].metadata.title.c_str(), titleLength);
        
        int artistLength = songs[i].metadata.artist.length();
        file.write(reinterpret_cast<char*>(&artistLength), sizeof(artistLength));
        file.write(songs[i].metadata.artist.c_str(), artistLength);
        
        int albumLength = songs[i].metadata.album.length();
        file.write(reinterpret_cast<char*>(&albumLength), sizeof(albumLength));
        file.write(songs[i].metadata.album.c_str(), albumLength);
        
        file.write(reinterpret_cast<char*>(&songs[i].metadata.year), sizeof(songs[i].metadata.year));
        file.write(reinterpret_cast<char*>(&songs[i].metadata.durationSecs), sizeof(songs[i].metadata.durationSecs));
        
        int pathLength = songs[i].metadata.filePath.length();
        file.write(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));
        file.write(songs[i].metadata.filePath.c_str(), pathLength);
        
        // Guardar géneros
        int genresCount = songs[i].metadata.genres.size();
        file.write(reinterpret_cast<char*>(&genresCount), sizeof(genresCount));
        
        for (const auto& genre : songs[i].metadata.genres) {
            int genreLength = genre.length();
            file.write(reinterpret_cast<char*>(&genreLength), sizeof(genreLength));
            file.write(genre.c_str(), genreLength);
        }
    }
    
    file.close();
    return true;
}

// Persistencia: cargar desde archivo binario
bool Library::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }
    
    // Leer el tamaño de la biblioteca
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Leer cada canción
    for (int i = 0; i < size; i++) {
        // Leer ID y playCount
        file.read(reinterpret_cast<char*>(&songs[i].id), sizeof(songs[i].id));
        file.read(reinterpret_cast<char*>(&songs[i].playCount), sizeof(songs[i].playCount));
        
        // Leer metadatos
        int titleLength;
        file.read(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
        char* titleBuffer = new char[titleLength + 1];
        file.read(titleBuffer, titleLength);
        titleBuffer[titleLength] = '\0';
        songs[i].metadata.title = titleBuffer;
        delete[] titleBuffer;
        
        int artistLength;
        file.read(reinterpret_cast<char*>(&artistLength), sizeof(artistLength));
        char* artistBuffer = new char[artistLength + 1];
        file.read(artistBuffer, artistLength);
        artistBuffer[artistLength] = '\0';
        songs[i].metadata.artist = artistBuffer;
        delete[] artistBuffer;
        
        int albumLength;
        file.read(reinterpret_cast<char*>(&albumLength), sizeof(albumLength));
        char* albumBuffer = new char[albumLength + 1];
        file.read(albumBuffer, albumLength);
        albumBuffer[albumLength] = '\0';
        songs[i].metadata.album = albumBuffer;
        delete[] albumBuffer;
        
        file.read(reinterpret_cast<char*>(&songs[i].metadata.year), sizeof(songs[i].metadata.year));
        file.read(reinterpret_cast<char*>(&songs[i].metadata.durationSecs), sizeof(songs[i].metadata.durationSecs));
        
        int pathLength;
        file.read(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));
        char* pathBuffer = new char[pathLength + 1];
        file.read(pathBuffer, pathLength);
        pathBuffer[pathLength] = '\0';
        songs[i].metadata.filePath = pathBuffer;
        delete[] pathBuffer;
        
        // Leer géneros
        int genresCount;
        file.read(reinterpret_cast<char*>(&genresCount), sizeof(genresCount));
        
        songs[i].metadata.genres.clear();
        for (int j = 0; j < genresCount; j++) {
            int genreLength;
            file.read(reinterpret_cast<char*>(&genreLength), sizeof(genreLength));
            char* genreBuffer = new char[genreLength + 1];
            file.read(genreBuffer, genreLength);
            genreBuffer[genreLength] = '\0';
            songs[i].metadata.genres.push_back(genreBuffer);
            delete[] genreBuffer;
        }
    }
    
    file.close();
    return true;
}

// Exportar a CSV
bool Library::exportToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        return false;
    }
    
    // Escribir encabezado
    file << "ID,Title,Artist,Album,Year,Duration,PlayCount,FilePath,Genres\n";
    
    // Escribir cada canción
    for (int i = 0; i < size; i++) {
        file << songs[i].id << ","
             << "\"" << songs[i].metadata.title << "\","
             << "\"" << songs[i].metadata.artist << "\","
             << "\"" << songs[i].metadata.album << "\","
             << songs[i].metadata.year << ","
             << songs[i].metadata.durationSecs << ","
             << songs[i].playCount << ","
             << "\"" << songs[i].metadata.filePath << "\",";
        
        // Escribir géneros
        file << "\"";
        for (size_t j = 0; j < songs[i].metadata.genres.size(); j++) {
            file << songs[i].metadata.genres[j];
            if (j < songs[i].metadata.genres.size() - 1) {
                file << ";";
            }
        }
        file << "\"\n";
    }
    
    file.close();
    return true;
}

// Importar desde CSV
bool Library::importFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return false;
    }
    
    // Leer y descartar la línea de encabezado
    std::string header;
    std::getline(file, header);
    
    // Leer cada línea
    std::string line;
    size = 0;
    
    while (std::getline(file, line) && size < MAX_LIB) {
        std::stringstream ss(line);
        std::string token;
        
        // ID
        std::getline(ss, token, ',');
        songs[size].id = std::stoi(token);
        
        // Title (puede contener comas, por lo que está entre comillas)
        if (ss.peek() == '"') {
            ss.ignore(); // Ignorar la comilla inicial
            std::getline(ss, songs[size].metadata.title, '"');
            ss.ignore(); // Ignorar la coma después de la comilla final
        } else {
            std::getline(ss, songs[size].metadata.title, ',');
        }
        
        // Artist
        if (ss.peek() == '"') {
            ss.ignore();
            std::getline(ss, songs[size].metadata.artist, '"');
            ss.ignore();
        } else {
            std::getline(ss, songs[size].metadata.artist, ',');
        }
        
        // Album
        if (ss.peek() == '"') {
            ss.ignore();
            std::getline(ss, songs[size].metadata.album, '"');
            ss.ignore();
        } else {
            std::getline(ss, songs[size].metadata.album, ',');
        }
        
        // Year
        std::getline(ss, token, ',');
        songs[size].metadata.year = std::stoi(token);
        
        // Duration
        std::getline(ss, token, ',');
        songs[size].metadata.durationSecs = std::stoi(token);
        
        // PlayCount
        std::getline(ss, token, ',');
        songs[size].playCount = std::stoi(token);
        
        // FilePath
        if (ss.peek() == '"') {
            ss.ignore();
            std::getline(ss, songs[size].metadata.filePath, '"');
            ss.ignore();
        } else {
            std::getline(ss, songs[size].metadata.filePath, ',');
        }
        
        // Genres
        std::string genres;
        if (ss.peek() == '"') {
            ss.ignore();
            std::getline(ss, genres, '"');
        } else {
            std::getline(ss, genres);
        }
        
        // Dividir los géneros por punto y coma
        std::stringstream genreSS(genres);
        std::string genre;
        songs[size].metadata.genres.clear();
        
        while (std::getline(genreSS, genre, ';')) {
            songs[size].metadata.genres.push_back(genre);
        }
        
        size++;
    }
    
    file.close();
    return true;
}
