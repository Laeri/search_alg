//
// Created by laeri on 1/27/17.
//

#include <map>
#include <thread>
#include <mutex>
#include "AStarSearch.h"

AStarSearch::AStarSearch(Heuristic *heuristic) : heuristic(heuristic) {}

AStarSearch::~AStarSearch() {
    delete heuristic;
}

void AStarSearch::search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    init_single_src(graph, src);
    std::vector<graph::Vertex *> open;
    std::vector<graph::Vertex *> closed;

    std::map<graph::Vertex *, float> g_cost;
    // f cost is stored in vertex distance member variable

    open.push_back(&src);
    graph::Vertex *current;
    g_cost[&src] = 0;

    while (!open.empty()) {
        current = open[0];
        open.erase(open.begin());
        closed.push_back(current);

        callback(Event::Current, current);
        if (current == &goal) {
            break;
        }


        for (auto &pair: graph.adj_of(current)) {
            graph::Vertex *node = graph.get_vertices()[pair.first];
            if (std::find(closed.begin(), closed.end(), node) == closed.end()) { // not in closed
                float g = g_cost[current] + pair.second;
                float h = heuristic->apply(*node, goal);
                float f = g + h;
                if (std::find(open.begin(), open.end(), node) == open.end()) { // not yet in open, so add it
                    node->pred = current;
                    open.push_back(node);
                    node->distance = f;
                    g_cost[node] = g;
                    callback(Event::Relax, node);
                    std::sort(open.begin(), open.end(), compare());
                } else { // check if g cost is lower than g cost present, if so update cost and parent if child node
                    if (g < g_cost[node]) {
                        node->pred = current;
                        node->distance = f;
                        g_cost[node] = g;
                        callback(Event::Relax, node);
                        std::sort(open.begin(), open.end(),compare());
                    }
                }


            }
        }

    }
}
