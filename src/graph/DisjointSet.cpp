//
// Created by laeri on 1/28/17.
//

#include "DisjointSet.h"

DisjointSet::DisjointSet(std::vector<graph::Vertex *> &vertices) {
}

void DisjointSet::merge(graph::Vertex *u, graph::Vertex *v) {
    find(u)->pred = find(v);
}

graph::Vertex *DisjointSet::find(graph::Vertex *u) {
    graph::Vertex *parent = u;
    while (parent->pred) {
        parent = parent->pred;
    }
    return parent;
}

bool DisjointSet::same_set(graph::Vertex *u, graph::Vertex *v) {
    return find(u) == find(v);
}