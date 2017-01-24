//
// Created by laeri on 1/23/17.
//

#include "Vertex.h"

namespace graph {
    Vertex::Vertex() {}
    Vertex::Vertex(float x, float y) : position(x, y) {}

    Vertex::Vertex(sf::Vector2f pos) : position(pos) {}

}