//
// Created by laeri on 1/25/17.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <SFML/Window/Event.hpp>
#include <thread>
#include "GraphDisplay.h"
#include "graph/Graph.h"
#include "Command.h"
#include "graph/shortest_path/Dijkstra.h"
#include "DeleteConnectionAction.h"
#include "graph/shortest_path/BellmanFord.h"
#include "GridDrawer.h"


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

void run_and_color(Graph &graph, graph::Vertex *start, graph::Vertex *end, sf::Color &on_path) {
     bellman_ford::bellman_ford(graph, *start);
   // Dijkstra::dijkstra(graph, *start);
    color(end, on_path);
}

void GraphDisplay::run() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Search Algorithms");

    GridDrawer gridDrawer;

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
                        } else if (!end && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                                            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))) {
                            end = grid[x][y];
                            end->type = graph::Type::end;
                            end->color = end_color;
                            std::thread t1(run_and_color, std::ref(*graph), start, end, std::ref(on_path));
                            t1.detach();
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