//
// Created by laeri on 1/25/17.
//

#include "GridDrawer.h"


void GridDrawer::draw_connections(Graph &graph, sf::RenderWindow &window, float half_length)  {
    for (auto &vertex: graph.get_vertices()) {
        for (auto adj: graph.adj_of(vertex)) {
            line[0].position = vertex->position + sf::Vector2f(half_length, half_length);
            line[1].position = graph.get_vertices()[adj.first]->position + sf::Vector2f(half_length, half_length);
            window.draw(line, 2, sf::Lines);
        }
    }
}

void GridDrawer::draw_grid(sf::RenderWindow &window, sf::CircleShape &circle, sf::RectangleShape &rectangleShape,
                             float half_length, const Grid &grid) const {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            circle.setPosition(grid[i][j]->position + sf::Vector2f(half_length, half_length));
            rectangleShape.setPosition(grid[i][j]->position);
            sf::Color rect_color = grid[i][j]->color;
            /*if(grid[i][j]->type == graph::Type::being_processed){
                rect_color = sf::Color::Cyan;
            } else if(grid[i][j]->type == graph::Type::free){
                rect_color = sf::Color::Green;
            } else if(grid[i][j]->type == graph::Type::on_path){
                rect_color = sf::Color::Red;
            }*/
            rectangleShape.setFillColor(rect_color);
            window.draw(rectangleShape);
            window.draw(circle);
        }
    }
}

void GridDrawer::draw(Graph &graph, sf::RenderWindow &window, Grid &grid, sf::CircleShape &circle,
                       sf::RectangleShape &rectangleShape, float half_length) {
    draw_grid(window,circle,rectangleShape,half_length,grid);
    draw_connections(graph,window, half_length);
}