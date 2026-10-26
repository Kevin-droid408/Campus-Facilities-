#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <iostream>

// ============================================================
// Graph - Campus Navigation
// Vertices = locations, Edges = pathways with distance
// ============================================================

struct Edge {
    int to;
    int weight;
    Edge(int t = -1, int w = 0) : to(t), weight(w) {}
};

class Graph {
private:
    std::vector<std::string> vertices;
    std::vector<std::vector<Edge>> adj;
    int numVertices;

    int findIndex(const std::string& name) const;
    void DFSUtil(int v, std::vector<bool>& visited) const;

public:
    Graph();
    ~Graph() = default;

    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    void addVertex(const std::string& name);
    void addEdge(const std::string& from, const std::string& to, int weight);

    void BFS(const std::string& start) const;
    void DFS(const std::string& start) const;
    void Dijkstra(const std::string& start, const std::string& end) const;

    bool isReachable(const std::string& from, const std::string& to) const;
    void connectedComponents() const;

    void display() const;
    int getNumVertices() const { return numVertices; }
};

#endif
