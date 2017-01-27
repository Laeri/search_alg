//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_EUCLIDEANDISTANCE_H
#define SEARCH_ALG_EUCLIDEANDISTANCE_H


#include "Heuristic.h"

class EuclideanDistance: public Heuristic {
public:
    float apply(graph::Vertex &node, graph::Vertex &goal) override;
};


#endif //SEARCH_ALG_EUCLIDEANDISTANCE_H
