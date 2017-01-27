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
    void createMaze(Grid &grid, Graph &graph, int x_start, int y_start);
    bool is_pos_acceptable(Grid &grid, Graph &graph, sf::Vector2i new_pos, Dir dir);
};


#endif //SEARCH_ALG_MAZECREATOR_H
