//
// Created by Saaketh Vangati on 12/8/20.
//

#ifndef TSPGA_TSP_H
#define TSPGA_TSP_H

#include <SDL.h>

#include "chromosome.h"
#include "graph.h"

typedef struct
{
    int x, y;
} city;

typedef struct
{
    int board_width, board_height;
    int num_cities;
    city *cities;
    float **city_distances;
    int k;
    chromosome *chromosomes;
    float graph_screen_proportion;
    graph distance_graph;
} tsp;

void initialize_tsp(tsp * const p_tsp, int board_width, int board_height, int num_cities, int k, float graph_screen_proportion);
void update_tsp(tsp * const p_tsp);
void draw_tsp(const tsp * const p_tsp, SDL_Window * const window);
void free_tsp(tsp * const p_tsp);

#endif //TSPGA_TSP_H
