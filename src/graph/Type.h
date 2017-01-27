//
// Created by laeri on 1/25/17.
//

#ifndef SEARCH_ALG_TYPE_H
#define SEARCH_ALG_TYPE_H


namespace graph {
    enum class Type {
        start, end, free, being_processed, on_path, occupied, maze_field, relaxed
    };
}
#endif //SEARCH_ALG_TYPE_H
