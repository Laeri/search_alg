//
// Created by laeri on 1/23/17.
//

#ifndef SEARCH_ALG_VERTEX_H
#define SEARCH_ALG_VERTEX_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Type.h"

namespace graph {
    class Vertex {
    public:
        sf::Vector2f position;
        float distance = 0;
        Type type = Type::free;

        Vertex *pred = nullptr;

        Vertex(float x, float y);

        Vertex(sf::Vector2f pos);

        Vertex();


    private:

    };
}

#endif //SEARCH_ALG_VERTEX_H
