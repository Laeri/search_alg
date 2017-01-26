//
// Created by laeri on 1/26/17.
//
#include "AStar.h"
#include "Dijkstra.h"

void a_star::a_star_search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    Dijkstra::init_single_source(graph, src);
    std::vector<graph::Vertex *> open;
    std::vector<graph::Vertex *> closed;
    open.push_back(&src);
    graph::Vertex *current;
    while (!open.empty()) {
        graph::Vertex *nearest = nullptr;
        float min_dist = std::numeric_limits<float>::max();
        for (auto &el: open) {
            if (el->distance < min_dist) {
                nearest = el;
                min_dist = el->distance;
            }
        }
        current = nearest;

        if(current == &goal){
            break;
        }

        for(auto &nex: graph.adj_of(current)){
            float cost_current = current->distance;

            // calculate cost

        }

    }
}
