#include "graph.h"
#include <stack>
#include <algorithm>

Graph::Graph() : numEdges(0) {}

Graph::~Graph() {
    for (auto& pair : adjList) {
        destroyList(pair.second);
    }
}

void Graph::destroyList(AdjNode* head) {
    while (head) {
        AdjNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void Graph::addVertex(int songId) {
    if (!hasVertex(songId)) {
        adjList[songId] = nullptr;
    }
}

bool Graph::hasVertex(int songId) const {
    return adjList.find(songId) != adjList.end();
}

void Graph::addEdge(int from, int to, float weight) {
    // Asegurarse de que ambos vértices existan
    addVertex(from);
    addVertex(to);
    
    // Verificar si la arista ya existe
    AdjNode* current = adjList[from];
    while (current) {
        if (current->songId == to) {
            // Actualizar el peso si la arista ya existe
            current->weight = weight;
            return;
        }
        current = current->next;
    }
    
    // Crear un nuevo nodo de adyacencia
    AdjNode* newNode = new AdjNode(to, weight);
    
    // Insertar al principio de la lista
    newNode->next = adjList[from];
    adjList[from] = newNode;
    
    numEdges++;
}

bool Graph::removeEdge(int from, int to) {
    if (!hasVertex(from)) {
        return false;
    }
    
    AdjNode* current = adjList[from];
    AdjNode* prev = nullptr;
    
    while (current) {
        if (current->songId == to) {
            // Eliminar el nodo
            if (prev) {
                prev->next = current->next;
            } else {
                adjList[from] = current->next;
            }
            
            delete current;
            numEdges--;
            return true;
        }
        
        prev = current;
        current = current->next;
    }
    
    return false;
}

bool Graph::removeVertex(int songId) {
    if (!hasVertex(songId)) {
        return false;
    }
    
    // Eliminar todas las aristas que apuntan a este vértice
    for (auto& pair : adjList) {
        if (pair.first != songId) {
            removeEdge(pair.first, songId);
        }
    }
    
    // Eliminar la lista de adyacencia del vértice
    destroyList(adjList[songId]);
    
    // Eliminar el vértice del mapa
    adjList.erase(songId);
    
    return true;
}

std::vector<int> Graph::breadthFirstSearch(int startId) {
    std::vector<int> result;
    
    if (!hasVertex(startId)) {
        return result;
    }
    
    std::unordered_set<int> visited;
    std::queue<int> queue;
    
    visited.insert(startId);
    queue.push(startId);
    
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        result.push_back(current);
        
        AdjNode* neighbor = adjList[current];
        while (neighbor) {
            if (visited.find(neighbor->songId) == visited.end()) {
                visited.insert(neighbor->songId);
                queue.push(neighbor->songId);
            }
            neighbor = neighbor->next;
        }
    }
    
    return result;
}

std::vector<int> Graph::depthFirstSearch(int startId) {
    std::vector<int> result;
    
    if (!hasVertex(startId)) {
        return result;
    }
    
    std::unordered_set<int> visited;
    std::stack<int> stack;
    
    stack.push(startId);
    
    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        
        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            result.push_back(current);
            
            AdjNode* neighbor = adjList[current];
            while (neighbor) {
                if (visited.find(neighbor->songId) == visited.end()) {
                    stack.push(neighbor->songId);
                }
                neighbor = neighbor->next;
            }
        }
    }
    
    return result;
}

std::vector<std::pair<int, float>> Graph::getRecommendations(int songId, int limit) {
    std::vector<std::pair<int, float>> recommendations;
    
    if (!hasVertex(songId)) {
        return recommendations;
    }
    
    // Obtener vecinos directos con sus pesos
    AdjNode* neighbor = adjList[songId];
    while (neighbor) {
        recommendations.push_back(std::make_pair(neighbor->songId, neighbor->weight));
        neighbor = neighbor->next;
    }
    
    // Ordenar por peso (mayor a menor)
    std::sort(recommendations.begin(), recommendations.end(),
              [](const std::pair<int, float>& a, const std::pair<int, float>& b) {
                  return a.second > b.second;
              });
    
    // Limitar el número de recomendaciones
    if (recommendations.size() > limit) {
        recommendations.resize(limit);
    }
    
    return recommendations;
}

std::vector<std::pair<int, float>> Graph::getNeighbors(int songId) {
    std::vector<std::pair<int, float>> neighbors;
    
    if (!hasVertex(songId)) {
        return neighbors;
    }
    
    AdjNode* current = adjList[songId];
    while (current) {
        neighbors.push_back(std::make_pair(current->songId, current->weight));
        current = current->next;
    }
    
    return neighbors;
}
