//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_COMMAND_H
#define SEARCH_ALG_COMMAND_H


#include "graph/Graph.h"

class Command {
public:
    Command();

    virtual void do_action() = 0;
    virtual void undo_action() = 0;

};


#endif //SEARCH_ALG_COMMAND_H
