//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_COMMAND_H
#define SEARCH_ALG_COMMAND_H


#include "graph/Graph.h"

class Command {
public:
    Command();

    virtual void do_action();
    virtual void undo_action();

};


#endif //SEARCH_ALG_COMMAND_H
