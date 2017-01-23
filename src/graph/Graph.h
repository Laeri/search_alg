//
// Created by laeri on 1/23/17.
//

#ifndef SEARCH_ALG_GRAPH_H
#define SEARCH_ALG_GRAPH_H

#include <vector>
#include "Vertex.h"

typedef std::vector<std::pair<int, int>> ADJ_V;
typedef std::vector<ADJ_V> Adjacency;
typedef std::vector<Vertex *> VertexList;

class Graph {
private:
    Adjacency adj;
    VertexList vertices;
    int index_of(Vertex *vertex);
public:
    Graph();

    ~Graph();

    void add(Vertex *vertex);

    void bi_connect(Vertex *va, Vertex *vb, int weight);

    bool connected(Vertex &va, Vertex &vb);


};


#endif //SEARCH_ALG_GRAPH_H
