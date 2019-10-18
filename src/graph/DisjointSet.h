//
// Created by laeri on 1/28/17.
//

#ifndef SEARCH_ALG_DISJOINTSET_H
#define SEARCH_ALG_DISJOINTSET_H


#include "Vertex.h"

class DisjointSet {
public:
    DisjointSet();
    void merge(graph::Vertex* u, graph::Vertex* v);
    graph::Vertex* find(graph::Vertex* u);
    bool same_set(graph::Vertex* u, graph::Vertex* v);
};


#endif //SEARCH_ALG_DISJOINTSET_H
