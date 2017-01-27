//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_HEURISTIC_H
#define SEARCH_ALG_HEURISTIC_H


#include "../../Vertex.h"

class Heuristic {
public:
    Heuristic();
    virtual float apply(graph::Vertex &node, graph::Vertex &goal);
};


#endif //SEARCH_ALG_HEURISTIC_H
