//
// Created by laeri on 1/28/17.
//

#ifndef SEARCH_ALG_KRUSKALMST_H
#define SEARCH_ALG_KRUSKALMST_H


#include "Graph.h"
struct TmpEdge {
    graph::Vertex *v1;
    graph::Vertex *v2;
    float cost;
};

struct edge_compare {
    bool
    operator()(const TmpEdge &edge1, const TmpEdge &edge2) {
        return edge1.cost < edge2.cost;
    }
};

class KruskalMST {
public:
    void build(Graph &graph, graph::Vertex &root);
};


#endif //SEARCH_ALG_KRUSKALMST_H
