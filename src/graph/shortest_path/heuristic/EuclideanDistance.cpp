//
// Created by laeri on 1/27/17.
//

#include "EuclideanDistance.h"

float EuclideanDistance::apply(graph::Vertex &node, graph::Vertex &goal) {
    sf::Vector2f delta = goal.position - node.position;
    return std::sqrt(delta.x * delta.x + delta.y * delta.y);
}
