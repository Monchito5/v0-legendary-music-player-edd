#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "../models/song.h"
#include "../library/library.h"
#include "../playlist/playlist.h"
#include "../history/history_stack.h"
#include "../history/dyn_stack.h"
#include "../queue/circular_queue.h"
#include "../queue/dyn_queue.h"
#include "../search/trie.h"
#include "../search/bst.h"
#include "../search/avl.h"
#include "../search/hash_table.h"
#include "../priority/heap.h"
#include "../priority/dyn_heap.h"
#include "../recommendation/graph.h"
#include <string>
#include <vector>
#include <functional>

// Tipo de callback para eventos de reproducción
using PlaybackCallback = std::function<void(const Song&)>;

class MusicPlayer {
private:
    // Estructuras de datos principales
    Library library;
    std::vector<Playlist*> playlists;
    HistoryStack history;
    DynStack unlimitedHistory;
    CircularQueue playQueue;
    DynQueue dynamicQueue;
    Trie titleTrie;
    BST songBST;
    AVL songAVL;
    HashTable songTable;
    Heap topSongs;
    DynHeap recommendations;
    Graph genreGraph;
    
    // Estado de reproducción
    Song* currentSong;
    bool isPlaying;
    int volume;
    int position;
    
    // Callbacks
    PlaybackCallback onTrackEnd;
    
    // Métodos privados
    void buildSearchIndexes();
    void buildRecommendationGraph();

public:
    // Constructor y destructor
    MusicPlayer();
    ~MusicPlayer();
    
    // Gestión de biblioteca
    bool loadLibrary(const std::string& filename);
    bool saveLibrary(const std::string& filename);
    bool addSong(const Song& song);
    bool removeSong(int id);
    Song* findSong(int id);
    Song* findSongByTitle(const std::string& title);
    std::vector<Song*> searchSongs(const std::string& query);
    
    // Gestión de playlists
    Playlist* createPlaylist(const std::string& name);
    bool removePlaylist(const std::string& name);
    Playlist* findPlaylist(const std::string& name);
    bool addSongToPlaylist(int songId, const std::string& playlistName);
    bool removeSongFromPlaylist(int songId, const std::string& playlistName);
    
    // Control de reproducción
    bool play(int songId);
    bool playNext();
    bool playPrevious();
    void pause();
    void resume();
    void stop();
    void setVolume(int vol);
    void setPosition(int pos);
    
    // Cola de reproducción
    bool addToQueue(int songId);
    bool removeFromQueue(int index);
    void clearQueue();
    
    // Historial
    std::vector<Song> getHistory(int limit);
    void clearHistory();
    
    // Recomendaciones
    std::vector<Song*> getRecommendations(int songId, int limit);
    
    // Ordenamiento
    void sortLibraryByTitle();
    void sortLibraryByArtist();
    void sortLibraryByYear();
    
    // Eventos
    void setOnTrackEndCallback(PlaybackCallback callback);
    
    // Getters
    Song* getCurrentSong() const { return currentSong; }
    bool getIsPlaying() const { return isPlaying; }
    int getVolume() const { return volume; }
    int getPosition() const { return position; }
    Library& getLibrary() { return library; }
    std::vector<Playlist*>& getPlaylists() { return playlists; }
    
    // Autocompletado
    std::vector<std::string> autocompleteTitle(const std::string& prefix);
};

#endif // MUSIC_PLAYER_H
