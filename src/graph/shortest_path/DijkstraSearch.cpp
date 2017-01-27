//
// Created by laeri on 1/27/17.
//

#include <thread>
#include "DijkstraSearch.h"
#include "GBestFirstSearch.h"

void DijkstraSearch::search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    init_single_src(graph, src);
    std::vector<graph::Vertex *> Q;

    for (graph::Vertex *vertex: graph.get_vertices()) {
        Q.push_back(vertex);
    }
    std::sort(Q.begin(), Q.end(), sort_vector());
    while (!Q.empty()) {
        graph::Vertex *u = Q[0];
        callback(Event::Current, u);
        Q.erase(Q.begin());

        for (std::pair<int, float> pair: graph.adj_of(u)) {
            graph::Vertex *v = graph.get_vertices()[pair.first];
            float weight = pair.second;
            bool resort_queue = v->distance > u->distance + weight;
            relax(*u, *v, weight);
            if (resort_queue) std::sort(Q.begin(), Q.end(), sort_vector());
        }

    }
}

