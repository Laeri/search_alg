//
// Created by laeri on 1/27/17.
//

#include "ManhattenDistance.h"

float ManhattenDistance::apply(graph::Vertex &node, graph::Vertex &goal) {
    float dx = std::abs(goal.position.x - node.position.x);
    float dy = std::abs(goal.position.y - node.position.y);
    return dx+dy;
}
