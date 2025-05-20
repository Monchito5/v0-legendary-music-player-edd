#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "../models/song.h"
#include <string>

// Nodo para la lista enlazada
struct PlaylistNode {
    Song song;
    PlaylistNode* next;
    
    PlaylistNode(const Song& s) : song(s), next(nullptr) {}
};

class Playlist {
private:
    std::string name;
    PlaylistNode* head;
    PlaylistNode* tail;
    int size;

public:
    // Constructor y destructor
    Playlist(const std::string& _name);
    ~Playlist();
    
    // Métodos básicos
    bool addSong(const Song& song);
    bool removeSong(int id);
    bool contains(int id) const;
    void clear();
    
    // Getters y setters
    std::string getName() const { return name; }
    void setName(const std::string& _name) { name = _name; }
    int getSize() const { return size; }
    
    // Iteración
    PlaylistNode* getHead() const { return head; }
    
    // Persistencia
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
};

#endif // PLAYLIST_H
