#include "src/player/music_player.h"
#include <iostream>
#include <string>

void printSong(const Song& song) {
    std::cout << "ID: " << song.id << std::endl;
    std::cout << "Título: " << song.metadata.title << std::endl;
    std::cout << "Artista: " << song.metadata.artist << std::endl;
    std::cout << "Álbum: " << song.metadata.album << std::endl;
    std::cout << "Año: " << song.metadata.year << std::endl;
    std::cout << "Duración: " << song.metadata.durationSecs << " segundos" << std::endl;
    std::cout << "Reproducciones: " << song.playCount << std::endl;

    std::cout << "Géneros: ";
    for (size_t i = 0; i < song.metadata.genres.size(); i++) {
        std::cout << song.metadata.genres[i];
        if (i < song.metadata.genres.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Ruta: " << song.metadata.filePath << std::endl;
    std::cout << "------------------------" << std::endl;
}

void onTrackEnd(const Song& song) {
    std::cout << "La canción '" << song.metadata.title << "' ha terminado." << std::endl;
}

int main() {
    MusicPlayer player;

    // Configurar callback para fin de pista
    player.setOnTrackEndCallback(onTrackEnd);

    // Crear algunas canciones de ejemplo
    Song song1;
    song1.id = 1;
    song1.metadata.title = "Bohemian Rhapsody";
    song1.metadata.artist = "Queen";
    song1.metadata.album = "A Night at the Opera";
    song1.metadata.year = 1975;
    song1.metadata.durationSecs = 355;
    song1.metadata.genres = {"Rock", "Progressive Rock"};
    song1.metadata.filePath = "music/bohemian_rhapsody.mp3";

    Song song2;
    song2.id = 2;
    song2.metadata.title = "Stairway to Heaven";
    song2.metadata.artist = "Led Zeppelin";
    song2.metadata.album = "Led Zeppelin IV";
    song2.metadata.year = 1971;
    song2.metadata.durationSecs = 482;
    song2.metadata.genres = {"Rock", "Hard Rock"};
    song2.metadata.filePath = "music/stairway_to_heaven.mp3";

    Song song3;
    song3.id = 3;
    song3.metadata.title = "Hotel California";
    song3.metadata.artist = "Eagles";
    song3.metadata.album = "Hotel California";
    song3.metadata.year = 1976;
    song3.metadata.durationSecs = 390;
    song3.metadata.genres = {"Rock", "Soft Rock"};
    song3.metadata.filePath = "music/hotel_california.mp3";

    // Añadir canciones a la biblioteca
    player.addSong(song1);
    player.addSong(song2);
    player.addSong(song3);

    // Crear una playlist
    Playlist* favorites = player.createPlaylist("Favoritos");
    player.addSongToPlaylist(1, "Favoritos");
    player.addSongToPlaylist(3, "Favoritos");

    // Reproducir una canción
    player.play(1);
    std::cout << "Reproduciendo: " << player.getCurrentSong()->metadata.title << std::endl;

    // Añadir a la cola
    player.addToQueue(2);
    player.addToQueue(3);

    // Reproducir siguiente
    player.playNext();
    std::cout << "Siguiente: " << player.getCurrentSong()->metadata.title << std::endl;

    // Reproducir anterior
    player.playPrevious();
    std::cout << "Anterior: " << player.getCurrentSong()->metadata.title << std::endl;

    // Buscar canciones
    std::vector<Song*> results = player.searchSongs("Rock");
    std::cout << "Resultados de búsqueda para 'Rock':" << std::endl;
    for (Song* song : results) {
        std::cout << "- " << song->metadata.title << " (" << song->metadata.artist << ")" << std::endl;
    }

    // Autocompletado
    std::vector<std::string> suggestions = player.autocompleteTitle("Ho");
    std::cout << "Autocompletado para 'Ho':" << std::endl;
    for (const std::string& suggestion : suggestions) {
        std::cout << "- " << suggestion << std::endl;
    }

    // Obtener recomendaciones
    std::vector<Song*> recommendations = player.getRecommendations(1, 2);
    std::cout << "Recomendaciones para '" << player.getCurrentSong()->metadata.title << "':" << std::endl;
    for (Song* song : recommendations) {
        std::cout << "- " << song->metadata.title << " (" << song->metadata.artist << ")" << std::endl;
    }

    // Guardar biblioteca
    player.saveLibrary("library.dat");

    return 0;
}
