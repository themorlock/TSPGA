//
// Created by Saaketh Vangati on 12/8/20.
//

#include "../include/tsp.h"

#include <math.h>

#include "../include/random.h"

void initialize_city(city * const p_city, int board_width, int board_height)
{
    p_city->x = rand_int() % board_width;
    p_city->y = rand_int() % board_height;
}

float compute_city_distance(const city * const p_city_1, const city * const p_city_2)
{
    return sqrtf(powf(p_city_1->x - p_city_2->x, 2.0f) + powf(p_city_1->y - p_city_2->y, 2.0f));
}

void initialize_tsp(tsp * const p_tsp, int board_width, int board_height, int num_cities, int k, float graph_screen_proportion)
{
    p_tsp->board_width = board_width;
    p_tsp->board_height = board_height;
    p_tsp->num_cities = num_cities;
    p_tsp->cities = (city *) malloc(num_cities * sizeof(city));
    for(int i = 0; i < num_cities; ++i)
    {
        initialize_city(&p_tsp->cities[i], board_width, board_height);
    }
    p_tsp->city_distances = (float **) malloc(num_cities * sizeof(float *));
    for(int i = 0; i < num_cities; ++i)
    {
        p_tsp->city_distances[i] = (float *) malloc(num_cities * sizeof(float));
        for(int j = 0; j < num_cities; ++j)
        {
            p_tsp->city_distances[i][j] = compute_city_distance(&p_tsp->cities[i], &p_tsp->cities[j]);
        }
    }
    p_tsp->k = k;
    p_tsp->chromosomes = (chromosome *) malloc(2 * k * sizeof(chromosome));
    for(int i = 0; i < 2 * k; ++i)
    {
        initialize_chromosome(&p_tsp->chromosomes[i], num_cities);
    }
    p_tsp->graph_screen_proportion = graph_screen_proportion;
    initialize_graph(&p_tsp->distance_graph);
}

void update_chromosomes(tsp * const p_tsp)
{
    for(int i = 0; i < p_tsp->k / 2; ++i)
    {
        int a_idx = p_tsp->k + rand_int() % p_tsp->k;
        int b_idx = p_tsp->k + rand_int() % p_tsp->k;
        crossover_chromosome(&p_tsp->chromosomes[i], &p_tsp->chromosomes[a_idx], &p_tsp->chromosomes[b_idx]
                             , p_tsp->num_cities);
    }
    for(int i = p_tsp->k / 2; i < 3 * p_tsp->k / 2; ++i)
    {
        int a_idx = p_tsp->k + rand_int() % p_tsp->k;
        mutated_chromosome(&p_tsp->chromosomes[i], &p_tsp->chromosomes[a_idx], p_tsp->num_cities);
    }
    for(int i = 3 * p_tsp->k / 2; i < p_tsp->k; ++i)
    {
        randomize_chromosome(&p_tsp->chromosomes[i], p_tsp->num_cities);
    }
}

void evaluate_chromosomes(tsp * const p_tsp)
{
    for(int i = 0; i < 2 * p_tsp->k; ++i)
    {
        float distance = 0.0f;
        for(int j = 0; j < p_tsp->num_cities - 1; ++j)
        {
            distance += p_tsp->city_distances[p_tsp->chromosomes[i].cities[j]][p_tsp->chromosomes[i].cities[j + 1]];
        }
        distance += p_tsp->city_distances[p_tsp->chromosomes[i].cities[p_tsp->num_cities - 1]][p_tsp->chromosomes[i].cities[0]];
        p_tsp->chromosomes[i].distance = distance;
    }
}

void rank_chromosomes(tsp * const p_tsp)
{
    qsort(p_tsp->chromosomes, 2 * p_tsp->k, sizeof(chromosome), compare_chromosomes);
}

void update_tsp(tsp * const p_tsp)
{
    update_chromosomes(p_tsp);
    evaluate_chromosomes(p_tsp);
    rank_chromosomes(p_tsp);
    add_value_to_graph(&p_tsp->distance_graph, p_tsp->chromosomes[2 * p_tsp->k - 1].distance);
}

