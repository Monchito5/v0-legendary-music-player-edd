/**
 * @file main.cpp
 * @brief Reproductor de música simplificado que utiliza estructuras de datos desde cero
 * @author v0
 * @date Mayo 2025
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdexcept>

// ==================== ESTRUCTURAS DE DATOS ====================

/**
 * @brief Implementación de una lista enlazada genérica
 */
template <typename T>
class Lista {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& _dato) : dato(_dato), siguiente(nullptr) {}
    };

    Nodo* primero;
    Nodo* ultimo;
    int tamanio;

public:
    // Constructor
    Lista() : primero(nullptr), ultimo(nullptr), tamanio(0) {}

    // Destructor
    ~Lista() {
        vaciar();
    }

    // Agregar elemento al final
    void agregar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);

        if (primero == nullptr) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }

        tamanio++;
    }

    // Insertar elemento en una posición específica
    bool insertar(int indice, const T& elemento) {
        if (indice < 0 || indice > tamanio) {
            return false;
        }

        if (indice == 0) {
            Nodo* nuevo = new Nodo(elemento);
            nuevo->siguiente = primero;
            primero = nuevo;

            if (ultimo == nullptr) {
                ultimo = nuevo;
            }

            tamanio++;
            return true;
        }

        if (indice == tamanio) {
            agregar(elemento);
            return true;
        }

        Nodo* actual = primero;
        for (int i = 0; i < indice - 1; i++) {
            actual = actual->siguiente;
        }

        Nodo* nuevo = new Nodo(elemento);
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;

        tamanio++;
        return true;
    }

    // Eliminar elemento en una posición específica
    bool eliminar(int indice) {
        if (indice < 0 || indice >= tamanio || primero == nullptr) {
            return false;
        }

        Nodo* aEliminar;

        if (indice == 0) {
            aEliminar = primero;
            primero = primero->siguiente;

            if (primero == nullptr) {
                ultimo = nullptr;
            }
        } else {
            Nodo* actual = primero;
            for (int i = 0; i < indice - 1; i++) {
                actual = actual->siguiente;
            }

            aEliminar = actual->siguiente;
            actual->siguiente = aEliminar->siguiente;

            if (aEliminar == ultimo) {
                ultimo = actual;
            }
        }

        delete aEliminar;
        tamanio--;
        return true;
    }

    // Modificar elemento en una posición específica
    bool modificar(int indice, const T& elemento) {
        if (indice < 0 || indice >= tamanio) {
            return false;
        }

        Nodo* actual = primero;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }

        actual->dato = elemento;
        return true;
    }

    // Obtener elemento en una posición específica
    T obtener(int indice) const {
        if (indice < 0 || indice >= tamanio) {
            throw std::out_of_range("Índice fuera de rango");
        }

        Nodo* actual = primero;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }

        return actual->dato;
    }

    // Buscar índice de un elemento
    int buscar(const T& elemento) const {
        Nodo* actual = primero;
        int indice = 0;

        while (actual != nullptr) {
            if (actual->dato == elemento) {
                return indice;
            }

            actual = actual->siguiente;
            indice++;
        }

        return -1;
    }

    // Verificar si la lista contiene un elemento
    bool contiene(const T& elemento) const {
        return buscar(elemento) != -1;
    }

    // Obtener tamaño de la lista
    int obtenerTamanio() const {
        return tamanio;
    }

    // Verificar si la lista está vacía
    bool estaVacia() const {
        return tamanio == 0;
    }

    // Vaciar la lista
    void vaciar() {
        while (primero != nullptr) {
            Nodo* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }

        ultimo = nullptr;
        tamanio = 0;
    }
};

/**
 * @brief Implementación de una pila genérica
 */
template <typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& _dato) : dato(_dato), siguiente(nullptr) {}
    };

    Nodo* cima_;
    int tamanio;

public:
    // Constructor
    Pila() : cima_(nullptr), tamanio(0) {}

    // Destructor
    ~Pila() {
        vaciar();
    }

    // Apilar elemento
    void apilar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);
        nuevo->siguiente = cima_;
        cima_ = nuevo;
        tamanio++;
    }

    // Desapilar elemento
    bool desapilar() {
        if (estaVacia()) {
            return false;
        }

        Nodo* temp = cima_;
        cima_ = cima_->siguiente;
        delete temp;
        tamanio--;
        return true;
    }

    // Obtener elemento en la cima
    T cima() const {
        if (estaVacia()) {
            throw std::out_of_range("La pila está vacía");
        }
        return cima_->dato;
    }

    // Verificar si la pila está vacía
    bool estaVacia() const {
        return tamanio == 0;
    }

    // Obtener tamaño de la pila
    int obtenerTamanio() const {
        return tamanio;
    }

    // Vaciar la pila
    void vaciar() {
        while (!estaVacia()) {
            desapilar();
        }
    }
};

/**
 * @brief Implementación de una cola genérica
 */
template <typename T>
class Cola {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& _dato) : dato(_dato), siguiente(nullptr) {}
    };

    Nodo* frente_;
    Nodo* final_;
    int tamanio;

public:
    // Constructor
    Cola() : frente_(nullptr), final_(nullptr), tamanio(0) {}

    // Destructor
    ~Cola() {
        vaciar();
    }

    // Encolar elemento
    void encolar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);

        if (estaVacia()) {
            frente_ = nuevo;
            final_ = nuevo;
        } else {
            final_->siguiente = nuevo;
            final_ = nuevo;
        }

        tamanio++;
    }

    // Desencolar elemento
    bool desencolar() {
        if (estaVacia()) {
            return false;
        }

        Nodo* temp = frente_;
        frente_ = frente_->siguiente;

        if (frente_ == nullptr) {
            final_ = nullptr;
        }

        delete temp;
        tamanio--;
        return true;
    }

    // Obtener elemento en el frente
    T frente() const {
        if (estaVacia()) {
            throw std::out_of_range("La cola está vacía");
        }
        return frente_->dato;
    }

    // Verificar si la cola está vacía
    bool estaVacia() const {
        return tamanio == 0;
    }

    // Obtener tamaño de la cola
    int obtenerTamanio() const {
        return tamanio;
    }

    // Vaciar la cola
    void vaciar() {
        while (!estaVacia()) {
            desencolar();
        }
    }
};

/**
 * @brief Implementación de un grafo dirigido
 */
template <typename T>
class Grafo {
private:
    struct Arista {
        int destino;
        int peso;

