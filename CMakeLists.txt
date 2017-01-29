cmake_minimum_required(VERSION 3.6)
project(search_alg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/graph/Graph.cpp src/graph/Graph.h src/graph/Vertex.cpp src/graph/Vertex.h src/Command.cpp src/Command.h src/DeleteConnectionAction.cpp src/DeleteConnectionAction.h src/GraphDisplay.cpp src/GraphDisplay.h src/graph/Type.h src/GridDrawer.cpp src/GridDrawer.h src/graph/MazeCreator.cpp src/graph/MazeCreator.h src/graph/shortest_path/GraphSearch.cpp src/graph/shortest_path/GraphSearch.h src/graph/shortest_path/DijkstraSearch.cpp src/graph/shortest_path/DijkstraSearch.h src/graph/shortest_path/DFSSearch.cpp src/graph/shortest_path/DFSSearch.h src/graph/shortest_path/BFSSearch.cpp src/graph/shortest_path/BFSSearch.h src/graph/shortest_path/BellmanFordSearch.cpp src/graph/shortest_path/BellmanFordSearch.h src/graph/shortest_path/AStarSearch.cpp src/graph/shortest_path/AStarSearch.h src/graph/shortest_path/GBestFirstSearch.cpp src/graph/shortest_path/GBestFirstSearch.h src/graph/shortest_path/heuristic/Heuristic.cpp src/graph/shortest_path/heuristic/Heuristic.h src/graph/shortest_path/heuristic/EuclideanDistance.cpp src/graph/shortest_path/heuristic/EuclideanDistance.h src/graph/shortest_path/heuristic/ManhattenDistance.cpp src/graph/shortest_path/heuristic/ManhattenDistance.h src/graph/shortest_path/heuristic/DiagonalDistance.cpp src/graph/shortest_path/heuristic/DiagonalDistance.h src/graph/KruskalMST.cpp src/graph/KruskalMST.h src/graph/DisjointSet.cpp src/graph/DisjointSet.h)
add_executable(search_alg ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

