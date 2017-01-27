//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_DIJKSTRASEARCH_H
#define SEARCH_ALG_DIJKSTRASEARCH_H


#include "GraphSearch.h"

class DijkstraSearch: public GraphSearch {
    void search(Graph &graph, graph::Vertex &src) override;
};


#endif //SEARCH_ALG_DIJKSTRASEARCH_H
