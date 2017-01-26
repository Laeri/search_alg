//
// Created by laeri on 1/26/17.
//

#include <queue>
#include <thread>
#include <iostream>
#include "GreedyBestFirstSearch.h"
#include "Dijkstra.h"

void best_first::best_first_search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    std::priority_queue<graph::Vertex *, std::vector<graph::Vertex *>, compare> open;
    src.pred = &src;

    for (auto v: graph.get_vertices()) {
        sf::Vector2f dPos = v->position - goal.position;
        float distance = std::sqrt(dPos.x * dPos.x + dPos.y * dPos.y);
        v->distance = distance;
    }
    open.push(&src);

    graph::Vertex *current;
    while (!open.empty()) {
        // no edges are relaxed!
       /* std::make_heap(const_cast<graph::Vertex**>(&open.top()),
                       const_cast<graph::Vertex**>(&open.top()) + open.size(),
                       compare());
        *///
        current = open.top();
        open.pop();
        if (current == &goal) {
            std::cout << "Goal found" << std::endl;
            break;
        } else {
            for (auto &pair: graph.adj_of(current)) {
                auto node = graph.get_vertices()[pair.first];
                if(!node->pred){
                    node->pred = current;
                    open.push(node);
                }
                if((node->type != graph::Type::start) && (node->type != graph::Type::end) && (node->type != graph::Type::occupied)) {
                    node->color = sf::Color::White;
                    node->type = graph::Type::being_processed;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        }
    }

    src.pred = nullptr;
}