//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_DIAGONALDISTANCE_H
#define SEARCH_ALG_DIAGONALDISTANCE_H


#include "Heuristic.h"

class DiagonalDistance : public Heuristic {
    float d_square;
    float d_diag;
public:
    DiagonalDistance(float d_square, float d_diag);
    float apply(graph::Vertex &node, graph::Vertex &goal) override;
};


#endif //SEARCH_ALG_DIAGONALDISTANCE_H
