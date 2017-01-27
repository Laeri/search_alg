//
// Created by laeri on 1/25/17.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <SFML/Window/Event.hpp>
#include <thread>
#include <iostream>
#include "GraphDisplay.h"
#include "DeleteConnectionAction.h"
#include "GridDrawer.h"
#include "graph/MazeCreator.h"
#include "graph/shortest_path/GraphSearch.h"
#include "graph/shortest_path/DijkstraSearch.h"
#include "graph/shortest_path/DFSSearch.h"
#include "graph/shortest_path/BFSSearch.h"
#include "graph/shortest_path/BellmanFordSearch.h"
#include "graph/shortest_path/AStarSearch.h"
#include "graph/shortest_path/GBestFirstSearch.h"


GraphDisplay::GraphDisplay() {}


void GraphDisplay::run() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Search Algorithms");

    graph = std::make_shared<Graph>();

    // colors to color nodes
    std::map<graph::Type, sf::Color> colors = {
            {graph::Type::free,            sf::Color(100, 255, 100)},
            {graph::Type::being_processed, sf::Color::White},
            {graph::Type::start,           sf::Color(255, 0, 0)},
            {graph::Type::end,             sf::Color(255, 0, 100)},
            {graph::Type::on_path,         sf::Color(79, 26, 60)},
            {graph::Type::occupied,        sf::Color(100, 100, 255)},
            {graph::Type::relaxed,         sf::Color::Magenta}
    };

    // create grid
    int side_length = 16; // in pixels
    float half_length = side_length / 2.f;
    int grid_width = SCREEN_WIDTH / side_length;
    int grid_height = SCREEN_HEIGHT / side_length;

    GridDrawer gridDrawer(colors, side_length);

    createText();

    createSearches();

    Grid grid = Grid(grid_width, std::vector<graph::Vertex *>(grid_height));
    // create grid and add vertices to graph (without connections)
    init_grid_graph(grid, colors[graph::Type::free], side_length, grid_width, grid_height);
    // connect all vertices with neighbour vertices on grid
    connect_grid(grid_width, grid_height, grid);

    // start and end position used for searching
    graph::Vertex *start = nullptr;
    graph::Vertex *end = nullptr;

    // pass lock_step to all search algorithms
    // in order to change the mode with key presses
    for (auto &search: search_func) {
        search.second->lock_step = lock_step;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    } else if (event.key.code == sf::Keyboard::R) { // reset map, clear connections
                        reset(colors[graph::Type::free], *graph, start, end);
                        for (auto &adj: graph->get_adjacencies()) {
                            adj.clear();
                        }
                        connect_grid(grid_width, grid_height, grid);
                    } else if (event.key.code == sf::Keyboard::T) { // reset map/graph but keep obstacles
                        for (auto &v :graph->get_vertices()) {
                            if (v->type != graph::Type::occupied) {
                                v->pred = nullptr;
                                v->type = graph::Type::free;
                            }
                        }
                        start = nullptr;
                        end = nullptr;
                    } else if (event.key.code == sf::Keyboard::M) { // create a maze with dfs on sepearate thread
                        createMaze(colors[graph::Type::free], grid, start, end);
                    } else if (event.key.code == sf::Keyboard::Right) { // cycle through search algorithms
                        current_search++;
                        if (current_search == search_func.end()) current_search = search_func.begin();
                    } else if (event.key.code == sf::Keyboard::Left) { // cycle through search algorithms
                        if (current_search == search_func.begin()) current_search = search_func.end();
                        current_search--;
                    } else if (event.key.code == sf::Keyboard::L) { // lock search algorithm in other thread
                        current_search->second->locked = true;
                    } else if (event.key.code == sf::Keyboard::U) { // unlock search algorithm in other thread
                        current_search->second->locked = false;
                        current_search->second->var.notify_one();
                    } else if (event.key.code ==
                               sf::Keyboard::P) { // change lock step mode (if true every step in algorithm gets locked)
                        *lock_step = *lock_step ? false : true;
                        if (!*lock_step) {
                            current_search->second->locked = false;
                            current_search->second->var.notify_one();
                        }
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Button::Left &&
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                         sf::Keyboard::isKeyPressed(
                                 sf::Keyboard::Key::RControl))) { // if control is down set start or end
                        int x = event.mouseButton.x * (1.f / side_length);
                        int y = event.mouseButton.y * (1.f / side_length);
                        if (!start) { // if start not set, set it at mouse pos
                            start = grid[x][y];
                            start->type = graph::Type::start;
                        } else if (!end) { // if start set but end not, set it at mouse pos
                            end = grid[x][y];
                            end->type = graph::Type::end;
                            std::thread t1(run_search, current_search->second, std::ref(*graph), start, end);
                            t1.detach();
                        } else { // if start and end have been set and CTRL is still down, choose new end node and color shortest path again
                            end->type = graph::Type::free;
                            graph::Vertex *path_v = end;
                            // remove color of old path
                            while ((path_v = path_v->pred)) {
                                if (path_v->type == graph::Type::start) break;
                                path_v->type = graph::Type::free;
                            }

                            end = grid[x][y];
                            end->type = graph::Type::end;
                        }
                    } else { // if CTRL is not down, create an obstacle and remove connections in graph
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if (inside_grid(side_length, grid, x, y)) {
                            grid[x][y]->type = graph::Type::occupied;
                            Command *delete_action = new DeleteConnectionAction(*graph,
                                                                                sf::Vector2i(x, y),
                                                                                grid[x][y]);
                            delete_action->do_action();
                            commands.push_back(delete_action);
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
                    // if mouse is moved while holding CTRL down, the cell under the mouse is deleted
                    // and connections in graph are removed to create obstacle / barrier
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                        !(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                          sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {

                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;
                        if (inside_grid(side_length, grid, x, y)) {
                            grid[x][y]->type = graph::Type::occupied;
                            Command *delete_action = new DeleteConnectionAction(*graph, sf::Vector2i(x, y), grid[x][y]);
                            delete_action->do_action();
                            commands.push_back(delete_action);
                        }
                    }
                    break;
            }
        }
        window.clear();
        gridDrawer.draw(*graph, window, grid, half_length);
        drawText();
        window.draw(text);
        window.display();
    }
}

