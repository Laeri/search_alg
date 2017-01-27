//
// Created by laeri on 1/27/17.
//

#include "DiagonalDistance.h"

DiagonalDistance::DiagonalDistance(float d_square, float d_diag) : d_square(d_square), d_diag(d_diag) {}

float DiagonalDistance::apply(graph::Vertex &node, graph::Vertex &goal) {
    float dx = std::abs(goal.position.x - node.position.x);
    float dy = std::abs(goal.position.y - node.position.y);
    float d_1 = 1;
    float d_2 = 1;
    return d_1 * (dx + dy) + (d_2 - 2 * d_1) * std::min(dx, dy);
}
