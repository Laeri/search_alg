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
#include "graph/Graph.h"
#include "Command.h"
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


int clamp(int x, int min, int max) {
    return std::min(std::max(x, min), max);
}

void color(graph::Vertex *end, sf::Color &on_path) {
    graph::Vertex *current = end;
    while ((current = current->pred)) {

        if (current->type != graph::Type::start && current->type != graph::Type::end) {
            current->type = graph::Type::on_path;
            current->color = on_path;
        }
    }
}

void run_search(GraphSearch *search, Graph &graph, graph::Vertex *start, graph::Vertex *end, sf::Color &on_path) {
    search->search(graph, *start, *end);
    color(end, on_path);
}

void create_maze(Grid &grid, Graph &graph, int start_x, int start_y, int step_size) {
    MazeCreator mazeCreator;
    mazeCreator.createMaze(grid, graph, start_x, start_y, step_size);
}

void GraphDisplay::run() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Search Algorithms");
    GridDrawer gridDrawer;

    std::map<std::string, GraphSearch *> search_func;


    sf::Font font;
    if (!font.loadFromFile("Rubik-Regular.ttf")) {
        std::cout << "Font could not be found" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);

    search_func["Dijkstra"] = new DijkstraSearch();
    search_func["DFS"] = new DFSSearch();
    search_func["BFS"] = new BFSSearch();
    search_func["Bellman-Ford"] = new BellmanFordSearch();
    search_func["A-Star"] = new AStarSearch();
    search_func["Greedy Best-First-Search"] = new GBestFirstSearch();
    auto current_search = search_func.begin();

    sf::CircleShape circle(1);
    circle.setFillColor(sf::Color::Black);
    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
    sf::RectangleShape rectangleShape({2, 2});
    rectangleShape.setOutlineThickness(1);
    rectangleShape.setOutlineColor(sf::Color::Black);


    sf::Color free_color = sf::Color(100, 255, 100);
    sf::Color taken_color = sf::Color(100, 100, 255);
    sf::Color start_color = sf::Color(255, 0, 0);
    sf::Color end_color = sf::Color(255, 0, 100);
    sf::Color on_path = sf::Color(79, 26, 60);
    graph = std::make_shared<Graph>();
    int side_length = 16; // in pixels
    float half_length = side_length / 2.f;
    int grid_width = SCREEN_WIDTH / side_length;
    int grid_height = SCREEN_HEIGHT / side_length;
    rectangleShape.setSize({side_length, side_length});
    Grid grid = Grid(grid_width, std::vector<graph::Vertex *>(grid_height));

    init_grid_graph(grid, free_color, side_length, grid_width, grid_height);
    Graph &g = *graph;

    connect_grid(grid_width, grid_height, grid);


    graph::Vertex *start = nullptr;
    graph::Vertex *end = nullptr;

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
                    } else if (event.key.code == sf::Keyboard::R) {
                        reset(free_color, *graph, start, end);
                        for (auto &adj: graph->get_adjacencies()) {
                            adj.clear();
                        }
                        connect_grid(grid_width, grid_height, grid);
                    } else if (event.key.code == sf::Keyboard::T) {
                        for (auto &v :graph->get_vertices()) {
                            if (v->type != graph::Type::occupied) {
                                v->pred = nullptr;
                                v->color = free_color;
                                v->type = graph::Type::free;
                            }
                        }
                        start = nullptr;
                        end = nullptr;
                    } else if (event.key.code == sf::Keyboard::M) {
                        reset(free_color, *graph, start, end);
                        sf::Clock clock;
                        srand(time((time_t *) clock.getElapsedTime().asMilliseconds()));
                        for (auto &adj: graph->get_adjacencies()) {
                            adj.clear();
                        }
                        std::thread maze_thread(create_maze, std::ref(grid), std::ref(*graph), 0, 0, 2);
                        maze_thread.detach();
                    } else if (event.key.code == sf::Keyboard::Right) {
                        current_search++;
                        if (current_search == search_func.end()) current_search = search_func.begin();
                    } else if (event.key.code == sf::Keyboard::Left) {
                        if (current_search == search_func.begin()) current_search = search_func.end();
                        current_search--;
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Button::Left &&
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))) {
                        int x = event.mouseButton.x * (1.f / side_length);
                        int y = event.mouseButton.y * (1.f / side_length);
                        if (!start) {
                            start = grid[x][y];
                            start->color = start_color;
                            start->type = graph::Type::start;
                        } else if (!end) {
                            end = grid[x][y];
                            end->type = graph::Type::end;
                            end->color = end_color;
                            std::thread t1(run_search, current_search->second, std::ref(*graph), start, end,
                                           std::ref(on_path));
                            t1.detach();
                        } else {
                            end->type = graph::Type::free;
                            end->color = free_color;
                            graph::Vertex *path_v = end;
                            while ((path_v = path_v->pred)) {
                                if (path_v->type == graph::Type::start) break;
                                path_v->type = graph::Type::free;
                                path_v->color = free_color;
                            }

                            end = grid[x][y];
                            end->type = graph::Type::end;
                            end->color = end_color;
                            color(end, on_path);
                        }
                    } else {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if (inside_grid(side_length, grid, x, y)) {
                            grid[x][y]->color = taken_color;
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
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                        !(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                          sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {

                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;
                        if (inside_grid(side_length, grid, x, y)) {
                            grid[x][y]->color = taken_color;
                            Command *delete_action = new DeleteConnectionAction(*graph, sf::Vector2i(x, y), grid[x][y]);
                            delete_action->do_action();
                            commands.push_back(delete_action);
                        }
                    }
                    break;
            }
        }
        window.clear();

        gridDrawer.draw(*graph, window, grid, circle, rectangleShape, half_length);

        text.setPosition(10, 10);
        text.setString(current_search->first);
        window.draw(text);

        window.display();
    }
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
            vertex->color = free_color;
            grid[x][y] = vertex;
            graph->add(vertex);
        }
    }
}


void GraphDisplay::reset(const sf::Color &free_color, Graph &graph, graph::Vertex *&start,
                         graph::Vertex *&end) {
    for (auto &v :graph.get_vertices()) {
        v->pred = nullptr;
        v->color = free_color;
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


void GraphDisplay::close() {

}