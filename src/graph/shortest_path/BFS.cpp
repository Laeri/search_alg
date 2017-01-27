//
// Created by laeri on 1/26/17.
//

#include <queue>
#include <thread>
#include "BFS.h"

void bfs::bfs_search(Graph &graph, graph::Vertex &src) {
    src.pred = &src;
    std::queue<graph::Vertex *> node_stack;
    node_stack.push(&src);
    graph::Vertex *current;
    while (!node_stack.empty()) {
        current = node_stack.front();
        node_stack.pop();
        for (auto &pair: graph.adj_of(current)) {
            graph::Vertex *next = graph.get_vertices()[pair.first];

            if ((next->type != graph::Type::start) && (next->type != graph::Type::end) &&
                (next->type != graph::Type::occupied)) {
                next->color = sf::Color::White;
                next->type = graph::Type::being_processed;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(100));

            if (!next->pred) {
                next->pred = current;
                node_stack.push(next);
            }
        }
    }

    src.pred = nullptr;
}