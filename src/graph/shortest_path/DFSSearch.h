//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_DFSSEARCH_H
#define SEARCH_ALG_DFSSEARCH_H


#include "GraphSearch.h"

class DFSSearch: public GraphSearch{
public:
    void search(Graph &graph, graph::Vertex &src) override;
};


#endif //SEARCH_ALG_DFSSEARCH_H
