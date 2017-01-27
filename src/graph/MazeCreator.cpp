//
// Created by laeri on 1/27/17.
//

#include <stack>
#include <set>
#include <iostream>
#include <thread>
#include "MazeCreator.h"

bool MazeCreator::is_pos_acceptable(Grid &grid, Graph &graph, sf::Vector2i new_pos, sf::Vector2i parent_pos,
                                    graph::Vertex *start, Dir dir) {
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


    if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x >= grid.size() || new_pos.y >= grid.size()) return false;

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
            if (x_check == parent_pos.x && y_check == parent_pos.y)continue;
            to_check.insert(grid[x_check][y_check]);

        }
    } else if (dir == Dir::up || dir == Dir::down) {
        for (auto &d: up) {
            int x_check = new_pos.x + d.first;
            int y_check = new_pos.y + y_sign * d.second;

            if (x_check < 0 || y_check < 0 || x_check >= grid.size() || y_check >= grid.size()) continue;
            if (x_check == parent_pos.x && y_check == parent_pos.y)continue;
            to_check.insert(grid[x_check][y_check]);
        }
    }
    for (auto &check: to_check) {
        if (check == start)continue;
        if (graph.adj_of(check).size() > 0) return false;
    }
    return true;

}

sf::Vector2i MazeCreator::next(sf::Vector2i current, Dir dir) {
    if (dir == Dir::up) {
        current.y += 1;
    } else if (dir == Dir::down) {
        current.y -= 1;
    } else if (dir == Dir::right) {
        current.x += 1;
    } else {
        current.x -= 1;
    }
    return current;
}

void MazeCreator::createMaze(Grid &grid, Graph &graph, int x_start, int y_start, int step_size) {
    createMaze(grid, graph, x_start, y_start, step_size, step_size);
}

void MazeCreator::createMaze(Grid &grid, Graph &graph, int x_start, int y_start, int step_size, int min_path_size) {
    graph::Vertex *start = grid[x_start][y_start];
    start->type = graph::Type::maze_field;
    std::stack<sf::Vector2i> pos_stack;
    pos_stack.push({x_start, y_start});

    while (!pos_stack.empty()) {
        sf::Vector2i current_pos = pos_stack.top();
        graph::Vertex *current_node = grid[current_pos.x][current_pos.y];
        pos_stack.pop();

        std::vector<Dir> directions = {Dir::up, Dir::down, Dir::left, Dir::right};

        std::random_shuffle(directions.begin(), directions.end());

        for (auto &dir: directions) {
            sf::Vector2i child_pos = next(current_pos, dir);
            if (child_pos.x < 0 || child_pos.x >= grid.size() || child_pos.y < 0 ||
                child_pos.y >= grid.size())
                continue;

            sf::Vector2i tmp = current_pos;
            bool path_found = true;
            int path_length = 0;

            for (int i = 0; i < step_size; i++) {
                sf::Vector2i parent_pos = sf::Vector2i(tmp);
                tmp = next(tmp, dir);
                if (!is_pos_acceptable(grid, graph, tmp, parent_pos, start, dir)) {
                    path_found = false;
                    break;
                }
                path_length ++;
            }
            tmp = current_pos;
            graph::Vertex *child;
            graph::Vertex *previous;
            previous = current_node;
            if (path_found || path_length >= min_path_size) {
                for (int i = 0; i < path_length; i++) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));

                    tmp = next(tmp, dir);
                    child = grid[tmp.x][tmp.y];
                    child->pred = previous;
                    graph.bi_connect(child, previous, 1);
                    grid[tmp.x][tmp.y]->type = graph::Type::maze_field;
                    previous = child;
                }
                pos_stack.push(tmp);
            }
        }
    }

    for (auto &v: graph.get_vertices()) {
        if (v->type != graph::Type::maze_field) {
            v->type = graph::Type::occupied;
        } else {
            v->pred = nullptr;
            v->type = graph::Type ::free;
        }
    }
}