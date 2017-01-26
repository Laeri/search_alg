//
// Created by laeri on 1/26/17.
//

#ifndef SEARCH_ALG_GREEDYBFS_H
#define SEARCH_ALG_GREEDYBFS_H

#include "../Graph.h"

namespace best_first {
    void best_first_search(Graph &graph, graph::Vertex &src, graph::Vertex &goal);
    struct compare {
        bool operator()(const graph::Vertex *u, const graph::Vertex *v) {
            return u->distance > v->distance;
        }
    };
}

#endif //SEARCH_ALG_GREEDYBFS_H
