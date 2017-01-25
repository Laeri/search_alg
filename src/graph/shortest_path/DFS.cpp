//
// Created by laeri on 1/25/17.
//

#include <thread>
#include "DFS.h"

void dfs::dfs_search(Graph &graph, graph::Vertex &vertex) {
    vertex.pred = &vertex;
    dfs_rec(graph, vertex);
    vertex.pred = nullptr;
}

void dfs::dfs_rec(Graph &graph, graph::Vertex &current) {
    sf::Color col = current.color;
    graph::Type type = current.type;
    current.color = sf::Color::White;
    current.type = graph::Type::being_processed;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    for (auto adj :graph.adj_of(&current)) {
        auto next = graph.get_vertices()[adj.first];
        if (!next->pred) {

            next->pred = &current;
            dfs_rec(graph, *next);
        }
    }
}