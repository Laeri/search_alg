//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_DFS_H
#define SEARCH_ALG_DFS_H

#include "../Vertex.h"
#include "../Graph.h"
#include "../../GraphDisplay.h"

namespace dfs {
    void dfs_search(Graph &graph, graph::Vertex &vertex);
    void dfs_rec(Graph &graph, graph::Vertex &current);
    void dfs_it(Grid &grid,Graph &graph, graph::Vertex &vertex);
}


#endif //SEARCH_ALG_DFS_H
