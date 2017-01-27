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

void GridDrawer::draw_grid(sf::RenderWindow &window, sf::RectangleShape &rectangleShape, const Grid &grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            rectangleShape.setPosition(grid[i][j]->position);
            sf::Color rect_color = colors[grid[i][j]->type];
            rectangleShape.setFillColor(rect_color);
            window.draw(rectangleShape);
        }
    }
}

void GridDrawer::draw(Graph &graph, sf::RenderWindow &window, Grid &grid, float half_length) {
    draw_grid(window, rectangleShape, grid);
    draw_connections(graph, window, half_length);
}

GridDrawer::GridDrawer(std::map<graph::Type, sf::Color> colors, float side_length) : colors(colors) {
    rectangleShape = sf::RectangleShape();
    rectangleShape.setOutlineThickness(1);
    rectangleShape.setOutlineColor(sf::Color::Black);
    rectangleShape.setSize({side_length, side_length});
}
