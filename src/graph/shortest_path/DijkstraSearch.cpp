//
// Created by laeri on 1/27/17.
//

#include <thread>
#include "DijkstraSearch.h"

void DijkstraSearch::search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    init_single_src(graph, src);
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
            if (v->distance <= min_dist) {
                min_pos = pos;
                min_dist = v->distance;
            }
            pos++;
        }
        graph::Vertex *u = Q[min_pos];
        if((u->type != graph::Type::start) && (u->type != graph::Type::end) && (u->type != graph::Type::occupied)) {
            u->color = sf::Color::White;
            u->type = graph::Type::being_processed;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        Q.erase(Q.begin() + min_pos);

        S.push_back(u);
        for (std::pair<int, float> pair: graph.adj_of(u)) {
            graph::Vertex *v = graph.get_vertices()[pair.first];
            float weight = pair.second;
            relax(*u, *v, weight);
        }

    }
}

