//
// Created by laeri on 1/23/17.
//

#ifndef SEARCH_ALG_VERTEX_H
#define SEARCH_ALG_VERTEX_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Color.hpp>

namespace graph {
    class Vertex {
    public:
        sf::Vector2f position;
        sf::Color color;
        float distance = 0;
        Vertex* pred = nullptr;
        Vertex(float x, float y);

        Vertex(sf::Vector2f pos);
        Vertex();
    private:

    };
}

#endif //SEARCH_ALG_VERTEX_H
