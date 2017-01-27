//
// Created by laeri on 1/26/17.
//
#include <map>
#include <thread>
#include "AStar.h"
#include "Dijkstra.h"

void a_star::a_star_search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    Dijkstra::init_single_source(graph, src);
    std::vector<graph::Vertex *> open;
    std::vector<graph::Vertex *> closed;

    std::map<graph::Vertex *, float> g_cost;
    std::map<graph::Vertex *, float> h_cost;
    std::map<graph::Vertex*, float> f_cost;

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

        if (current == &goal) {
            break;
        }

        for (auto &pair: graph.adj_of(current)) {
            graph::Vertex *node = graph.get_vertices()[pair.first];
            if (std::find(closed.begin(), closed.end(), node) == closed.end()) { // not in closed
                float g = g_cost[current] + pair.second;
                // calculate h cost
                float dx = node->position.x - goal.position.x;
                float dy = node->position.y - goal.position.y;
                float h = std::sqrt(dx * dx + dy * dy);
                float f = g+h;
                if (std::find(open.begin(), open.end(), node) == open.end()) { // not yet in open, so add it
                    node->pred = current;
                    open.push_back(node);
                    node->distance = f;
                    g_cost[node] = g;
                    h_cost[node] = h;
                    f_cost[node] = f;
                } else { // check if g cost is lower than g cost present, if so update cost and parent if child node
                    if(g < g_cost[node]){
                        node->pred = current;
                        node->distance = f;
                        g_cost[node] = g;
                        h_cost[node] = h;
                        f_cost[node] = f;
                    }
                }



                // color
                if((current->type != graph::Type::start) && (current->type != graph::Type::end) && (current->type != graph::Type::occupied)) {
                    current->color = sf::Color::White;
                    current->type = graph::Type::being_processed;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));

            }
        }

    }
}