        Arista(int _destino, int _peso = 1) : destino(_destino), peso(_peso) {}

        bool operator==(const Arista& otra) const {
            return destino == otra.destino && peso == otra.peso;
        }
    };

    Lista<T> vertices;
    Lista<Lista<Arista>> adyacencia;

public:
    // Constructor
    Grafo() {}

    // Destructor
    ~Grafo() {
        vaciar();
    }

    // Agregar vértice
    bool agregarVertice(const T& vertice) {
        if (existeVertice(vertice)) {
            return false;
        }

        vertices.agregar(vertice);
        adyacencia.agregar(Lista<Arista>());
        return true;
    }

    // Verificar si existe un vértice
    bool existeVertice(const T& vertice) const {
        return buscarVertice(vertice) != -1;
    }

    // Buscar índice de un vértice
    int buscarVertice(const T& vertice) const {
        for (int i = 0; i < vertices.obtenerTamanio(); i++) {
            if (vertices.obtener(i) == vertice) {
                return i;
            }
        }
        return -1;
    }

    // Agregar arista
    bool agregarArista(const T& origen, const T& destino, int peso = 1) {
        int indiceOrigen = buscarVertice(origen);
        int indiceDestino = buscarVertice(destino);

        if (indiceOrigen == -1 || indiceDestino == -1) {
            return false;
        }

        // Verificar si la arista ya existe
        Lista<Arista> listaAdyacencia = adyacencia.obtener(indiceOrigen);
        for (int i = 0; i < listaAdyacencia.obtenerTamanio(); i++) {
            if (listaAdyacencia.obtener(i).destino == indiceDestino) {
                return false;
            }
        }

        // Agregar la arista
        listaAdyacencia.agregar(Arista(indiceDestino, peso));
        adyacencia.modificar(indiceOrigen, listaAdyacencia);
        return true;
    }

    // Obtener vértices adyacentes (BFS)
    Lista<T> obtenerVecinosBFS(const T& origen) const {
        Lista<T> resultado;
        int indiceOrigen = buscarVertice(origen);

        if (indiceOrigen == -1) {
            return resultado;
        }

        // Arreglo para marcar vértices visitados
        bool* visitados = new bool[vertices.obtenerTamanio()];
        for (int i = 0; i < vertices.obtenerTamanio(); i++) {
            visitados[i] = false;
        }

        // Cola para BFS
        Cola<int> cola;
        cola.encolar(indiceOrigen);
        visitados[indiceOrigen] = true;

        while (!cola.estaVacia()) {
            int actual = cola.frente();
            cola.desencolar();

            // No agregar el vértice origen al resultado
            if (actual != indiceOrigen) {
                resultado.agregar(vertices.obtener(actual));
            }

            // Explorar vecinos
            Lista<Arista> vecinos = adyacencia.obtener(actual);
            for (int i = 0; i < vecinos.obtenerTamanio(); i++) {
                int vecino = vecinos.obtener(i).destino;
                if (!visitados[vecino]) {
                    cola.encolar(vecino);
                    visitados[vecino] = true;
                }
            }
        }

        delete[] visitados;
        return resultado;
    }

    // Obtener vértices adyacentes (DFS)
    Lista<T> obtenerVecinosDFS(const T& origen) const {
        Lista<T> resultado;
        int indiceOrigen = buscarVertice(origen);

        if (indiceOrigen == -1) {
            return resultado;
        }

        // Arreglo para marcar vértices visitados
        bool* visitados = new bool[vertices.obtenerTamanio()];
        for (int i = 0; i < vertices.obtenerTamanio(); i++) {
            visitados[i] = false;
        }

        // Llamada al método auxiliar recursivo
        dfsRecursivo(indiceOrigen, resultado, visitados, indiceOrigen);

        delete[] visitados;
        return resultado;
    }

    // Vaciar el grafo
    void vaciar() {
        vertices.vaciar();
        adyacencia.vaciar();
    }

    // Obtener número de vértices
    int obtenerNumVertices() const {
        return vertices.obtenerTamanio();
    }

private:
    // Método auxiliar recursivo para DFS
    void dfsRecursivo(int actual, Lista<T>& resultado, bool* visitados, int origen) const {
        visitados[actual] = true;

        // No agregar el vértice origen al resultado
        if (actual != origen) {
            resultado.agregar(vertices.obtener(actual));
        }

        // Explorar vecinos
        Lista<Arista> vecinos = adyacencia.obtener(actual);
        for (int i = 0; i < vecinos.obtenerTamanio(); i++) {
            int vecino = vecinos.obtener(i).destino;
            if (!visitados[vecino]) {
                dfsRecursivo(vecino, resultado, visitados, origen);
            }
        }
    }
};

// ==================== UTILIDADES ====================

/**
 * @brief Utilidades para manejar caracteres UTF-8 en español
 */
class UTF8Util {
public:
    // Formatea un texto para que tenga un ancho específico
    static std::string formatearTexto(const std::string& texto, int ancho) {
        // Verificar límites para evitar errores
        if (ancho <= 0) {
            return "";
        }

        if (texto.length() > static_cast<size_t>(ancho)) {
            // Asegurar que no excedemos el tamaño del string
            size_t longitud = std::min(texto.length(), static_cast<size_t>(ancho - 3));
            return texto.substr(0, longitud) + "...";
        }

        // Limitar el tamaño del padding para evitar strings muy grandes
        size_t padding = std::min(static_cast<size_t>(ancho - texto.length()), static_cast<size_t>(100));
        return texto + std::string(padding, ' ');
    }

    // Crea una línea de separación
    static std::string formatearLinea(int longitud) {
        // Limitar la longitud para evitar strings muy grandes
        longitud = std::min(longitud, 200);
        return std::string(longitud, '-');
    }

    // Formatea un título centrado
    static std::string formatearTitulo(const std::string& titulo) {
        const int ancho = 80;

        // Verificar que el título no sea demasiado largo
        if (titulo.length() > static_cast<size_t>(ancho)) {
            return titulo.substr(0, ancho - 3) + "...";
        }

        int espacios = (ancho - titulo.length()) / 2;
        espacios = std::max(0, espacios); // Asegurar que no sea negativo

        return std::string(espacios, ' ') + titulo;
    }

    // Caracteres especiales en español
    static std::string A_ACENTO() { return "á"; }
    static std::string E_ACENTO() { return "é"; }
    static std::string I_ACENTO() { return "í"; }
    static std::string O_ACENTO() { return "ó"; }
    static std::string U_ACENTO() { return "ú"; }
    static std::string N_TILDE() { return "ñ"; }
};

