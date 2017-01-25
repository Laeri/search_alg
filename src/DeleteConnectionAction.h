//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_DELETECONNECTIONACTION_H
#define SEARCH_ALG_DELETECONNECTIONACTION_H


#include <map>
#include "Command.h"

class DeleteConnectionAction: public Command {
private:
    Graph *graph;
    sf::Vector2i grid_pos;
    graph::Vertex* node;
    std::vector<std::pair<int, float>> adj_node;
    std::map<int, std::vector<std::pair<int,float>>> adj_other;
public:
    DeleteConnectionAction(Graph &graph, sf::Vector2i grid_pos, graph::Vertex* node);

    void do_action() override;

    void undo_action() override;
};


#endif //SEARCH_ALG_DELETECONNECTIONACTION_H
