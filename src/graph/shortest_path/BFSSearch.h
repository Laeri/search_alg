//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_BFSSEARCH_H
#define SEARCH_ALG_BFSSEARCH_H


#include "GraphSearch.h"

class BFSSearch: public GraphSearch {
public:
    void search(Graph &graph, graph::Vertex &src) override;
};


#endif //SEARCH_ALG_BFSSEARCH_H
