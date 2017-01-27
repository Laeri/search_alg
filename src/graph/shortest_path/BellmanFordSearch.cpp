//
// Created by laeri on 1/27/17.
//

#include <thread>
#include "BellmanFordSearch.h"

void BellmanFordSearch::search(Graph &graph, graph::Vertex &src, graph::Vertex &goal) {
    init_single_src(graph, src);

    Adjacency &adj = graph.get_adjacencies();
    for(int i = 0; i < graph.get_vertices().size()-1; i++){
        int v1 = 0;
        for(auto &a: adj){
            for(auto &pair: a){
                graph::Vertex * u =  graph.get_vertices()[v1];
                graph::Vertex * v = graph.get_vertices()[pair.first];
                relax(*u,*v,pair.second);
            }
            v1++;
        }
    }

    int v1 = 0;
    for(auto &a: adj){
        for(auto &pair: a){
            graph::Vertex * u =  graph.get_vertices()[v1];
            graph::Vertex * v = graph.get_vertices()[pair.first];
            if(u->distance + pair.second < v->distance){
                throw std::runtime_error("Graph contains negative cycle! Bellman-Ford Algorithm can not be used.");
            }
        }
        v1++;
    }
}
