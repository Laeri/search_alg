//
// Created by laeri on 1/26/17.
//

#ifndef SEARCH_ALG_ASTAR_H
#define SEARCH_ALG_ASTAR_H


#include "../Vertex.h"
#include "../Graph.h"

namespace a_star {
void a_star_search(Graph &graph, graph::Vertex &src, graph::Vertex &goal);
}

#endif //SEARCH_ALG_ASTAR_H
