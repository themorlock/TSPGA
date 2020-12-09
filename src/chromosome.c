//
// Created by Saaketh Vangati on 12/7/20.
//

#include "../include/chromosome.h"

#include <string.h>

#include "../include/random.h"

void initialize_chromosome(chromosome * const p_chromosome, int num_cities)
{
    p_chromosome->cities = (int *) malloc(num_cities * sizeof(int));
    for(int i = 0; i < num_cities; ++i)
    {
        p_chromosome->cities[i] = i;
    }
    randomize_chromosome(p_chromosome, num_cities);
}

void randomize_chromosome(chromosome * const p_chromosome, int num_cities)
{
    for(int i = num_cities - 1; i >= 0; --i)
    {
        int j = rand_int() % (i + 1);

        int temp = p_chromosome->cities[i];
        p_chromosome->cities[i] = p_chromosome->cities[j];
        p_chromosome->cities[j] = temp;
    }
}

void crossover_chromosome(chromosome * const p_chromosome, chromosome * const a, chromosome * const b, int num_cities)
{
    memcpy(p_chromosome->cities, b->cities, num_cities * sizeof(int));
    int start_idx = rand_int() % (num_cities - 1);
    int end_idx = start_idx + 1 + rand_int() % (num_cities - 1 - start_idx);
    for(int i = 0; i < num_cities; ++i)
    {
        for(int j = start_idx; j <= end_idx; ++j)
        {
            if(p_chromosome->cities[i] == b->cities[j])
            {
                p_chromosome->cities[i] = -1;
            }
        }
    }
    int count = 0;
    for(int i = 0; i < num_cities; ++i)
    {
        if(p_chromosome->cities[i] != -1)
        {
            int temp = p_chromosome->cities[count];
            p_chromosome->cities[count] = p_chromosome->cities[i];
            p_chromosome->cities[i] = temp;
            ++count;
        }
    }
    memcpy(p_chromosome->cities + (num_cities - (end_idx - start_idx + 1))
           , b->cities + start_idx, (end_idx - start_idx + 1) * sizeof(int));
}

void mutated_chromosome(chromosome * const p_chromosome, const chromosome * const a, int num_cities)
{
    memcpy(p_chromosome->cities, a->cities, num_cities * sizeof(int));
    int start_idx = rand_int() % (num_cities - 1);
    int end_idx = start_idx + 1 + rand_int() % (num_cities - 1 - start_idx);
    for(int i = 0; i <= (end_idx - start_idx); ++i)
    {
        int temp = p_chromosome->cities[start_idx + i];
        p_chromosome->cities[start_idx + i] = p_chromosome->cities[end_idx - i];
        p_chromosome->cities[end_idx - i] = temp;
    }
}

int compare_chromosomes(const void * const a, const void * const b)
{
    if(((chromosome *) b)->distance > ((chromosome *) a)->distance)
    {
        return 1;
    }
    else if(((chromosome *) b)->distance < ((chromosome *) a)->distance)
    {
        return -1;
    }
    return 0;
}

void free_chromosome(chromosome * const p_chromosome)
{
    free(p_chromosome->cities);
}
