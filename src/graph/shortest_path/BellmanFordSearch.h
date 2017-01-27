//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_BELLMANFORDSEARCH_H
#define SEARCH_ALG_BELLMANFORDSEARCH_H


#include "GraphSearch.h"

class BellmanFordSearch: public GraphSearch {
public:
    void search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) override;
};


#endif //SEARCH_ALG_BELLMANFORDSEARCH_H
