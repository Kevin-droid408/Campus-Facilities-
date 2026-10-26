#include "Graph.h"
#include <queue>
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

Graph::Graph() : numVertices(0) {}

int Graph::findIndex(const string& name) const {
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == name) return i;
    }
    return -1;
}

void Graph::addVertex(const string& name) {
    if (findIndex(name) != -1) {
        cout << "Location \"" << name << "\" already exists.\n";
        return;
    }
    vertices.push_back(name);
    adj.emplace_back();
    numVertices++;
    cout << "Location \"" << name << "\" added.\n";
}

void Graph::addEdge(const string& from, const string& to, int weight) {
    int u = findIndex(from);
    int v = findIndex(to);
    if (u == -1 || v == -1) {
        cout << "Error: One or both locations not found.\n";
        return;
    }
    adj[u].push_back(Edge(v, weight));
    adj[v].push_back(Edge(u, weight));
    cout << "Pathway added: " << from << " <--> " << to << " (" << weight << " m)\n";
}

void Graph::BFS(const string& start) const {
    int s = findIndex(start);
    if (s == -1) {
        cout << "Start location not found.\n";
        return;
    }
    cout << "\n--- BFS starting from \"" << start << "\" ---\n";
    vector<bool> visited(numVertices, false);
    queue<int> q;
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << vertices[u] << "  ";
        for (const Edge& e : adj[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }
    cout << "\n";
}

void Graph::DFSUtil(int v, vector<bool>& visited) const {
    visited[v] = true;
    cout << vertices[v] << "  ";
    for (const Edge& e : adj[v]) {
        if (!visited[e.to]) DFSUtil(e.to, visited);
    }
}

void Graph::DFS(const string& start) const {
    int s = findIndex(start);
    if (s == -1) {
        cout << "Start location not found.\n";
        return;
    }
    cout << "\n--- DFS starting from \"" << start << "\" ---\n";
    vector<bool> visited(numVertices, false);
    DFSUtil(s, visited);
    cout << "\n";
}

void Graph::Dijkstra(const string& start, const string& end) const {
    int src = findIndex(start);
    int dest = findIndex(end);
    if (src == -1 || dest == -1) {
        cout << "One or both locations not found.\n";
        return;
    }
    vector<int> dist(numVertices, INT_MAX);
    vector<int> prev(numVertices, -1);
    vector<bool> used(numVertices, false);
    dist[src] = 0;

    for (int count = 0; count < numVertices; count++) {
        int u = -1, minDist = INT_MAX;
        for (int i = 0; i < numVertices; i++) {
            if (!used[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        used[u] = true;
        for (const Edge& e : adj[u]) {
            int v = e.to;
            if (!used[v] && dist[u] != INT_MAX && dist[u] + e.weight < dist[v]) {
                dist[v] = dist[u] + e.weight;
                prev[v] = u;
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "No path exists from " << start << " to " << end << ".\n";
        return;
    }

    vector<int> path;
    for (int at = dest; at != -1; at = prev[at]) path.push_back(at);
    reverse(path.begin(), path.end());

    cout << "\n===== Shortest Path =====\n";
    cout << "From : " << start << "\nTo   : " << end << "\nPath : ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << vertices[path[i]];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\nTotal distance: " << dist[dest] << " metres\n";
    cout << "=========================\n";
}

bool Graph::isReachable(const string& from, const string& to) const {
    int s = findIndex(from);
    int d = findIndex(to);
    if (s == -1 || d == -1) return false;
    vector<bool> visited(numVertices, false);
    queue<int> q;
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == d) return true;
        for (const Edge& e : adj[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }
    return false;
}

void Graph::connectedComponents() const {
    vector<bool> visited(numVertices, false);
    int componentCount = 0;
    cout << "\n===== Connected Components =====\n";
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            componentCount++;
            cout << "Component " << componentCount << ": ";
            DFSUtil(i, visited);
            cout << "\n";
        }
    }
    cout << "Total components: " << componentCount << "\n";
    cout << "================================\n";
}

void Graph::display() const {
    cout << "\n========== Campus Map (Graph) ==========\n";
    if (numVertices == 0) {
        cout << "Graph is empty.\n";
        return;
    }
    for (int i = 0; i < numVertices; i++) {
        cout << vertices[i] << " --> ";
        if (adj[i].empty()) cout << "(no connections)";
        else {
            for (size_t j = 0; j < adj[i].size(); j++) {
                cout << vertices[adj[i][j].to] << "(" << adj[i][j].weight << "m)";
                if (j + 1 < adj[i].size()) cout << ", ";
            }
        }
        cout << "\n";
    }
    cout << "========================================\n";
}
