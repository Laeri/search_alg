//
// Created by laeri on 1/25/17.
//

#include "DeleteConnectionAction.h"

DeleteConnectionAction::DeleteConnectionAction(Graph &graph, sf::Vector2i grid_pos, graph::Vertex* node) : Command(), grid_pos(grid_pos) {
    this->graph = &graph;
    this->node = node;
}

void DeleteConnectionAction::do_action() {
    node->type = graph::Type::occupied;
    adj_node =  std::vector<std::pair<int, float>>(graph->adj_of(node).begin(), graph->adj_of(node).end());
    graph->adj_of(node).clear();
    //graph->remove_adj_to(node);

    int from = 0;
    int v = graph->index_of(node);
    for (auto &edges: graph->get_adjacencies()) {
        std::vector<std::pair<int, float>>::iterator it = edges.begin();
        while((it != edges.end())){
            if(it->first == v){
                adj_other[from].push_back(*it);
                it = edges.erase(it);
                //edges.erase(it++);  // alternatively,
            } else {
                ++it;
            }
        }
        from++;
    }
}

void DeleteConnectionAction::undo_action() {
    node->type = graph::Type::free;
    graph->adj_of(node).insert(graph->adj_of(node).begin(), adj_node.begin(), adj_node.end());
    for(auto &mapping: adj_other){
        int v_index = mapping.first;
        std::vector<std::pair<int, float>> edges = mapping.second;
        auto &adj = graph->adj_of(graph->get_vertices()[v_index]);
        adj.insert(adj.begin(), edges.begin(), edges.end());
    }
}
