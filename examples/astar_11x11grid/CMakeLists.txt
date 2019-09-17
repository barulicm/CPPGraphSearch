cmake_minimum_required(VERSION 3.12)

project("GraphSearch-Example-astar-11x11grid")

find_package(GraphSearch CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} GraphSearch::GraphSearch)
