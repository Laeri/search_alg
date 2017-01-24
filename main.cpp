#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include "src/graph/Vertex.h"
#include "src/graph/Graph.h"


typedef std::vector<std::vector<Vertex *>> Grid;

int clamp(int x, int min, int max) {
    return std::min(std::max(x, min), max);
}

int main() {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 640;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Search Algorithms");
    sf::CircleShape circle(2.f);
    sf::RectangleShape rectangleShape({2, 2});
    rectangleShape.setOutlineThickness(1);
    rectangleShape.setOutlineColor(sf::Color::Black);

    sf::Color free_color = sf::Color(100, 255, 100);
    sf::Color taken_color = sf::Color(100, 100, 255);
    sf::Color start_color = sf::Color(255,0,0);
    sf::Color end_color = sf::Color(255,0,100);

    std::shared_ptr<Graph> graph = std::make_shared<Graph>();
    int side_length = 16; // in pixels
    int half_length = side_length / 2;
    int grid_width = SCREEN_WIDTH / side_length;
    int grid_height = SCREEN_HEIGHT / side_length;
    rectangleShape.setSize({side_length, side_length});
    Grid grid(grid_width, std::vector<Vertex *>(grid_height));
    for (auto y = 0; y < grid_height; y++) {
        for (auto x = 0; x < grid_width; x++) {
            Vertex *vertex = new Vertex(x * side_length, y * side_length);
            vertex->color = free_color;
            grid[x][y] = vertex;
            graph->add(vertex);
        }
    }


    for (auto i = 0; i < grid_width; i++) {
        for (auto j = 0; j < grid_height; j++) {
            for (auto s = -1; s < 2; s++) {
                for (auto t = -1; t < 2; t++) {
                    int coord_x = clamp(i + s, 0, grid_width - 1);
                    int coord_y = clamp(j + t, 0, grid_height - 1);
                    graph->bi_connect(grid[i][j], grid[coord_x][coord_y], 1);
                }
            }
        }
    }

    Vertex *start = nullptr;
    Vertex *end = nullptr;
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
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;
                        x *= (1.f / side_length);
                        y *= (1.f / side_length);
                        if(x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size()) {
                            grid[x][y]->color = taken_color;
                        }
                    }
                    break;
            }
        }
        window.clear();

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                circle.setPosition(grid[i][j]->position);
                rectangleShape.setPosition(grid[i][j]->position);
                rectangleShape.setFillColor(grid[i][j]->color);
                window.draw(rectangleShape);
            }
        }

        window.display();
    }
    return 0;
}
