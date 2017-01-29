//
// Created by laeri on 1/29/17.
//

#ifndef SEARCH_ALG_PRIMMST_H
#define SEARCH_ALG_PRIMMST_H


#include "Graph.h"
#include "Vertex.h"

struct compare_vertex {
    bool operator()(const graph::Vertex* u, const graph::Vertex* v){
        return u->distance < v->distance;
    }
};

struct Connection {
    graph::Vertex* from;
    float cost;
};

class PrimMST {
public:
    void build(Graph &graph, graph::Vertex &root);

};


#endif //SEARCH_ALG_PRIMMST_H
