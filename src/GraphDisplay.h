//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_GRAPHDISPLAY_H
#define SEARCH_ALG_GRAPHDISPLAY_H


#include "Command.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
typedef std::vector<std::vector<graph::Vertex *>> Grid;

class GraphDisplay {

private:
    int SCREEN_HEIGHT = 640;
    int SCREEN_WIDTH = 640;

    std::shared_ptr<Graph> graph;
    std::vector<Command *> commands;


    std::vector<std::pair<int, int>> neighbours = {{-1, 0},
                                                   {1,  1},
                                                   {-1, 1},
                                                   {1,  -1},
                                                   {-1, -1},
                                                   {1,  0},
                                                   {0,  1},
                                                   {0,  -1}};
public:
    GraphDisplay();
    void run();
    void close();
    void reset(const sf::Color &free_color, Graph &graph, graph::Vertex *&start, graph::Vertex *&end);


    bool in_bounds(int side_length, int &x, int &y) const;

    void init_grid_graph(Grid &grid, const sf::Color &free_color, int side_length, int grid_width, int grid_height) const;

    void draw_grid(sf::RenderWindow &window, sf::CircleShape &circle, sf::RectangleShape &rectangleShape, float half_length,
                   const Grid &grid) const;

    void draw_connections(sf::RenderWindow &window,  sf::Vertex *line, float half_length) const;
};


#endif //SEARCH_ALG_GRAPHDISPLAY_H
