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
    std::map<graph::Vertex *, float> h_cost;
    std::map<graph::Vertex *, float> f_cost;

    open.push_back(&src);
    graph::Vertex *current;
    g_cost[&src] = 0;

    while (!open.empty()) {
        graph::Vertex *nearest = nullptr;
        int min_pos = -1;
        int pos = 0;
        float min_dist = std::numeric_limits<float>::max();
        for (auto &el: open) {
            if (el->distance < min_dist) {
                nearest = el;
                min_dist = el->distance;
                min_pos = pos;
            }
            pos++;
        }
        current = nearest;
        open.erase(open.begin() + min_pos);
        closed.push_back(current);

        callback(Event::Current, current);
        if (current == &goal) {
            break;
        }


        for (auto &pair: graph.adj_of(current)) {
            graph::Vertex *node = graph.get_vertices()[pair.first];
            if (std::find(closed.begin(), closed.end(), node) == closed.end()) { // not in closed
                float g = g_cost[current] + pair.second;
                // calculate h cost
                float h = heuristic->apply(*node, goal);
                float f = g + h;
                if (std::find(open.begin(), open.end(), node) == open.end()) { // not yet in open, so add it
                    node->pred = current;
                    open.push_back(node);
                    node->distance = f;
                    g_cost[node] = g;
                    h_cost[node] = h;
                    f_cost[node] = f;
                    callback(Event::Relax, node);
                } else { // check if g cost is lower than g cost present, if so update cost and parent if child node
                    if (g < g_cost[node]) {
                        node->pred = current;
                        node->distance = f;
                        g_cost[node] = g;
                        h_cost[node] = h;
                        f_cost[node] = f;
                        callback(Event::Relax, node);
                    }
                }


            }
        }

    }
}