// ==================== ALGORITMOS ====================

/**
 * @brief Algoritmos de búsqueda
 */
class Busqueda {
public:
    // Verifica si una cadena contiene otra (insensible a mayúsculas/minúsculas)
    static bool contieneCadenaInsensible(const std::string& texto, const std::string& busqueda) {
        std::string textoLower = texto;
        std::string busquedaLower = busqueda;

        // Convertir a minúsculas
        std::transform(textoLower.begin(), textoLower.end(), textoLower.begin(),
                      [](unsigned char c){ return std::tolower(c); });
        std::transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(),
                      [](unsigned char c){ return std::tolower(c); });

        // Buscar subcadena
        return textoLower.find(busquedaLower) != std::string::npos;
    }
};

/**
 * @brief Algoritmos de ordenamiento
 */
template <typename T>
class Ordenamiento {
public:
    // Ordena una lista por un campo específico
    static void ordenarPorCampo(Lista<T>& lista,
                              std::function<bool(const T&, const T&)> comparador,
                              bool ascendente = true) {
        int n = lista.obtenerTamanio();

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                T elemento1 = lista.obtener(j);
                T elemento2 = lista.obtener(j + 1);

                bool debeIntercambiar = ascendente ?
                    comparador(elemento2, elemento1) :
                    comparador(elemento1, elemento2);

                if (debeIntercambiar) {
                    lista.modificar(j, elemento2);
                    lista.modificar(j + 1, elemento1);
                }
            }
        }
    }
};

// ==================== MODELOS ====================

/**
 * @brief Estructura que representa una canción
 */
struct Cancion {
    std::string titulo;           // Título de la canción
    std::string artista;          // Artista o intérprete
    std::string album;            // Álbum al que pertenece
    int anio;                     // Año de lanzamiento
    int duracion;                 // Duración en segundos
    Lista<std::string> generos;   // Géneros musicales

    // Constructor por defecto
    Cancion() : titulo(""), artista(""), album(""), anio(0), duracion(0) {}

    // Constructor con parámetros
    Cancion(const std::string& _titulo, const std::string& _artista, const std::string& _album,
            int _anio, int _duracion)
        : titulo(_titulo), artista(_artista), album(_album), anio(_anio), duracion(_duracion) {}

    // Métodos de comparación para ordenamiento
    bool compararPorTitulo(const Cancion& otra) const {
        return titulo < otra.titulo;
    }

    bool compararPorArtista(const Cancion& otra) const {
        return artista < otra.artista;
    }

    bool compararPorAlbum(const Cancion& otra) const {
        return album < otra.album;
    }

    bool compararPorAnio(const Cancion& otra) const {
        return anio < otra.anio;
    }

    // Operadores de comparación
    bool operator==(const Cancion& otra) const {
        return titulo == otra.titulo && artista == otra.artista;
    }

    bool operator!=(const Cancion& otra) const {
        return !(*this == otra);
    }

    // Método para formatear la duración
    std::string obtenerDuracionFormateada() const {
        int minutos = duracion / 60;
        int segundos = duracion % 60;
        char buffer[10];
        sprintf(buffer, "%02d:%02d", minutos, segundos);
        return std::string(buffer);
    }
};

/**
 * @brief Estructura que representa una lista de reproducción
 */
struct ListaReproduccion {
    std::string nombre;           // Nombre de la lista de reproducción
    std::string descripcion;      // Descripción opcional
    Lista<int> canciones;         // Índices de canciones en la biblioteca

    // Constructor por defecto
    ListaReproduccion() : nombre("Nueva Lista"), descripcion("") {}

    // Constructor con nombre
    ListaReproduccion(const std::string& _nombre) : nombre(_nombre), descripcion("") {}

    // Constructor completo
    ListaReproduccion(const std::string& _nombre, const std::string& _descripcion) :
        nombre(_nombre), descripcion(_descripcion) {}

    // Agrega una canción a la lista de reproducción
    bool agregarCancion(int indiceCancion) {
        if (canciones.contiene(indiceCancion)) {
            return false;
        }

        canciones.agregar(indiceCancion);
        return true;
    }

    // Elimina una canción de la lista de reproducción
    bool eliminarCancion(int indiceCancion) {
        int posicion = canciones.buscar(indiceCancion);
        if (posicion == -1) {
            return false;
        }

        canciones.eliminar(posicion);
        return true;
    }

    // Verifica si la lista contiene una canción específica
    bool contieneCancion(int indiceCancion) const {
        return canciones.contiene(indiceCancion);
    }

    // Obtiene el número de canciones en la lista
    int obtenerNumCanciones() const {
        return canciones.obtenerTamanio();
    }

    // Vacía la lista de reproducción
    void vaciar() {
        canciones.vaciar();
    }
};

// ==================== REPRODUCTOR DE MÚSICA ====================

/**
 * @brief Clase principal del reproductor de música
 */
class ReproductorMusica {
private:
    Lista<Cancion> canciones;
    Lista<ListaReproduccion> listasReproduccion;
    Pila<int> historial;
    Cola<int> colaReproduccion;
    Grafo<std::string> grafoAfinidad;

    int cancionActual;
    bool reproduciendo;

