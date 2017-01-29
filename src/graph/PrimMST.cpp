//
// Created by laeri on 1/29/17.
//

#include <map>
#include "PrimMST.h"
#include "shortest_path/GraphSearch.h"
#include "DisjointSet.h"

void PrimMST::build(Graph &graph, graph::Vertex &root) {

    std::map<graph::Vertex*, Connection> min_edge;
    for(auto &v: graph.get_vertices()){
        // distance is value of minimum edge, not distance to root!
        v->distance = std::numeric_limits<float>::max();
    }
    std::vector<graph::Vertex*> v_list = std::vector<graph::Vertex*>(graph.get_vertices().begin(), graph.get_vertices().end());
    DisjointSet set = DisjointSet(graph.get_vertices());
    while(!v_list.empty()){
        std::sort(v_list.begin(), v_list.end(), compare_vertex());
        graph::Vertex* vertex = *v_list.begin();
        v_list.erase(v_list.begin());

        for(auto &adj: graph.adj_of(vertex)){
            graph::Vertex* connected = graph.get_vertices()[adj.first];
            if(!set.same_set(vertex, connected) &&adj.second < connected->distance){
                connected->distance = adj.second;
                Connection t;
                t.from=vertex;
                t.cost = adj.second;
                min_edge[connected] = t;
            }
        }

            auto edge = min_edge[vertex];
            vertex->pred = edge.from;

    }
    for(auto &v: graph.get_vertices()){
        graph.adj_of(v).clear();
    }

    for(auto &edge_val: min_edge){
        graph::Vertex* to = edge_val.first;
        graph::Vertex* from = edge_val.second.from;
        float cost = edge_val.second.cost;
       graph.bi_connect(from, to, cost);
    }

}