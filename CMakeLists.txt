cmake_minimum_required(VERSION 3.6)
project(search_alg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/graph/Graph.cpp src/graph/Graph.h src/graph/Vertex.cpp src/graph/Vertex.h src/graph/shortest_path/Dijkstra.h src/graph/shortest_path/Dijkstra.cpp src/graph/shortest_path/BellmanFord.h src/graph/shortest_path/BellmanFord.cpp src/Command.cpp src/Command.h src/DeleteConnectionAction.cpp src/DeleteConnectionAction.h src/GraphDisplay.cpp src/GraphDisplay.h src/graph/Type.h src/GridDrawer.cpp src/GridDrawer.h src/graph/shortest_path/DFS.h src/graph/shortest_path/DFS.cpp src/graph/shortest_path/AStar.h src/graph/shortest_path/AStar.cpp src/graph/shortest_path/GreedyBestFirstSearch.h src/graph/shortest_path/GreedyBestFirstSearch.cpp src/graph/shortest_path/BFS.h src/graph/shortest_path/BFS.cpp src/graph/MazeCreator.cpp src/graph/MazeCreator.h src/graph/shortest_path/GraphSearch.cpp src/graph/shortest_path/GraphSearch.h src/graph/shortest_path/DijkstraSearch.cpp src/graph/shortest_path/DijkstraSearch.h)
add_executable(search_alg ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

