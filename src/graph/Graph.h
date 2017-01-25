//
// Created by laeri on 1/23/17.
//

#ifndef SEARCH_ALG_GRAPH_H
#define SEARCH_ALG_GRAPH_H

#include <vector>
#include "Vertex.h"

typedef std::vector<std::pair<int, float>> ADJ_V;
typedef std::vector<ADJ_V> Adjacency;
typedef std::vector<graph::Vertex *> VertexList;

class Graph {
private:
    Adjacency adj;
    VertexList vertices;
public:
    Graph();

    ~Graph();

    void add(graph::Vertex *vertex);

    void bi_connect(graph::Vertex *va, graph::Vertex *vb, float weight);

    bool connected(graph::Vertex &va, graph::Vertex &vb);

    VertexList& get_vertices();
    Adjacency& get_adjacencies();
    ADJ_V &adj_of(graph::Vertex *);
    void remove_adj_to(graph::Vertex *vertex);
    int index_of(graph::Vertex *vertex);

};


#endif //SEARCH_ALG_GRAPH_H