    // Método para cargar datos ficticios
    void cargarDatosFicticios() {
        try {
            // Canciones ficticias
            Cancion cancion1("Bohemian Rhapsody", "Queen", "A Night at the Opera", 1975, 355);
            cancion1.generos.agregar("Rock");
            cancion1.generos.agregar("Progresivo");

            Cancion cancion2("Imagine", "John Lennon", "Imagine", 1971, 183);
            cancion2.generos.agregar("Rock");
            cancion2.generos.agregar("Pop");

            Cancion cancion3("Billie Jean", "Michael Jackson", "Thriller", 1982, 294);
            cancion3.generos.agregar("Pop");
            cancion3.generos.agregar("Funk");

            Cancion cancion4("Hotel California", "Eagles", "Hotel California", 1976, 390);
            cancion4.generos.agregar("Rock");

            Cancion cancion5("Sweet Child O' Mine", "Guns N' Roses", "Appetite for Destruction", 1987, 356);
            cancion5.generos.agregar("Rock");
            cancion5.generos.agregar("Hard Rock");

            Cancion cancion6("Smells Like Teen Spirit", "Nirvana", "Nevermind", 1991, 301);
            cancion6.generos.agregar("Grunge");
            cancion6.generos.agregar("Rock Alternativo");

            Cancion cancion7("Like a Rolling Stone", "Bob Dylan", "Highway 61 Revisited", 1965, 379);
            cancion7.generos.agregar("Folk Rock");

            Cancion cancion8("I Want to Hold Your Hand", "The Beatles", "Meet the Beatles!", 1963, 146);
            cancion8.generos.agregar("Rock");
            cancion8.generos.agregar("Pop");

            Cancion cancion9("Purple Haze", "Jimi Hendrix", "Are You Experienced", 1967, 170);
            cancion9.generos.agregar("Rock Psicodélico");
            cancion9.generos.agregar("Hard Rock");

            Cancion cancion10("Johnny B. Goode", "Chuck Berry", "Chuck Berry Is on Top", 1958, 161);
            cancion10.generos.agregar("Rock and Roll");

            // Agregar canciones a la biblioteca
            agregarCancion(cancion1);
            agregarCancion(cancion2);
            agregarCancion(cancion3);
            agregarCancion(cancion4);
            agregarCancion(cancion5);
            agregarCancion(cancion6);
            agregarCancion(cancion7);
            agregarCancion(cancion8);
            agregarCancion(cancion9);
            agregarCancion(cancion10);

            // Listas de reproducción ficticias
            ListaReproduccion lista1("Clásicos del Rock", "Las mejores canciones de rock de todos los tiempos");
            lista1.agregarCancion(0);  // Bohemian Rhapsody
            lista1.agregarCancion(3);  // Hotel California
            lista1.agregarCancion(4);  // Sweet Child O' Mine
            lista1.agregarCancion(5);  // Smells Like Teen Spirit

            ListaReproduccion lista2("Pop Hits", "Éxitos del pop a través de las décadas");
            lista2.agregarCancion(1);  // Imagine
            lista2.agregarCancion(2);  // Billie Jean
            lista2.agregarCancion(7);  // I Want to Hold Your Hand

            // Agregar listas a la biblioteca
            listasReproduccion.agregar(lista1);
            listasReproduccion.agregar(lista2);

            // Construir grafo de afinidad
            construirGrafoAfinidad();
        } catch (const std::exception& e) {
            std::cerr << "Error al cargar datos ficticios: " << e.what() << std::endl;
        }
    }

