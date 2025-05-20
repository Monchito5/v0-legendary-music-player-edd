#ifndef GRAPH_H
#define GRAPH_H

#include "../models/song.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

// Nodo de adyacencia
struct AdjNode {
    int songId;
    float weight;
    AdjNode* next;
    
    AdjNode(int id, float w) : songId(id), weight(w), next(nullptr) {}
};

class Graph {
private:
    std::unordered_map<int, AdjNode*> adjList;
    int numEdges;
    
    // Métodos auxiliares
    void destroyList(AdjNode* head);

public:
    // Constructor y destructor
    Graph();
    ~Graph();
    
    // Métodos básicos
    void addVertex(int songId);
    bool hasVertex(int songId) const;
    void addEdge(int from, int to, float weight);
    bool removeEdge(int from, int to);
    bool removeVertex(int songId);
    
    // Recorridos
    std::vector<int> breadthFirstSearch(int startId);
    std::vector<int> depthFirstSearch(int startId);
    
    // Recomendaciones
    std::vector<std::pair<int, float>> getRecommendations(int songId, int limit);
    
    // Getters
    int getNumVertices() const { return adjList.size(); }
    int getNumEdges() const { return numEdges; }
    
    // Obtener vecinos
    std::vector<std::pair<int, float>> getNeighbors(int songId);
};

#endif // GRAPH_H
