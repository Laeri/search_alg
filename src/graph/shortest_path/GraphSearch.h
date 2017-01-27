//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_GRAPHSEARCH_H
#define SEARCH_ALG_GRAPHSEARCH_H


#include "../Graph.h"

class GraphSearch {
public:
    virtual void search(Graph &graph, graph::Vertex &src, graph::Vertex &goal)= 0;
    virtual void relax(graph::Vertex &u, graph::Vertex &v, float weight);

    virtual void init_single_src(Graph &graph, graph::Vertex &src);
};


#endif //SEARCH_ALG_GRAPHSEARCH_H
