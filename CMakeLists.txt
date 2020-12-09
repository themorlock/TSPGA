cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_STANDARD 99)

project(TSPGA C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(TSPGA src/main.c src/chromosome.c include/chromosome.h src/random.c include/random.h src/tsp.c include/tsp.h src/graph.c include/graph.h)
target_link_libraries(TSPGA ${SDL2_LIBRARIES})