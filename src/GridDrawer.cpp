//
// Created by laeri on 1/25/17.
//

#include "GridDrawer.h"


void GridDrawer::draw_connections(Graph &graph, sf::RenderWindow &window, float half_length) {
    for (auto &vertex: graph.get_vertices()) {
        for (auto adj: graph.adj_of(vertex)) {
            line[0].position = vertex->position + sf::Vector2f(half_length, half_length);
            line[1].position = graph.get_vertices()[adj.first]->position + sf::Vector2f(half_length, half_length);
            window.draw(line, 2, sf::Lines);
        }
    }
}

void GridDrawer::draw_grid(sf::RenderWindow &window, sf::CircleShape &circle, sf::RectangleShape &rectangleShape,
                           float half_length, const Grid &grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            circle.setPosition(grid[i][j]->position + sf::Vector2f(half_length, half_length));
            rectangleShape.setPosition(grid[i][j]->position);
            sf::Color rect_color = colors[grid[i][j]->type];
            rectangleShape.setFillColor(rect_color);
            window.draw(rectangleShape);
            window.draw(circle);
        }
    }
}

void GridDrawer::draw(Graph &graph, sf::RenderWindow &window, Grid &grid, float half_length) {
    draw_grid(window, circle, rectangleShape, half_length, grid);
    draw_connections(graph, window, half_length);
}

GridDrawer::GridDrawer(std::map<graph::Type, sf::Color> colors, float side_length) : colors(colors) {
    // shapes to draw grid and graph
    circle = sf::CircleShape(1.0f);
    circle.setFillColor(sf::Color::Black);
    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
    rectangleShape = sf::RectangleShape();
    rectangleShape.setOutlineThickness(1);
    rectangleShape.setOutlineColor(sf::Color::Black);
    rectangleShape.setSize({side_length, side_length});
}
