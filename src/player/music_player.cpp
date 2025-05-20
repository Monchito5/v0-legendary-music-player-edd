#include "music_player.h"
#include <algorithm>

MusicPlayer::MusicPlayer() : currentSong(nullptr), isPlaying(false), volume(50), position(0) {
    // Configurar el comparador para el heap de canciones más reproducidas
    topSongs.setComparator([](const Song& a, const Song& b) {
        return a.playCount > b.playCount; // Max-heap por reproducciones
    });
    
    // Configurar el comparador para el heap de recomendaciones
    recommendations.setComparator([](const Song& a, const Song& b) {
        return a.playCount > b.playCount; // Max-heap por reproducciones
    });
}

MusicPlayer::~MusicPlayer() {
    // Liberar memoria de las playlists
    for (Playlist* playlist : playlists) {
        delete playlist;
    }
}

bool MusicPlayer::loadLibrary(const std::string& filename) {
    bool success = library.loadFromFile(filename);
    
    if (success) {
        buildSearchIndexes();
        buildRecommendationGraph();
    }
    
    return success;
}

bool MusicPlayer::saveLibrary(const std::string& filename) {
    return library.saveToFile(filename);
}

bool MusicPlayer::addSong(const Song& song) {
    bool success = library.addSong(song);
    
    if (success) {
        // Actualizar estructuras de búsqueda
        titleTrie.insert(song.metadata.title);
        songBST.insert(song);
        songAVL.insert(song);
        songTable.insert(song.metadata.title, library.findSongById(song.id));
        
        // Actualizar grafo de recomendaciones
        genreGraph.addVertex(song.id);
        
        // Conectar con canciones del mismo género
        for (const auto& genre : song.metadata.genres) {
            for (int i = 0; i < library.getSize(); i++) {
                Song* otherSong = &library.getSongs()[i];
                
                if (otherSong->id != song.id) {
                    for (const auto& otherGenre : otherSong->metadata.genres) {
                        if (genre == otherGenre) {
                            // Añadir conexión bidireccional con peso 1.0
                            genreGraph.addEdge(song.id, otherSong->id, 1.0f);
                            genreGraph.addEdge(otherSong->id, song.id, 1.0f);
                            break;
                        }
                    }
                }
            }
        }
    }
    
    return success;
}

bool MusicPlayer::removeSong(int id) {
    Song* song = library.findSongById(id);
    
    if (!song) {
        return false;
    }
    
    // Eliminar de las estructuras de búsqueda
    songBST.remove(id);
    songAVL.remove(id);
    songTable.remove(song->metadata.title);
    
    // Eliminar del grafo de recomendaciones
    genreGraph.removeVertex(id);
    
    // Eliminar de la biblioteca
    return library.removeSong(id);
}

Song* MusicPlayer::findSong(int id) {
    return library.findSongById(id);
}

Song* MusicPlayer::findSongByTitle(const std::string& title) {
    // Usar la tabla hash para búsqueda O(1)
    return songTable.search(title);
}

std::vector<Song*> MusicPlayer::searchSongs(const std::string& query) {
    std::vector<Song*> results;
    
    // Buscar en la biblioteca
    for (int i = 0; i < library.getSize(); i++) {
        Song* song = &library.getSongs()[i];
        
        // Buscar en título, artista y álbum
        if (song->metadata.title.find(query) != std::string::npos ||
            song->metadata.artist.find(query) != std::string::npos ||
            song->metadata.album.find(query) != std::string::npos) {
            results.push_back(song);
        }
    }
    
    return results;
}

Playlist* MusicPlayer::createPlaylist(const std::string& name) {
    // Verificar si ya existe una playlist con ese nombre
    for (Playlist* playlist : playlists) {
        if (playlist->getName() == name) {
            return playlist;
        }
    }
    
    // Crear nueva playlist
    Playlist* newPlaylist = new Playlist(name);
    playlists.push_back(newPlaylist);
    
    return newPlaylist;
}

bool MusicPlayer::removePlaylist(const std::string& name) {
    for (auto it = playlists.begin(); it != playlists.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            playlists.erase(it);
            return true;
        }
    }
    
    return false;
}

Playlist* MusicPlayer::findPlaylist(const std::string& name) {
    for (Playlist* playlist : playlists) {
        if (playlist->getName() == name) {
            return playlist;
        }
    }
    
    return nullptr;
}

bool MusicPlayer::addSongToPlaylist(int songId, const std::string& playlistName) {
    Song* song = findSong(songId);
    if (!song) {
        return false;
    }
    
    Playlist* playlist = findPlaylist(playlistName);
    if (!playlist) {
        return false;
    }
    
    return playlist->addSong(*song);
}

bool MusicPlayer::removeSongFromPlaylist(int songId, const std::string& playlistName) {
    Playlist* playlist = findPlaylist(playlistName);
    if (!playlist) {
        return false;
    }
    
    return playlist->removeSong(songId);
}

bool MusicPlayer::play(int songId) {
    Song* song = findSong(songId);
    if (!song) {
        return false;
    }
    
    // Guardar la canción actual en el historial si existe
    if (currentSong) {
        history.push(*currentSong);
        unlimitedHistory.push(*currentSong);
    }
    
    // Establecer la nueva canción actual
    currentSong = song;
    isPlaying = true;
    position = 0;
    
    // Incrementar el contador de reproducciones
    song->playCount++;
    
    return true;
}

