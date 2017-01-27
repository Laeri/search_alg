//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_GRIDPAINTER_H
#define SEARCH_ALG_GRIDPAINTER_H


#include "GraphDisplay.h"

class GridDrawer {

private:
    sf::CircleShape circle;
    sf::RectangleShape rectangleShape;
    sf::Vertex line[2] = {sf::Vertex(), sf::Vertex()};
    std::map<graph::Type, sf::Color> colors;

    void draw_connections(Graph &graph, sf::RenderWindow &window, float half_length);

    void
    draw_grid(sf::RenderWindow &window, sf::CircleShape &circle, sf::RectangleShape &rectangleShape, float half_length,
              const Grid &grid);

public:
    void draw(Graph &graph, sf::RenderWindow &window, Grid &grid, float half_length);


    GridDrawer(std::map<graph::Type, sf::Color> colors, float side_length);
};

#endif //SEARCH_ALG_GRIDPAINTER_H
