//
// Created by laeri on 1/24/17.
//


#include <queue>
#include <set>
#include <thread>
#include "Dijkstra.h"


void Dijkstra::dijkstra(Graph &graph, graph::Vertex &src) {
    Dijkstra::init_single_source(graph, src);
    std::vector<graph::Vertex *> S;
    std::vector<graph::Vertex *> Q;

    for (graph::Vertex *vertex: graph.get_vertices()) {
        Q.push_back(vertex);
    }
    while (!Q.empty()) {

        float min_dist = std::numeric_limits<float>::max();
        int pos = 0;
        int min_pos = -1;
        for (auto &v: Q) {
            if (v->distance < min_dist) {
                min_pos = pos;
                min_dist = v->distance;
            }
            pos++;
        }
        graph::Vertex *u = Q[min_pos];
        u->color = sf::Color::White;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        Q.erase(Q.begin() + min_pos);

        S.push_back(u);
        for (std::pair<int, float> pair: graph.adj_of(u)) {
            graph::Vertex *v = graph.get_vertices()[pair.first];
            float weight = pair.second;
            relax(u, v, weight);
        }

    }
}

void Dijkstra::init_single_source(Graph &graph, graph::Vertex &src) {
    for (auto vertex: graph.get_vertices()) {
        vertex->distance = std::numeric_limits<float>::max();
        vertex->pred = nullptr;
    }
    src.distance = 0;
}


void Dijkstra::relax(graph::Vertex *u, graph::Vertex *v, float weight) {
    if (v->distance > u->distance + weight) {
        v->distance = u->distance + weight;
        v->pred = u;
    }
}