bool MusicPlayer::playNext() {
    // Primero intentar reproducir desde la cola
    Song nextSong;
    if (playQueue.dequeue(nextSong)) {
        return play(nextSong.id);
    }
    
    // Si no hay canciones en la cola, reproducir la siguiente en la biblioteca
    if (!currentSong) {
        return false;
    }
    
    // Buscar la siguiente canción en la biblioteca
    bool found = false;
    for (int i = 0; i < library.getSize(); i++) {
        if (found) {
            return play(library.getSongs()[i].id);
        }
        
        if (library.getSongs()[i].id == currentSong->id) {
            found = true;
        }
    }
    
    // Si era la última canción, volver a la primera
    if (library.getSize() > 0) {
        return play(library.getSongs()[0].id);
    }
    
    return false;
}

bool MusicPlayer::playPrevious() {
    // Obtener la canción anterior del historial
    Song prevSong;
    if (history.pop(prevSong)) {
        // No guardar en el historial al reproducir una canción anterior
        Song* song = findSong(prevSong.id);
        if (song) {
            currentSong = song;
            isPlaying = true;
            position = 0;
            song->playCount++;
            return true;
        }
    }
    
    return false;
}

void MusicPlayer::pause() {
    isPlaying = false;
}

void MusicPlayer::resume() {
    isPlaying = true;
}

void MusicPlayer::stop() {
    isPlaying = false;
    position = 0;
}

void MusicPlayer::setVolume(int vol) {
    volume = std::max(0, std::min(100, vol));
}

void MusicPlayer::setPosition(int pos) {
    if (currentSong) {
        position = std::max(0, std::min(currentSong->metadata.durationSecs, pos));
    }
}

bool MusicPlayer::addToQueue(int songId) {
    Song* song = findSong(songId);
    if (!song) {
        return false;
    }
    
    return playQueue.enqueue(*song);
}

bool MusicPlayer::removeFromQueue(int index) {
    // No se puede eliminar directamente de una cola circular
    // Se necesitaría implementar una función específica
    return false;
}

void MusicPlayer::clearQueue() {
    playQueue.clear();
}

std::vector<Song> MusicPlayer::getHistory(int limit) {
    std::vector<Song> result;
    
    // Crear una copia temporal del historial
    HistoryStack tempHistory = history;
    
    // Extraer hasta 'limit' canciones
    for (int i = 0; i < limit; i++) {
        Song song;
        if (tempHistory.pop(song)) {
            result.push_back(song);
        } else {
            break;
        }
    }
    
    return result;
}

void MusicPlayer::clearHistory() {
    history.clear();
    unlimitedHistory.clear();
}

std::vector<Song*> MusicPlayer::getRecommendations(int songId, int limit) {
    std::vector<Song*> result;
    
    // Obtener recomendaciones del grafo
    std::vector<std::pair<int, float>> recommendations = genreGraph.getRecommendations(songId, limit);
    
    // Convertir IDs a punteros de Song
    for (const auto& rec : recommendations) {
        Song* song = findSong(rec.first);
        if (song) {
            result.push_back(song);
        }
    }
    
    return result;
}

void MusicPlayer::sortLibraryByTitle() {
    library.bubbleSort();
}

void MusicPlayer::sortLibraryByArtist() {
    // Implementar ordenamiento por artista
    Song* songs = library.getSongs();
    int size = library.getSize();
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (songs[j].metadata.artist > songs[j + 1].metadata.artist) {
                std::swap(songs[j], songs[j + 1]);
            }
        }
    }
}

void MusicPlayer::sortLibraryByYear() {
    // Implementar ordenamiento por año
    Song* songs = library.getSongs();
    int size = library.getSize();
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (songs[j].metadata.year > songs[j + 1].metadata.year) {
                std::swap(songs[j], songs[j + 1]);
            }
        }
    }
}

void MusicPlayer::setOnTrackEndCallback(PlaybackCallback callback) {
    onTrackEnd = callback;
}

void MusicPlayer::buildSearchIndexes() {
    // Construir índices de búsqueda
    titleTrie = Trie(); // Reiniciar
    songBST = BST();
    songAVL = AVL();
    songTable = HashTable();
    
    for (int i = 0; i < library.getSize(); i++) {
        Song& song = library.getSongs()[i];
        
        titleTrie.insert(song.metadata.title);
        songBST.insert(song);
        songAVL.insert(song);
        songTable.insert(song.metadata.title, &song);
    }
}

void MusicPlayer::buildRecommendationGraph() {
    // Construir grafo de recomendaciones
    genreGraph = Graph();
    
    // Añadir vértices para todas las canciones
    for (int i = 0; i < library.getSize(); i++) {
        Song& song = library.getSongs()[i];
        genreGraph.addVertex(song.id);
    }
    
    // Conectar canciones con géneros similares
    for (int i = 0; i < library.getSize(); i++) {
        Song& song1 = library.getSongs()[i];
        
        for (int j = i + 1; j < library.getSize(); j++) {
            Song& song2 = library.getSongs()[j];
            
            // Calcular similitud de géneros
            float similarity = 0.0f;
            
            for (const auto& genre1 : song1.metadata.genres) {
                for (const auto& genre2 : song2.metadata.genres) {
                    if (genre1 == genre2) {
                        similarity += 1.0f;
                    }
                }
            }
            
            // Normalizar por el número total de géneros
            int totalGenres = song1.metadata.genres.size() + song2.metadata.genres.size();
            if (totalGenres > 0) {
                similarity /= totalGenres;
            }
            
            // Añadir arista si hay similitud
            if (similarity > 0.0f) {
                genreGraph.addEdge(song1.id, song2.id, similarity);
                genreGraph.addEdge(song2.id, song1.id, similarity);
            }
        }
    }
}

std::vector<std::string> MusicPlayer::autocompleteTitle(const std::string& prefix) {
    return titleTrie.autocomplete(prefix);
}
