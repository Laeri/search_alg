//
// Created by laeri on 1/24/17.
//

#include "../Graph.h"

#ifndef SEARCH_ALG_DIJKSTRA_H
#define SEARCH_ALG_DIJKSTRA_H

#endif //SEARCH_ALG_DIJKSTRA_H

namespace Dijkstra {
    struct compare {
        bool operator()(const graph::Vertex *u, const graph::Vertex *v) {
            return u->distance > v->distance;
        }
    };

    void dijkstra(Graph &graph, graph::Vertex &src);

    void relax(graph::Vertex *u, graph::Vertex *v, float weight);

    void init_single_source(Graph &graph, graph::Vertex &src);
}