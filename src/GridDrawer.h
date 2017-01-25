//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_GRIDPAINTER_H
#define SEARCH_ALG_GRIDPAINTER_H


#include "GraphDisplay.h"

class GridDrawer {

private:
    sf::Vertex line[2] = {sf::Vertex(), sf::Vertex()};


    void draw_connections(Graph &graph, sf::RenderWindow &window, float half_length);

    void
    draw_grid(sf::RenderWindow &window, sf::CircleShape &circle, sf::RectangleShape &rectangleShape, float half_length,
              const Grid &grid) const;

public:
    void draw(Graph &graph, sf::RenderWindow &window, Grid &grid, sf::CircleShape &circle,
              sf::RectangleShape &rectangleShape,
              float half_length);


};

#endif //SEARCH_ALG_GRIDPAINTER_H
