//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_MANHATTENDISTANCE_H
#define SEARCH_ALG_MANHATTENDISTANCE_H


#include "Heuristic.h"

class ManhattenDistance: public Heuristic {
public:
    float apply(graph::Vertex &node, graph::Vertex &goal) override;
};


#endif //SEARCH_ALG_MANHATTENDISTANCE_H
