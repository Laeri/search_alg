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

void Graph::add(Vertex *vertex) {
    vertices.push_back(vertex);
    adj.push_back(std::vector<std::pair<int, int>>());
}

void Graph::bi_connect(Vertex *va, Vertex *vb, int weight) {
    int v1 = index_of(va);
    int v2 = index_of(vb);
    adj[v1].push_back(std::make_pair(v2, weight));
    adj[v2].push_back(std::make_pair(v1, weight));
}

bool Graph::connected(Vertex &va, Vertex &vb) {
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

int Graph::index_of(Vertex *vertex) {
    auto it = std::find(vertices.begin(), vertices.end(), vertex);
    /*
    if(it_a == vertices.end()){
        return -1;
    }*/
    return std::distance(vertices.begin(), it);
}