    // Construir grafo de afinidad para recomendaciones
    void construirGrafoAfinidad() {
        try {
            grafoAfinidad.vaciar();

            // Agregar todos los artistas y géneros como vértices
            for (int i = 0; i < canciones.obtenerTamanio(); i++) {
                Cancion cancion = canciones.obtener(i);

                if (!grafoAfinidad.existeVertice(cancion.artista)) {
                    grafoAfinidad.agregarVertice(cancion.artista);
                }

                for (int j = 0; j < cancion.generos.obtenerTamanio(); j++) {
                    std::string genero = cancion.generos.obtener(j);
                    if (!grafoAfinidad.existeVertice(genero)) {
                        grafoAfinidad.agregarVertice(genero);
                    }
                }
            }

            // Conectar artistas con sus géneros
            for (int i = 0; i < canciones.obtenerTamanio(); i++) {
                Cancion cancion = canciones.obtener(i);

                for (int j = 0; j < cancion.generos.obtenerTamanio(); j++) {
                    std::string genero = cancion.generos.obtener(j);
                    grafoAfinidad.agregarArista(cancion.artista, genero);
                    grafoAfinidad.agregarArista(genero, cancion.artista);
                }
            }

            // Conectar artistas que comparten géneros
            for (int i = 0; i < canciones.obtenerTamanio(); i++) {
                Cancion cancion1 = canciones.obtener(i);

                for (int j = i + 1; j < canciones.obtenerTamanio(); j++) {
                    Cancion cancion2 = canciones.obtener(j);

                    if (cancion1.artista != cancion2.artista) {
                        bool compartenGenero = false;

                        for (int k = 0; k < cancion1.generos.obtenerTamanio() && !compartenGenero; k++) {
                            std::string genero1 = cancion1.generos.obtener(k);

                            for (int l = 0; l < cancion2.generos.obtenerTamanio() && !compartenGenero; l++) {
                                std::string genero2 = cancion2.generos.obtener(l);

                                if (genero1 == genero2) {
                                    compartenGenero = true;
                                }
                            }
                        }

                        if (compartenGenero) {
                            grafoAfinidad.agregarArista(cancion1.artista, cancion2.artista);
                            grafoAfinidad.agregarArista(cancion2.artista, cancion1.artista);
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al construir grafo de afinidad: " << e.what() << std::endl;
        }
    }

public:
    // Constructor
    ReproductorMusica()
        : cancionActual(-1),
          reproduciendo(false) {

        cargarDatosFicticios();
    }

    // Métodos para gestionar canciones
    void agregarCancion(const Cancion& cancion) {
        canciones.agregar(cancion);
    }

    Cancion obtenerCancion(int indice) const {
        if (indice < 0 || indice >= canciones.obtenerTamanio()) {
            // Devolver una canción vacía en caso de error
            return Cancion();
        }
        return canciones.obtener(indice);
    }

    int obtenerNumCanciones() const {
        return canciones.obtenerTamanio();
    }

    // Métodos para búsqueda de canciones
    Lista<int> buscarCancionesPorTitulo(const std::string& titulo) const {
        Lista<int> resultados;

        try {
            for (int i = 0; i < canciones.obtenerTamanio(); i++) {
                Cancion cancion = canciones.obtener(i);
                if (Busqueda::contieneCadenaInsensible(cancion.titulo, titulo)) {
                    resultados.agregar(i);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en búsqueda por título: " << e.what() << std::endl;
        }

        return resultados;
    }

    Lista<int> buscarCancionesPorArtista(const std::string& artista) const {
        Lista<int> resultados;

        try {
            for (int i = 0; i < canciones.obtenerTamanio(); i++) {
                Cancion cancion = canciones.obtener(i);
                if (Busqueda::contieneCadenaInsensible(cancion.artista, artista)) {
                    resultados.agregar(i);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error en búsqueda por artista: " << e.what() << std::endl;
        }

        return resultados;
    }

    // Métodos para ordenamiento
    void ordenarPorTitulo(bool ascendente = true) {
        try {
            Ordenamiento<Cancion>::ordenarPorCampo(canciones,
                [](const Cancion& a, const Cancion& b) -> bool {
                    return a.compararPorTitulo(b);
                }, ascendente);
        } catch (const std::exception& e) {
            std::cerr << "Error al ordenar por título: " << e.what() << std::endl;
        }
    }

    void ordenarPorArtista(bool ascendente = true) {
        try {
            Ordenamiento<Cancion>::ordenarPorCampo(canciones,
                [](const Cancion& a, const Cancion& b) -> bool {
                    return a.compararPorArtista(b);
                }, ascendente);
        } catch (const std::exception& e) {
            std::cerr << "Error al ordenar por artista: " << e.what() << std::endl;
        }
    }

    // Métodos para reproducción
    bool reproducir(int indice) {
        if (indice >= 0 && indice < canciones.obtenerTamanio()) {
            if (cancionActual >= 0) {
                historial.apilar(cancionActual);
            }
            cancionActual = indice;
            reproduciendo = true;
            return true;
        }
        return false;
    }

    bool pausar() {
        if (reproduciendo) {
            reproduciendo = false;
            return true;
        }
        return false;
    }

    bool reanudar() {
        if (cancionActual >= 0 && !reproduciendo) {
            reproduciendo = true;
            return true;
        }
        return false;
    }

    bool siguiente() {
        if (!colaReproduccion.estaVacia()) {
            if (cancionActual >= 0) {
                historial.apilar(cancionActual);
            }
            cancionActual = colaReproduccion.frente();
            colaReproduccion.desencolar();
            reproduciendo = true;
            return true;
        } else if (cancionActual >= 0 && cancionActual < canciones.obtenerTamanio() - 1) {
            historial.apilar(cancionActual);
            cancionActual++;
            reproduciendo = true;
            return true;
        }
        return false;
    }

    bool anterior() {
        if (!historial.estaVacia()) {
            if (cancionActual >= 0) {
                colaReproduccion.encolar(cancionActual);
            }
            cancionActual = historial.cima();
            historial.desapilar();
            reproduciendo = true;
            return true;
        }
        return false;
    }

    int obtenerCancionActual() const {
        return cancionActual;
    }

    bool estaReproduciendo() const {
        return reproduciendo;
    }

    // Métodos para la cola de reproducción
    void encolarCancion(int indice) {
        if (indice >= 0 && indice < canciones.obtenerTamanio()) {
            colaReproduccion.encolar(indice);
        }
    }

    bool desencolarCancion() {
        return colaReproduccion.desencolar();
    }

    int obtenerSiguienteEnCola() const {
        if (!colaReproduccion.estaVacia()) {
            return colaReproduccion.frente();
        }
        return -1;
    }

    int obtenerTamanioCola() const {
        return colaReproduccion.obtenerTamanio();
    }

    // Métodos para el historial
    int obtenerUltimaCancionHistorial() const {
        if (!historial.estaVacia()) {
            return historial.cima();
        }
        return -1;
    }

    int obtenerTamanioHistorial() const {
        return historial.obtenerTamanio();
    }

    void limpiarHistorial() {
        historial.vaciar();
    }

    // Métodos para listas de reproducción
    ListaReproduccion obtenerListaReproduccion(int indice) const {
        if (indice < 0 || indice >= listasReproduccion.obtenerTamanio()) {
            // Devolver una lista vacía en caso de error
            return ListaReproduccion();
        }
        return listasReproduccion.obtener(indice);
    }

    int obtenerNumListasReproduccion() const {
        return listasReproduccion.obtenerTamanio();
    }

    // Métodos para recomendaciones
    Lista<int> obtenerRecomendaciones(int indiceCancion) const {
        Lista<int> recomendaciones;

        try {
            if (indiceCancion < 0 || indiceCancion >= canciones.obtenerTamanio()) {
                return recomendaciones;
            }

            Cancion cancion = canciones.obtener(indiceCancion);

            // Obtener artistas similares
            Lista<std::string> artistasSimilares = grafoAfinidad.obtenerVecinosDFS(cancion.artista);

            // Buscar canciones con artistas similares
            for (int i = 0; i < canciones.obtenerTamanio(); i++) {
                if (i != indiceCancion) {
                    Cancion candidata = canciones.obtener(i);

                    // Verificar si el artista es similar
                    for (int j = 0; j < artistasSimilares.obtenerTamanio(); j++) {
                        if (candidata.artista == artistasSimilares.obtener(j)) {
                            recomendaciones.agregar(i);
                            break;
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al obtener recomendaciones: " << e.what() << std::endl;
        }

        return recomendaciones;
    }
};

// ==================== INTERFAZ DE USUARIO ====================

/**
 * @brief Interfaz de usuario para el reproductor de música
 */
class InterfazUsuario {
private:
    ReproductorMusica& reproductor;
    bool ejecutando;

    // Leer opción del usuario
    int leerOpcion() {
        int opcion;
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return opcion;
    }

    // Limpiar pantalla
    void limpiarPantalla() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    // Mostrar menú principal
    void mostrarMenuPrincipal() {
        try {
            std::cout << UTF8Util::formatearTitulo("REPRODUCTOR DE M" + UTF8Util::U_ACENTO() + "SICA") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar información de reproducción actual
            if (reproductor.obtenerCancionActual() != -1) {
                Cancion cancionActual = reproductor.obtenerCancion(reproductor.obtenerCancionActual());
                std::cout << "Reproduciendo: " << cancionActual.titulo << " - " << cancionActual.artista;
                if (reproductor.estaReproduciendo()) {
                    std::cout << " [▶]";
                } else {
                    std::cout << " [⏸]";
                }
                std::cout << std::endl;
                std::cout << UTF8Util::formatearLinea(80) << std::endl;
            }

            std::cout << "1. Ver biblioteca de canciones" << std::endl;
            std::cout << "2. Ver listas de reproducción" << std::endl;
            std::cout << "3. Buscar canciones" << std::endl;
            std::cout << "4. Reproducir canción" << std::endl;
            std::cout << "5. Control de reproducción" << std::endl;
            std::cout << "6. Ver cola de reproducción" << std::endl;
            std::cout << "7. Ver historial" << std::endl;
            std::cout << "8. Obtener recomendaciones" << std::endl;
            std::cout << "0. Salir" << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Ingrese una opción: ";
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar menú principal: " << e.what() << std::endl;
        }
    }

    // Mostrar biblioteca de canciones
    void mostrarBiblioteca() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("BIBLIOTECA DE CANCIONES") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (reproductor.obtenerNumCanciones() == 0) {
                std::cout << "La biblioteca está vacía." << std::endl;
                return;
            }

            std::cout << "Ordenar por:" << std::endl;
            std::cout << "1. Título" << std::endl;
            std::cout << "2. Artista" << std::endl;
            std::cout << "0. Volver sin ordenar" << std::endl;
            std::cout << "Ingrese una opción: ";

            int opcionOrden = leerOpcion();
            bool ascendente = true;

            if (opcionOrden >= 1 && opcionOrden <= 2) {
                std::cout << "Orden:" << std::endl;
                std::cout << "1. Ascendente" << std::endl;
                std::cout << "2. Descendente" << std::endl;
                std::cout << "Ingrese una opción: ";

                int opcionDireccion = leerOpcion();
                ascendente = (opcionDireccion != 2);

                switch (opcionOrden) {
                    case 1:
                        reproductor.ordenarPorTitulo(ascendente);
                        break;
                    case 2:
                        reproductor.ordenarPorArtista(ascendente);
                        break;
                }
            }

            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("BIBLIOTECA DE CANCIONES") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar encabezados de columnas
            std::cout << UTF8Util::formatearTexto("Índice", 8) << " | ";
            std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
            std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
            std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;

            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar canciones
            for (int i = 0; i < reproductor.obtenerNumCanciones(); i++) {
                Cancion cancion = reproductor.obtenerCancion(i);

                std::cout << UTF8Util::formatearTexto(std::to_string(i), 8) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar biblioteca: " << e.what() << std::endl;
        }
    }

    // Mostrar listas de reproducción
    void mostrarListasReproduccion() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("LISTAS DE REPRODUCCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (reproductor.obtenerNumListasReproduccion() == 0) {
                std::cout << "No hay listas de reproducción." << std::endl;
                return;
            }

            // Mostrar listas de reproducción
            for (int i = 0; i < reproductor.obtenerNumListasReproduccion(); i++) {
                ListaReproduccion lista = reproductor.obtenerListaReproduccion(i);

                std::cout << i << ". " << lista.nombre << " (" << lista.obtenerNumCanciones() << " canciones)" << std::endl;
            }

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Ingrese el índice de la lista para ver su contenido (o -1 para volver): ";

            int indice = leerOpcion();

            if (indice >= 0 && indice < reproductor.obtenerNumListasReproduccion()) {
                mostrarContenidoLista(indice);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar listas de reproducción: " << e.what() << std::endl;
        }
    }

    // Mostrar contenido de una lista de reproducción
    void mostrarContenidoLista(int indiceLista) {
        try {
            limpiarPantalla();
            ListaReproduccion lista = reproductor.obtenerListaReproduccion(indiceLista);

            std::cout << UTF8Util::formatearTitulo("LISTA: " + lista.nombre) << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (lista.descripcion != "") {
                std::cout << "Descripción: " << lista.descripcion << std::endl;
                std::cout << UTF8Util::formatearLinea(80) << std::endl;
            }

            if (lista.obtenerNumCanciones() == 0) {
                std::cout << "Esta lista está vacía." << std::endl;
                return;
            }

            // Mostrar encabezados de columnas
            std::cout << UTF8Util::formatearTexto("Nº", 4) << " | ";
            std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
            std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
            std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;

            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar canciones de la lista
            for (int i = 0; i < lista.canciones.obtenerTamanio(); i++) {
                int indiceCancion = lista.canciones.obtener(i);
                Cancion cancion = reproductor.obtenerCancion(indiceCancion);

                std::cout << UTF8Util::formatearTexto(std::to_string(i + 1), 4) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
            }

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Opciones:" << std::endl;
            std::cout << "1. Reproducir lista" << std::endl;
            std::cout << "0. Volver" << std::endl;
            std::cout << "Ingrese una opción: ";

            int opcion = leerOpcion();

            if (opcion == 1) {
                reproducirLista(indiceLista);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar contenido de lista: " << e.what() << std::endl;
        }
    }

    // Reproducir una lista de reproducción
    void reproducirLista(int indiceLista) {
        try {
            ListaReproduccion lista = reproductor.obtenerListaReproduccion(indiceLista);

            if (lista.obtenerNumCanciones() == 0) {
                std::cout << "Esta lista está vacía." << std::endl;
                return;
            }

            // Reproducir la primera canción
            int indiceCancion = lista.canciones.obtener(0);
            reproductor.reproducir(indiceCancion);

            // Encolar el resto de canciones
            for (int i = 1; i < lista.canciones.obtenerTamanio(); i++) {
                indiceCancion = lista.canciones.obtener(i);
                reproductor.encolarCancion(indiceCancion);
            }

            std::cout << "Reproduciendo lista: " << lista.nombre << std::endl;
            mostrarReproduccionActual();
        } catch (const std::exception& e) {
            std::cerr << "Error al reproducir lista: " << e.what() << std::endl;
        }
    }

    // Buscar canciones
    void buscarCanciones() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("BUSCAR CANCIONES") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            std::cout << "Buscar por:" << std::endl;
            std::cout << "1. Título" << std::endl;
            std::cout << "2. Artista" << std::endl;
            std::cout << "0. Volver" << std::endl;
            std::cout << "Ingrese una opción: ";

            int opcion = leerOpcion();

            if (opcion >= 1 && opcion <= 2) {
                std::cout << "Ingrese el término de búsqueda: ";
                std::string termino;
                std::getline(std::cin, termino);

                Lista<int> resultados;

                switch (opcion) {
                    case 1:
                        resultados = reproductor.buscarCancionesPorTitulo(termino);
                        break;
                    case 2:
                        resultados = reproductor.buscarCancionesPorArtista(termino);
                        break;
                }

                mostrarResultadosBusqueda(resultados);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al buscar canciones: " << e.what() << std::endl;
        }
    }

    // Mostrar resultados de búsqueda
    void mostrarResultadosBusqueda(const Lista<int>& resultados) {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("RESULTADOS DE B" + UTF8Util::U_ACENTO() + "SQUEDA") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (resultados.obtenerTamanio() == 0) {
                std::cout << "No se encontraron resultados." << std::endl;
                return;
            }

            std::cout << "Se encontraron " << resultados.obtenerTamanio() << " resultados:" << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar encabezados de columnas
            std::cout << UTF8Util::formatearTexto("Índice", 8) << " | ";
            std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
            std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
            std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;

            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar resultados
            for (int i = 0; i < resultados.obtenerTamanio(); i++) {
                int indice = resultados.obtener(i);
                Cancion cancion = reproductor.obtenerCancion(indice);

                std::cout << UTF8Util::formatearTexto(std::to_string(indice), 8) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
            }

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Opciones:" << std::endl;
            std::cout << "1. Reproducir una canción" << std::endl;
            std::cout << "2. Agregar una canción a la cola" << std::endl;
            std::cout << "0. Volver" << std::endl;
            std::cout << "Ingrese una opción: ";

            int opcion = leerOpcion();

            if (opcion == 1 || opcion == 2) {
                std::cout << "Ingrese el índice de la canción: ";
                int indice = leerOpcion();

                if (indice >= 0 && indice < reproductor.obtenerNumCanciones()) {
                    if (opcion == 1) {
                        reproductor.reproducir(indice);
                        std::cout << "Reproduciendo canción." << std::endl;
                    } else {
                        reproductor.encolarCancion(indice);
                        std::cout << "Canción agregada a la cola." << std::endl;
                    }
                } else {
                    std::cout << "Índice inválido." << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar resultados de búsqueda: " << e.what() << std::endl;
        }
    }

    // Reproducir canción
    void reproducirCancion() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("REPRODUCIR CANCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar canciones de la biblioteca
            mostrarBiblioteca();

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Ingrese el índice de la canción a reproducir: ";

            int indice = leerOpcion();

            if (indice >= 0 && indice < reproductor.obtenerNumCanciones()) {
                reproductor.reproducir(indice);
                std::cout << "Reproduciendo canción." << std::endl;
                mostrarReproduccionActual();
            } else {
                std::cout << "Índice inválido." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al reproducir canción: " << e.what() << std::endl;
        }
    }

    // Mostrar reproducción actual
    void mostrarReproduccionActual() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("REPRODUCCI" + UTF8Util::O_ACENTO() + "N ACTUAL") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (reproductor.obtenerCancionActual() == -1) {
                std::cout << "No hay ninguna canción reproduciéndose." << std::endl;
                return;
            }

            Cancion cancion = reproductor.obtenerCancion(reproductor.obtenerCancionActual());

            std::cout << "Título: " << cancion.titulo << std::endl;
            std::cout << "Artista: " << cancion.artista << std::endl;
            std::cout << "Álbum: " << cancion.album << std::endl;
            std::cout << "Año: " << cancion.anio << std::endl;
            std::cout << "Duración: " << cancion.obtenerDuracionFormateada() << std::endl;

            std::cout << "Géneros: ";
            for (int i = 0; i < cancion.generos.obtenerTamanio(); i++) {
                std::cout << cancion.generos.obtener(i);
                if (i < cancion.generos.obtenerTamanio() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;

            std::cout << "Estado: " << (reproductor.estaReproduciendo() ? "Reproduciendo" : "Pausado") << std::endl;

            // Simulación de barra de progreso
            int duracionTotal = cancion.duracion;
            // Limitar el progreso para evitar desbordamientos
            int progreso = duracionTotal > 0 ? rand() % duracionTotal : 0;
            int porcentaje = duracionTotal > 0 ? (progreso * 100) / duracionTotal : 0;

            std::cout << "\nProgreso: [";
            // Limitar el tamaño de la barra de progreso
            const int maxBarLength = 50;
            for (int i = 0; i < maxBarLength; i++) {
                if (i < (porcentaje * maxBarLength / 100)) {
                    std::cout << "=";
                } else if (i == (porcentaje * maxBarLength / 100)) {
                    std::cout << ">";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << "] " << porcentaje << "%" << std::endl;

            int minutos = progreso / 60;
            int segundos = progreso % 60;
            int minutosTotal = duracionTotal / 60;
            int segundosTotal = duracionTotal % 60;

            printf("%02d:%02d / %02d:%02d\n", minutos, segundos, minutosTotal, segundosTotal);

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Controles:" << std::endl;
            std::cout << "1. " << (reproductor.estaReproduciendo() ? "Pausar" : "Reanudar") << std::endl;
            std::cout << "2. Anterior" << std::endl;
            std::cout << "3. Siguiente" << std::endl;
            std::cout << "0. Volver" << std::endl;
            std::cout << "Ingrese una opción: ";

            int opcion = leerOpcion();

            switch (opcion) {
                case 1:
                    if (reproductor.estaReproduciendo()) {
                        reproductor.pausar();
                        std::cout << "Reproducción pausada." << std::endl;
                    } else {
                        reproductor.reanudar();
                        std::cout << "Reproducción reanudada." << std::endl;
                    }
                    mostrarReproduccionActual();
                    break;
                case 2:
                    if (reproductor.anterior()) {
                        std::cout << "Reproduciendo canción anterior." << std::endl;
                    } else {
                        std::cout << "No hay canciones anteriores en el historial." << std::endl;
                    }
                    mostrarReproduccionActual();
                    break;
                case 3:
                    if (reproductor.siguiente()) {
                        std::cout << "Reproduciendo siguiente canción." << std::endl;
                    } else {
                        std::cout << "No hay más canciones en la cola." << std::endl;
                    }
                    mostrarReproduccionActual();
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar reproducción actual: " << e.what() << std::endl;
        }
    }

    // Mostrar cola de reproducción
    void mostrarColaReproduccion() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("COLA DE REPRODUCCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (reproductor.obtenerTamanioCola() == 0) {
                std::cout << "La cola de reproducción está vacía." << std::endl;
                return;
            }

            std::cout << "Próxima canción:" << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            int siguienteEnCola = reproductor.obtenerSiguienteEnCola();
            if (siguienteEnCola != -1) {
                Cancion cancion = reproductor.obtenerCancion(siguienteEnCola);

                std::cout << "Título: " << cancion.titulo << std::endl;
                std::cout << "Artista: " << cancion.artista << std::endl;
                std::cout << "Álbum: " << cancion.album << std::endl;
            }

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Total de canciones en cola: " << reproductor.obtenerTamanioCola() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar cola de reproducción: " << e.what() << std::endl;
        }
    }

    // Mostrar historial
    void mostrarHistorial() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("HISTORIAL DE REPRODUCCI" + UTF8Util::O_ACENTO() + "N") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (reproductor.obtenerTamanioHistorial() == 0) {
                std::cout << "El historial está vacío." << std::endl;
                return;
            }

            std::cout << "Última canción reproducida:" << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            int ultimaCancion = reproductor.obtenerUltimaCancionHistorial();
            if (ultimaCancion != -1) {
                Cancion cancion = reproductor.obtenerCancion(ultimaCancion);

                std::cout << "Título: " << cancion.titulo << std::endl;
                std::cout << "Artista: " << cancion.artista << std::endl;
                std::cout << "Álbum: " << cancion.album << std::endl;
            }

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Total de canciones en historial: " << reproductor.obtenerTamanioHistorial() << std::endl;

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Opciones:" << std::endl;
            std::cout << "1. Limpiar historial" << std::endl;
            std::cout << "2. Volver a la última canción" << std::endl;
            std::cout << "0. Volver" << std::endl;
            std::cout << "Ingrese una opción: ";

            int opcion = leerOpcion();

            switch (opcion) {
                case 1:
                    reproductor.limpiarHistorial();
                    std::cout << "Historial limpiado." << std::endl;
                    break;
                case 2:
                    if (reproductor.anterior()) {
                        std::cout << "Reproduciendo canción anterior." << std::endl;
                        mostrarReproduccionActual();
                    } else {
                        std::cout << "No hay canciones anteriores en el historial." << std::endl;
                    }
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar historial: " << e.what() << std::endl;
        }
    }

    // Mostrar recomendaciones
    void mostrarRecomendaciones() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("RECOMENDACIONES") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            if (reproductor.obtenerCancionActual() == -1) {
                std::cout << "No hay ninguna canción reproduciéndose. Reproduzca una canción para obtener recomendaciones." << std::endl;
                return;
            }

            Cancion cancionActual = reproductor.obtenerCancion(reproductor.obtenerCancionActual());
            std::cout << "Basado en: " << cancionActual.titulo << " - " << cancionActual.artista << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            Lista<int> recomendaciones = reproductor.obtenerRecomendaciones(reproductor.obtenerCancionActual());

            if (recomendaciones.obtenerTamanio() == 0) {
                std::cout << "No se encontraron recomendaciones." << std::endl;
                return;
            }

            std::cout << "Canciones recomendadas:" << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar encabezados de columnas
            std::cout << UTF8Util::formatearTexto("Índice", 8) << " | ";
            std::cout << UTF8Util::formatearTexto("Título", 30) << " | ";
            std::cout << UTF8Util::formatearTexto("Artista", 20) << " | ";
            std::cout << UTF8Util::formatearTexto("Álbum", 20) << std::endl;

            std::cout << UTF8Util::formatearLinea(80) << std::endl;

            // Mostrar recomendaciones
            for (int i = 0; i < recomendaciones.obtenerTamanio(); i++) {
                int indice = recomendaciones.obtener(i);
                Cancion cancion = reproductor.obtenerCancion(indice);

                std::cout << UTF8Util::formatearTexto(std::to_string(indice), 8) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.titulo, 30) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.artista, 20) << " | ";
                std::cout << UTF8Util::formatearTexto(cancion.album, 20) << std::endl;
            }

            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Opciones:" << std::endl;
            std::cout << "1. Reproducir una recomendación" << std::endl;
            std::cout << "2. Agregar todas las recomendaciones a la cola" << std::endl;
            std::cout << "0. Volver" << std::endl;
            std::cout << "Ingrese una opción: ";

            int opcion = leerOpcion();
            int indice; // Declarar la variable fuera del switch

            switch (opcion) {
                case 1:
                    std::cout << "Ingrese el índice de la canción a reproducir: ";
                    indice = leerOpcion(); // Usar la variable ya declarada

                    if (indice >= 0 && indice < reproductor.obtenerNumCanciones()) {
                        reproductor.reproducir(indice);
                        std::cout << "Reproduciendo canción." << std::endl;
                        mostrarReproduccionActual();
                    } else {
                        std::cout << "Índice inválido." << std::endl;
                    }
                    break;
                case 2:
                    for (int i = 0; i < recomendaciones.obtenerTamanio(); i++) {
                        indice = recomendaciones.obtener(i);
                        reproductor.encolarCancion(indice);
                    }
                    std::cout << "Recomendaciones agregadas a la cola." << std::endl;
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al mostrar recomendaciones: " << e.what() << std::endl;
        }
    }

public:
    // Constructor
    InterfazUsuario(ReproductorMusica& _reproductor)
        : reproductor(_reproductor), ejecutando(true) {}

    // Iniciar la interfaz
    void iniciar() {
        try {
            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("REPRODUCTOR DE M" + UTF8Util::U_ACENTO() + "SICA") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Bienvenido al reproductor de música didáctico." << std::endl;
            std::cout << "Este programa utiliza estructuras de datos como listas, pilas, colas y grafos." << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();

            while (ejecutando) {
                limpiarPantalla();
                mostrarMenuPrincipal();
                int opcion = leerOpcion();

                switch (opcion) {
                    case 1:
                        mostrarBiblioteca();
                        break;
                    case 2:
                        mostrarListasReproduccion();
                        break;
                    case 3:
                        buscarCanciones();
                        break;
                    case 4:
                        reproducirCancion();
                        break;
                    case 5:
                        mostrarReproduccionActual();
                        break;
                    case 6:
                        mostrarColaReproduccion();
                        break;
                    case 7:
                        mostrarHistorial();
                        break;
                    case 8:
                        mostrarRecomendaciones();
                        break;
                    case 0:
                        ejecutando = false;
                        break;
                    default:
                        std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                        break;
                }

                if (ejecutando) {
                    std::cout << "\nPresione Enter para continuar...";
                    std::cin.get();
                }
            }

            limpiarPantalla();
            std::cout << UTF8Util::formatearTitulo("GRACIAS POR USAR EL REPRODUCTOR DE M" + UTF8Util::U_ACENTO() + "SICA") << std::endl;
            std::cout << UTF8Util::formatearLinea(80) << std::endl;
            std::cout << "Hasta pronto!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error en la interfaz de usuario: " << e.what() << std::endl;
        }
    }
};

// ==================== FUNCIÓN PRINCIPAL ====================

int main() {
    try {
        // Inicializar generador de números aleatorios
        srand(static_cast<unsigned int>(time(nullptr)));

        // Crear el reproductor de música
        ReproductorMusica reproductor;

        // Crear la interfaz de usuario
        InterfazUsuario interfaz(reproductor);

        // Iniciar la interfaz
        interfaz.iniciar();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error fatal: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Error desconocido" << std::endl;
        return 2;
    }
}
