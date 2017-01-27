//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_MAZECREATOR_H
#define SEARCH_ALG_MAZECREATOR_H


#include "Graph.h"
#include "../GraphDisplay.h"

class MazeCreator {
public:
    enum class Dir {
        up, down, right, left
    };
private:
    sf::Vector2i next(sf::Vector2i current, Dir dir);
public:

    void createMaze(Grid &grid, Graph &graph, int x_start, int y_start ,int step_size);
    bool is_pos_acceptable(Grid &grid, Graph &graph, sf::Vector2i new_pos, sf::Vector2i parent_pos, graph::Vertex* start, Dir dir);
};


#endif //SEARCH_ALG_MAZECREATOR_H
