cmake_minimum_required(VERSION 3.6)
project(search_alg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/graph/Graph.cpp src/graph/Graph.h src/graph/Vertex.cpp src/graph/Vertex.h src/graph/shortest_path/Dijkstra.h src/graph/shortest_path/Dijkstra.cpp src/graph/shortest_path/BellmanFord.h src/graph/shortest_path/BellmanFord.cpp)
add_executable(search_alg ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

