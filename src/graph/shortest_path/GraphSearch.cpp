//
// Created by laeri on 1/27/17.
//

#include "GraphSearch.h"

void GraphSearch::init_single_src(Graph &graph, graph::Vertex &src) {
    float max_value = std::numeric_limits<float>::max();
    for (auto &v: graph.get_vertices()) {
        v->distance = max_value;
        v->pred = nullptr;
    }
    src.distance = 0;
}

void GraphSearch::relax(graph::Vertex &u, graph::Vertex &v, float weight) {
    if (v.distance > u.distance + weight) {
        v.distance = u.distance + weight;
        v.pred = &u;
    }
}