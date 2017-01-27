//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_GREEDYBFSSEARCH_H
#define SEARCH_ALG_GREEDYBFSSEARCH_H


#include "GraphSearch.h"

struct compare {
    bool operator()(const graph::Vertex* u, const graph::Vertex* v){
        return u->distance > v->distance;
    }
};

class GBestFirstSearch : public GraphSearch {
public:
    void search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) override;
};


#endif //SEARCH_ALG_GREEDYBFSSEARCH_H
