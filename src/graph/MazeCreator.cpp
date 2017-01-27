//
// Created by laeri on 1/27/17.
//

#include <stack>
#include <set>
#include "MazeCreator.h"

bool MazeCreator::is_pos_acceptable(Grid &grid, Graph &graph, sf::Vector2i new_pos, Dir dir) {
    std::vector<std::pair<int, int>> right = {{0, 1},
                                              {0, -1},
                                              {1, 0},
                                              {1, 1},
                                              {1, -1}};
    std::vector<std::pair<int, int>> up = {{0,  1},
                                           {-1, 0},
                                           {1,  0},
                                           {1,  1},
                                           {-1, 1}};

    int x_sign = 1;
    int y_sign = 1;
    if (dir == Dir::left) x_sign = -1;
    if (dir == Dir::down) y_sign = -1;

    std::set<graph::Vertex *> to_check;
    if (dir == Dir::left || dir == Dir::right) {
        for (auto &d: right) {
            int x_check = new_pos.x + x_sign * d.first;
            int y_check = new_pos.y + d.second;

            if (x_check < 0 || y_check < 0 || x_check >= grid.size() || y_check >= grid.size()) continue;
            if (grid[x_check][y_check] == grid[new_pos.x][new_pos.y]->pred)continue;
            to_check.insert(grid[x_check][y_check]);

        }
    } else if (dir == Dir::up || dir == Dir::down) {
        for (auto &d: up) {
            int x_check = new_pos.x + d.first;
            int y_check = new_pos.y + y_sign * d.second;

            if (x_check < 0 || y_check < 0 || x_check >= grid.size() || y_check >= grid.size()) continue;
            if (grid[x_check][y_check] == grid[new_pos.x][new_pos.y]->pred)continue;
            to_check.insert(grid[x_check][y_check]);
        }
    }
    for (auto &check: to_check) {
        if (graph.adj_of(check).size() > 0) return false;
    }


}

void MazeCreator::createMaze(Grid &grid, Graph &graph, int x_start, int y_start) {

    Dir dir;
    std::stack<sf::Vector2i> pos_stack;
    pos_stack.push({x_start, y_start});
    while (!pos_stack.empty()) {
        sf::Vector2i current_pos = pos_stack.top();
        graph::Vertex *current_node = grid[current_pos.x][current_pos.y];
        pos_stack.pop();

        std::vector<Dir> directions = {Dir::up, Dir::down, Dir::left, Dir::right};

        std::random_shuffle(directions.begin(), directions.end());

        for (auto &dir: directions) {
            sf::Vector2i child_pos = sf::Vector2i(current_pos);
            if (dir == Dir::up) {
                child_pos.y += 1;
            } else if (dir == Dir::down) {
                child_pos.y -= 1;
            } else if (dir == Dir::right) {
                child_pos.x += 1;
            } else {
                child_pos.x -= 1;
            }

            if (child_pos.x < 0 || child_pos.x >= grid.size() || child_pos.y < 0 || child_pos.y >= grid.size())continue;
            graph::Vertex *child_node = grid[child_pos.x][child_pos.y];
            child_node->pred = current_node;
            if (is_pos_acceptable(grid, graph, child_pos, dir)) {
                pos_stack.push(child_pos);
                grid[child_pos.x][child_pos.y]->type = graph::Type::maze_field;
                graph.bi_connect(child_node, current_node, 1);
            } else {
                child_node->pred = nullptr;
            }

        }

    }

    for (auto &v: graph.get_vertices()) {
        if (v->type != graph::Type::maze_field) {
            v->color = sf::Color::Blue;
            v->type = graph::Type::occupied;
        }
    }
}