//
// Created by laeri on 1/27/17.
//

#include <stack>
#include <chrono>
#include <thread>
#include "DFSSearch.h"

void DFSSearch::search(Graph &graph, graph::Vertex &src) {
    std::stack<graph::Vertex *> v_stack;
    v_stack.push(&src);
    src.pred = &src; // create dummy connection
    while (!v_stack.empty()) {
        graph::Vertex *current = v_stack.top();
        v_stack.pop();
        std::vector<std::pair<int, float>> tmp = std::vector<std::pair<int, float>>(*(&graph.adj_of(current)));
        while (!tmp.empty()) {
            int i = std::rand() % tmp.size();
            graph::Vertex *branch = graph.get_vertices()[tmp[i].first];
            if (branch->type != graph::Type::start && branch->type != graph::Type::end) {
                branch->type = graph::Type::being_processed;
                branch->color = sf::Color::White;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (!branch->pred) {
                v_stack.push(branch);
                branch->pred = current;
            }
            tmp.erase(tmp.begin() + i);
        }
    }
    src.pred = nullptr; // remove dummy connection
}