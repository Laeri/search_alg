//
// Created by laeri on 1/27/17.
//

#include <iostream>
#include <thread>
#include "GraphSearch.h"

GraphSearch::GraphSearch() {
    on_event = [this](Event event, graph::Vertex *node) {
        switch (event) {
            case Event::Relax:
                this->relax_steps++;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                if (node->type != graph::Type::start && node->type != graph::Type::end) {
                    node->type = graph::Type::relaxed;
                }
                break;
            case Event::Current:
                if ((node->type != graph::Type::start) && (node->type != graph::Type::end) &&
                    (node->type != graph::Type::occupied)) {
                    node->color = sf::Color::White;
                    node->type = graph::Type::being_processed;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                break;
        }
    };

    lock = std::unique_lock<std::mutex>(mutex);
}

GraphSearch::GraphSearch(Function on_event) : on_event(on_event) {
}

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
        callback(Event::Relax, &v);
    }

}

void GraphSearch::callback(Event event, graph::Vertex *vertex) {
    if (locked) {
        var.wait(lock);
    } else if (lock_step && *lock_step) locked = true;
    if (on_event) on_event(event, vertex);
    else std::cout << "No callback function provided!" << std::endl;
}