//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_GRAPHDISPLAY_H
#define SEARCH_ALG_GRAPHDISPLAY_H


#include "Command.h"
#include "graph/shortest_path/GraphSearch.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

typedef std::vector<std::vector<graph::Vertex *>> Grid;
typedef std::map<std::string, GraphSearch *>::iterator Search_it;

class GraphDisplay {

private:
    int SCREEN_HEIGHT = 640;
    int SCREEN_WIDTH = 640;
    sf::Font font;
    sf::Text text;
    Search_it current_search;
    std::map<std::string, GraphSearch *> search_func;
    std::shared_ptr<Graph> graph;
    std::vector<Command *> commands;
    bool *lock_step = new bool(false);

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
    ~GraphDisplay();
    void run();

    void close();

    void reset(const sf::Color &free_color, Graph &graph, graph::Vertex *&start, graph::Vertex *&end);


    bool in_bounds(int side_length, int &x, int &y) const;

    void
    init_grid_graph(Grid &grid, const sf::Color &free_color, int side_length, int grid_width, int grid_height) const;

    void
    draw_grid(sf::RenderWindow &window, sf::CircleShape &circle, sf::RectangleShape &rectangleShape, float half_length,
              const Grid &grid) const;

    void draw_connections(sf::RenderWindow &window, sf::Vertex *line, float half_length) const;

    void connect_grid(int grid_width, int grid_height, const Grid &grid) const;

    bool inside_grid(int side_length, const Grid &grid, int &x, int &y) const;

    void createSearches();

    void drawText();

    void createMaze(const sf::Color &free_color, Grid &grid, graph::Vertex *&start, graph::Vertex *&end);

    void createText();
};

void color(graph::Vertex *end, sf::Color &on_path);
void run_search(GraphSearch *search, Graph &graph, graph::Vertex *start, graph::Vertex *end, sf::Color &on_path);
int clamp(int x, int min, int max);
void create_maze(Grid &grid, Graph &graph, int start_x, int start_y, int step_size);
#endif //SEARCH_ALG_GRAPHDISPLAY_H
