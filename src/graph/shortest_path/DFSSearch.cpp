//
// Created by laeri on 1/27/17.
//

#include <stack>
#include <chrono>
#include <thread>
#include "DFSSearch.h"

void DFSSearch::search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    std::stack<graph::Vertex *> v_stack;
    v_stack.push(&src);
    src.pred = &src; // create dummy connection
    while (!v_stack.empty()) {
        graph::Vertex *current = v_stack.top();
        v_stack.pop();
        callback(Event::Current, current);
        std::vector<std::pair<int, float>> tmp = std::vector<std::pair<int, float>>(*(&graph.adj_of(current)));
        while (!tmp.empty()) {
            int i = std::rand() % tmp.size();
            graph::Vertex *branch = graph.get_vertices()[tmp[i].first];

            if (!branch->pred) {
                v_stack.push(branch);
                branch->pred = current;
                callback(Event::Relax, branch);
            }
            tmp.erase(tmp.begin() + i);
        }
    }
    src.pred = nullptr; // remove dummy connection
}
