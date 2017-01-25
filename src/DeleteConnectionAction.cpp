//
// Created by laeri on 1/25/17.
//

#include "DeleteConnectionAction.h"

DeleteConnectionAction::DeleteConnectionAction(Graph &graph, sf::Vector2i grid_pos, graph::Vertex* node) : Command(), grid_pos(grid_pos) {
    this->graph = &graph;
    this->node = node;
}

void DeleteConnectionAction::do_action() {
    graph->adj_of(node).clear();
    graph->remove_adj_to(node);
}

void DeleteConnectionAction::undo_action() {

}
