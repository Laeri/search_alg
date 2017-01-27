//
// Created by laeri on 1/27/17.
//

#include <thread>
#include <queue>
#include "GBestFirstSearch.h"


void GBestFirstSearch::search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {

    /* use standard priority queue because node distances
    * do not change after insertion
    */

    std::priority_queue<graph::Vertex *, std::vector<graph::Vertex *>, compare_queue> open;
    // set predecessor to dummy value (points back to itself)
    src.pred = &src;
    open.push(&src);
    graph::Vertex *current;
    while (!open.empty()) {
        // no edges are relaxed, therefore open.top() always returns smallest element
        current = open.top();
        callback(Event::Current, current);
        open.pop();
        if (current == &goal) {
            break;
        } else {
            for (auto &pair: graph.adj_of(current)) {
                auto node = graph.get_vertices()[pair.first];
                if (!node->pred) {
                    node->pred = current;
                    sf::Vector2f dPos = node->position - goal.position;
                    float distance = std::sqrt(dPos.x * dPos.x + dPos.y * dPos.y);
                    node->distance = distance;
                    open.push(node);
                    callback(Event::Relax, node);
                }
            }
        }
    }
    // reset predecessor of src
    src.pred = nullptr;
}
