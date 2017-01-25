//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_DELETECONNECTIONACTION_H
#define SEARCH_ALG_DELETECONNECTIONACTION_H


#include "Command.h"

class DeleteConnectionAction: public Command {
private:
    Graph *graph;
    sf::Vector2i grid_pos;
    graph::Vertex* node;
public:
    DeleteConnectionAction(Graph &graph, sf::Vector2i grid_pos, graph::Vertex* node);

    void do_action() override;

    void undo_action() override;
};


#endif //SEARCH_ALG_DELETECONNECTIONACTION_H