void get_unit_dimensions(const SDL_Window * const window, int board_width, int board_height, int *unit_width, int *unit_height)
{
    int screen_width, screen_height;
    SDL_GetRendererOutputSize(SDL_GetRenderer(window), &screen_width, &screen_height);
    *unit_width = screen_width / board_width;
    *unit_height = screen_height / board_height;
}

void draw_tsp(const tsp * const p_tsp, SDL_Window * const window)
{
    int unit_width, unit_height;
    get_unit_dimensions(window, p_tsp->board_width, p_tsp->board_height, &unit_width, &unit_height);
    SDL_SetRenderDrawColor(SDL_GetRenderer(window), 0xFF, 0x0, 0x0, 0xFF);
    for(int i = 0; i < p_tsp->num_cities; ++i)
    {
        SDL_Rect rect = {p_tsp->cities[i].x * unit_width, p_tsp->cities[i].y * unit_height, unit_width, unit_height};
        SDL_RenderFillRect(SDL_GetRenderer(window), &rect);
    }
    SDL_SetRenderDrawColor(SDL_GetRenderer(window), 0xFF, 0xFF, 0xFF, 0xFF);
    for(int i = 0; i < p_tsp->num_cities - 1; ++i)
    {
        SDL_RenderDrawLine(SDL_GetRenderer(window), p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[i]].x
        * unit_width, p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[i]].y * unit_height
        , p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[i + 1]].x * unit_width
        , p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[i + 1]].y * unit_height);
    }
    SDL_RenderDrawLine(SDL_GetRenderer(window)
                       , p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[p_tsp->num_cities - 1]].x
                       * unit_width, p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[p_tsp->num_cities - 1]].y
                       * unit_height, p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[0]].x * unit_width
                       , p_tsp->cities[p_tsp->chromosomes[2 * p_tsp->k - 1].cities[0]].y * unit_height);
    float point_gap = (float) p_tsp->board_width / (float) p_tsp->distance_graph.data_size;
    float max_point_height = p_tsp->graph_screen_proportion * (float) p_tsp->board_height;
    float max_distance = get_max_value_from_graph(&p_tsp->distance_graph);
    SDL_SetRenderDrawColor(SDL_GetRenderer(window), 0x0, 0xFF, 0x00, 0xFF);
    for(int i = 0; i < p_tsp->distance_graph.data_size - 1; ++i)
    {
        SDL_RenderDrawLineF(SDL_GetRenderer(window), i * point_gap * unit_width
                            , (p_tsp->board_height - (max_point_height * (p_tsp->distance_graph.data[i] / max_distance)))
                            * unit_height, (i + 1) * point_gap * unit_width
                            , (p_tsp->board_height - (max_point_height * (p_tsp->distance_graph.data[i + 1] / max_distance)))
                            * unit_height);
    }
}

void save_tsp(const tsp * const p_tsp)
{
    char file_name[40];
    struct tm *time_now;
    time_t now = time(NULL);
    time_now = gmtime(&now);
    strftime(file_name, sizeof(file_name), "TSPGA_%Y-%m-%d_%H-%M-%S.csv", time_now);
    FILE *fp = fopen(file_name, "w");
    fprintf(fp, "Generation Number, Shortest Distance\n");
    for(int i = 0; i < p_tsp->distance_graph.data_size; ++i)
    {
        fprintf(fp, "%d, %f\n", (i + 1), p_tsp->distance_graph.data[i]);
    }
    fclose(fp);
}

void free_tsp(tsp * const p_tsp)
{
    free(p_tsp->cities);
    for(int i = 0; i < p_tsp->num_cities; ++i)
    {
        free(p_tsp->city_distances[i]);
    }
    free(p_tsp->city_distances);
    for(int i = 0; i < p_tsp->k; ++i)
    {
        free_chromosome(&p_tsp->chromosomes[i]);
    }
    free(p_tsp->chromosomes);
    free_graph(&p_tsp->distance_graph);
}
