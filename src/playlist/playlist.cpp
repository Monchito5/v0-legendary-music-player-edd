#include "playlist.h"
#include <fstream>

Playlist::Playlist(const std::string& _name) : name(_name), head(nullptr), tail(nullptr), size(0) {}

Playlist::~Playlist() {
    clear();
}

bool Playlist::addSong(const Song& song) {
    PlaylistNode* newNode = new PlaylistNode(song);
    
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    
    size++;
    return true;
}

bool Playlist::removeSong(int id) {
    if (!head) {
        return false;
    }
    
    // Caso especial: eliminar el primer nodo
    if (head->song.id == id) {
        PlaylistNode* temp = head;
        head = head->next;
        
        // Si la lista queda vacía, actualizar tail
        if (!head) {
            tail = nullptr;
        }
        
        delete temp;
        size--;
        return true;
    }
    
    // Buscar el nodo a eliminar
    PlaylistNode* current = head;
    while (current->next && current->next->song.id != id) {
        current = current->next;
    }
    
    // Si se encontró el nodo
    if (current->next) {
        PlaylistNode* temp = current->next;
        current->next = temp->next;
        
        // Si se elimina el último nodo, actualizar tail
        if (temp == tail) {
            tail = current;
        }
        
        delete temp;
        size--;
        return true;
    }
    
    return false;
}

bool Playlist::contains(int id) const {
    PlaylistNode* current = head;
    while (current) {
        if (current->song.id == id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void Playlist::clear() {
    PlaylistNode* current = head;
    while (current) {
        PlaylistNode* temp = current;
        current = current->next;
        delete temp;
    }
    
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool Playlist::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }
    
    // Guardar el nombre de la playlist
    int nameLength = name.length();
    file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    file.write(name.c_str(), nameLength);
    
    // Guardar el tamaño de la playlist
    file.write(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Guardar los IDs de las canciones
    PlaylistNode* current = head;
    while (current) {
        file.write(reinterpret_cast<char*>(&current->song.id), sizeof(current->song.id));
        current = current->next;
    }
    
    file.close();
    return true;
}

bool Playlist::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }
    
    // Limpiar la playlist actual
    clear();
    
    // Leer el nombre de la playlist
    int nameLength;
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = nameBuffer;
    delete[] nameBuffer;
    
    // Leer el tamaño de la playlist
    int playlistSize;
    file.read(reinterpret_cast<char*>(&playlistSize), sizeof(playlistSize));
    
    // Leer los IDs de las canciones
    for (int i = 0; i < playlistSize; i++) {
        int songId;
        file.read(reinterpret_cast<char*>(&songId), sizeof(songId));
        
        // Crear una canción temporal con el ID leído
        Song tempSong;
        tempSong.id = songId;
        
        // Añadir la canción a la playlist
        addSong(tempSong);
    }
    
    file.close();
    return true;
}
