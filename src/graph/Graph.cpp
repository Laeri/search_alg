//
// Created by laeri on 1/23/17.
//

#include <algorithm>
#include "Graph.h"

Graph::Graph() {
}

Graph::~Graph() {
    for (auto &vertex: vertices) {
        delete vertex;
    }
}

void Graph::add(graph::Vertex *vertex) {
    vertices.push_back(vertex);
    adj.push_back(std::vector<std::pair<int, float>>());
}

void Graph::bi_connect(graph::Vertex *va, graph::Vertex *vb, float weight) {
    int v1 = index_of(va);
    int v2 = index_of(vb);
    bool already_connected = false;
    for (auto a: adj[v1]) {
        if (a.first == v2) already_connected = true;
    }
    if (!already_connected)
        adj[v1].push_back(std::make_pair(v2, weight));
    already_connected = false;

    for (auto a: adj[v2]) {
        if (a.first == v1) already_connected = true;
    }
    if (!already_connected)
        adj[v2].push_back(std::make_pair(v1, weight));
}

bool Graph::connected(graph::Vertex &va, graph::Vertex &vb) {
    auto it_a = std::find(vertices.begin(), vertices.end(), &va);
    auto it_b = std::find(vertices.begin(), vertices.end(), &vb);
    if (it_a == vertices.end() || it_b == vertices.end()) {
        return false;
    } else {
        int v1 = std::distance(vertices.begin(), it_a);
        int v2 = std::distance(vertices.begin(), it_b);
        for (auto a: adj[v1]) {
            if (a.first == v2) {
                return true;
            }
        }
        for (auto a: adj[v2]) {
            if (a.first == v1) {
                return true;
            }
        }

    }

    return false;
}

int Graph::index_of(graph::Vertex *vertex) {
    auto it = std::find(vertices.begin(), vertices.end(), vertex);
    /*
    if(it_a == vertices.end()){
        return -1;
    }*/
    return std::distance(vertices.begin(), it);
}

VertexList& Graph::get_vertices() {
    return vertices;
}

ADJ_V& Graph::adj_of(graph::Vertex *vertex) {
    int i = 0;
    for (auto v:vertices) {
        if (v == vertex) {
            return adj[i];
        }
        i++;
    }
    throw std::runtime_error("Vertex is not part of graph.");
}

Adjacency& Graph::get_adjacencies() {
    return adj;
}

void Graph::remove_adj_to(graph::Vertex *vertex) {
    int v = index_of(vertex);
    for (auto &edges: adj) {
        std::vector<std::pair<int, float>>::iterator it = edges.begin();
        while((it != edges.end())){
            if(it->first == v){
                it = edges.erase(it);
                //edges.erase(it++);  // alternatively,
            } else {
                ++it;
            }
        }
    }
}