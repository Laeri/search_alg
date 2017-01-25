//
// Created by laeri on 1/24/17.
//

#include <chrono>
#include <thread>
#include <iostream>
#include "BellmanFord.h"
#include "Dijkstra.h"

void bellman_ford::bellman_ford(Graph &graph, graph::Vertex &src) {
    Dijkstra::init_single_source(graph, src);

    Adjacency adj = graph.get_adjacencies();
    for(int i = 0; i < graph.get_vertices().size()-1; i++){
        int v1 = 0;
        for(auto &a: adj){
            for(auto &pair: a){
                graph::Vertex * u =  graph.get_vertices()[v1];
                graph::Vertex * v = graph.get_vertices()[pair.first];
                if(v->distance > u->distance+pair.second){
                    graph.get_vertices()[pair.first]->color = sf::Color::Cyan;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                Dijkstra::relax(u,v,pair.second);
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
