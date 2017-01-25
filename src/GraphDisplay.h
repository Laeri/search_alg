//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_GRAPHDISPLAY_H
#define SEARCH_ALG_GRAPHDISPLAY_H


#include "Command.h"

typedef std::vector<std::vector<graph::Vertex *>> Grid;

class GraphDisplay {

private:
    int SCREEN_HEIGHT = 640;
    int SCREEN_WIDTH = 640;
    std::vector<Command *> commands;
public:
    GraphDisplay();
    void run();
    void close();
    void reset(const sf::Color &free_color, Graph &graph, graph::Vertex *&start, graph::Vertex *&end);


    bool in_bounds(int side_length, int &x, int &y) const;
};


#endif //SEARCH_ALG_GRAPHDISPLAY_H
