//
// Created by laeri on 1/25/17.
//

#include <thread>
#include <stack>
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

void dfs::dfs_it(Graph &graph, graph::Vertex &vertex) {
    std::stack<graph::Vertex *> v_stack;
    v_stack.push(&vertex);
    vertex.pred = &vertex;
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
    vertex.pred = nullptr;
}

void dfs::dfs_maze(Grid &grid, Graph &graph, graph::Vertex &vertex) {
    std::stack<graph::Vertex *> v_stack;
    v_stack.push(&vertex);
    vertex.pred = &vertex;
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
    vertex.pred = nullptr;
    for (auto &adj: graph.get_adjacencies()) {
        adj.clear();
    }
    for (auto &v: graph.get_vertices()) {
        if (v->type != graph::Type::start && v->type != graph::Type::end && v->type != graph::Type::occupied) {
            v->type = graph::Type::free;
            v->color = sf::Color::Green;
        }
        if (v->pred)
            graph.bi_connect(v, v->pred, 1);
    }
}