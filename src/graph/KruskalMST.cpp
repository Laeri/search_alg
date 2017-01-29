//
// Created by laeri on 1/28/17.
//

#include <iostream>
#include "KruskalMST.h"
#include "DisjointSet.h"

void KruskalMST::build(Graph &graph, graph::Vertex &root) {


    std::vector<TmpEdge> edges;
    std::vector<graph::Vertex*> tmp_vertices(graph.get_vertices().begin(), graph.get_vertices().end());
    std::random_shuffle(tmp_vertices.begin(), tmp_vertices.end());
    for (auto &vertex: tmp_vertices) {
        std::random_shuffle(graph.adj_of(vertex).begin(), graph.adj_of(vertex).end());
        for (auto &adj: graph.adj_of(vertex)) {
            TmpEdge tmpEdge;
            tmpEdge.v1 = vertex;
            tmpEdge.v2 = graph.get_vertices()[adj.first];
            tmpEdge.cost = adj.second;
            edges.push_back(tmpEdge);

        }
        graph.adj_of(vertex).clear();
    }

    std::sort(edges.begin(), edges.end(), edge_compare());

    DisjointSet set = DisjointSet(graph.get_vertices());
    for (auto &edge: edges) {
        if (!set.same_set(edge.v1, edge.v2)) {
            graph.bi_connect(edge.v1, edge.v2, edge.cost);
            edge.v1->type = graph::Type ::maze_field;
            edge.v2->type = graph::Type ::maze_field;
            set.merge(edge.v1, edge.v2);
        }
    }

    for(auto &vertex: graph.get_vertices()){

    }
}