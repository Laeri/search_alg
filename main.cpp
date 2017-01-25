#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include "src/graph/Vertex.h"
#include "src/graph/Graph.h"
#include "src/graph/shortest_path/BellmanFord.h"
#include "src/graph/shortest_path/Dijkstra.h"
#include "src/DeleteConnectionAction.h"
#include <thread>

typedef std::vector<std::vector<graph::Vertex *>> Grid;

int clamp(int x, int min, int max) {
    return std::min(std::max(x, min), max);
}

void color(graph::Vertex *end, sf::Color &on_path){
    graph::Vertex *current = end;
    while ((current = current->pred)) {
        current->color = on_path;
    }
}

void run_and_color(Graph &graph, graph::Vertex *start, graph::Vertex *end, sf::Color &on_path) {
    //bellman_ford::bellman_ford(graph, *start);
    Dijkstra::dijkstra(graph,*start);
    color(end, on_path);
}

int main() {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 640;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Search Algorithms");
    sf::CircleShape circle(1);
    circle.setFillColor(sf::Color::Black);
    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
    sf::RectangleShape rectangleShape({2, 2});
    rectangleShape.setOutlineThickness(1);
    rectangleShape.setOutlineColor(sf::Color::Black);


    sf::Vertex line[] = {sf::Vertex(sf::Vector2f()), sf::Vertex(sf::Vector2f())};

    sf::Color free_color = sf::Color(100, 255, 100);
    sf::Color taken_color = sf::Color(100, 100, 255);
    sf::Color start_color = sf::Color(255, 0, 0);
    sf::Color end_color = sf::Color(255, 0, 100);
    //sf::Color on_path = sf::Color(0, 255, 255);
    sf::Color on_path = sf::Color::Black;
    std::shared_ptr<Graph> graph = std::make_shared<Graph>();
    int side_length = 16; // in pixels
    float half_length = side_length / 2.f;
    int grid_width = SCREEN_WIDTH / side_length;
    int grid_height = SCREEN_HEIGHT / side_length;
    rectangleShape.setSize({side_length, side_length});
    Grid grid(grid_width, std::vector<graph::Vertex *>(grid_height));
    for (auto y = 0; y < grid_height; y++) {
        for (auto x = 0; x < grid_width; x++) {
            graph::Vertex *vertex = new graph::Vertex(x * side_length, y * side_length);
            vertex->color = free_color;
            grid[x][y] = vertex;
            graph->add(vertex);
        }
    }

    std::vector<std::pair<int, int>> neighbours = {{-1, 0},
                                                   {1,  1},
                                                   {-1, 1},
                                                   {1,  -1},
                                                   {-1, -1},
                                                   {1,  0},
                                                   {0,  1},
                                                   {0,  -1}};

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
                        for (auto &v :graph->get_vertices()) {
                            v->color = free_color;
                        }
                        start = nullptr;
                        end = nullptr;
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
                        } else if (!end) {
                            end = grid[x][y];
                            end->color = end_color;
                            std::thread t1(run_and_color, std::ref(*graph), start, end, std::ref(on_path));
                            t1.detach();

                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {

                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;
                        x *= (1.f / side_length);
                        y *= (1.f / side_length);
                        if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size()) {
                            grid[x][y]->color = taken_color;
                            DeleteConnectionAction delete_action(*graph, sf::Vector2i(x, y), grid[x][y]);
                            delete_action.do_action();
                        }
                    }
                    break;
            }
        }
        window.clear();

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                circle.setPosition(grid[i][j]->position + sf::Vector2f(half_length, half_length));
                rectangleShape.setPosition(grid[i][j]->position);
                rectangleShape.setFillColor(grid[i][j]->color);
                window.draw(rectangleShape);
                window.draw(circle);
            }
        }

        for (auto &vertex: graph->get_vertices()) {
            for (auto adj: graph->adj_of(vertex)) {
                line[0].position = vertex->position + sf::Vector2f(half_length, half_length);
                line[1].position = graph->get_vertices()[adj.first]->position + sf::Vector2f(half_length, half_length);
                window.draw(line, 2, sf::Lines);
            }
        }
        window.display();
    }
    return 0;
}
