//
// Created by laeri on 1/27/17.
//

#ifndef SEARCH_ALG_GRAPHSEARCH_H
#define SEARCH_ALG_GRAPHSEARCH_H


#include <mutex>
#include <condition_variable>
#include "../Graph.h"


enum class Event {
    Current, Relax
};

struct compare {
    bool operator()(const graph::Vertex* u, const graph::Vertex* v){
        // > because first element in vector shall be minimum element when using std::sort
        return u->distance < v->distance;
    }
};

typedef std::function<void(Event, graph::Vertex *)> Function;

class GraphSearch {
private:
    Function on_event = nullptr;
    int relax_steps = 0;

public:

    GraphSearch();

    GraphSearch(Function on_event);

    std::mutex mutex;
    std::condition_variable var;
    std::unique_lock<std::mutex> lock;
    bool locked = false;
    bool *lock_step = nullptr;

    virtual void search(Graph &graph, graph::Vertex &src, graph::Vertex &goal)= 0;

    virtual void relax(graph::Vertex &u, graph::Vertex &v, float weight);

    virtual void init_single_src(Graph &graph, graph::Vertex &src);

    virtual void callback(Event event, graph::Vertex *vertex);
};


#endif //SEARCH_ALG_GRAPHSEARCH_H