void GraphDisplay::createText() {
    if (!font.loadFromFile("Rubik-Regular.ttf")) {
        std::cout << "Font could not be found" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
}

void GraphDisplay::createMaze(const sf::Color &free_color, Grid &grid, graph::Vertex *&start, graph::Vertex *&end) {
    reset(free_color, *graph, start, end);
    sf::Clock clock;
    srand(time((time_t *) clock.getElapsedTime().asMilliseconds()));
    for (auto &adj: graph->get_adjacencies()) {
        adj.clear();
    }
    std::thread maze_thread(create_maze, ref(grid), std::ref(*graph), 0, 0, 2);
    maze_thread.detach();
}

void GraphDisplay::drawText() {
    text.setPosition(10, 10);
    text.setString(current_search->first);
}

void GraphDisplay::createSearches() {
    search_func["Dijkstra"] = new DijkstraSearch();
    search_func["DFS"] = new DFSSearch();
    search_func["BFS"] = new BFSSearch();
    search_func["Bellman-Ford"] = new BellmanFordSearch();
    search_func["A-Star"] = new AStarSearch();
    search_func["Greedy Best-First-Search"] = new GBestFirstSearch();
    current_search = search_func.begin();
}

bool GraphDisplay::inside_grid(int side_length, const Grid &grid, int &x, int &y) const {
    x *= (1.f / side_length);
    y *= (1.f / side_length);
    return x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size();
}

void GraphDisplay::connect_grid(int grid_width, int grid_height, const Grid &grid) const {
    for (auto i = 0; i < grid_width; i++) {
        for (auto j = 0; j < grid_height; j++) {
            for (auto &pair: neighbours) {
                int coord_x = clamp(i + pair.first, 0, grid_width - 1);
                int coord_y = clamp(j + pair.second, 0, grid_height - 1);
                if (!(i == coord_x && j == coord_y)) {
                    sf::Vector2f dPos = sf::Vector2f(i - coord_x, j - coord_y);
                    float dist = std::sqrt(dPos.x * dPos.x + dPos.y * dPos.y);
                    graph->bi_connect(grid[i][j], grid[coord_x][coord_y], dist);
                }
            }
        }
    }
}


void GraphDisplay::init_grid_graph(Grid &grid, const sf::Color &free_color, int side_length, int grid_width,
                                   int grid_height) const {
    for (auto y = 0; y < grid_height; y++) {
        for (auto x = 0; x < grid_width; x++) {
            graph::Vertex *vertex = new graph::Vertex(x * side_length, y * side_length);
            vertex->type = graph::Type::free;
            grid[x][y] = vertex;
            graph->add(vertex);
        }
    }
}


void GraphDisplay::reset(const sf::Color &free_color, Graph &graph, graph::Vertex *&start,
                         graph::Vertex *&end) {
    for (auto &v :graph.get_vertices()) {
        v->pred = nullptr;
        v->type = graph::Type::free;
    }
    start = nullptr;
    end = nullptr;
    for (auto &command: commands) {
        command->undo_action();
    }
    for (auto command: commands) {
        delete command;
    }
    commands.clear();
}

GraphDisplay::~GraphDisplay() {
    delete lock_step;
}


int clamp(int x, int min, int max) {
    return std::min(std::max(x, min), max);
}

void color(graph::Vertex *end) {
    graph::Vertex *current = end;
    while ((current = current->pred)) {

        if (current->type != graph::Type::start && current->type != graph::Type::end) {
            current->type = graph::Type::on_path;
        }
    }
}

void run_search(GraphSearch *search, Graph &graph, graph::Vertex *start, graph::Vertex *end) {
    search->search(graph, *start, *end);
    color(end);
}

void create_maze(Grid &grid, Graph &graph, int start_x, int start_y, int step_size) {
    MazeCreator mazeCreator;
    mazeCreator.createMaze(grid, graph, start_x, start_y, step_size);
}
