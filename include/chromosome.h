//
// Created by Saaketh Vangati on 12/7/20.
//

#ifndef TSPGA_CHROMOSOME_H
#define TSPGA_CHROMOSOME_H

#include <stdlib.h>

typedef struct
{
    float distance;
    int *cities;
} chromosome;

void initialize_chromosome(chromosome * const p_chromosome, int num_cities);
void randomize_chromosome(chromosome * const p_chromosome, int num_cities);
void crossover_chromosome(chromosome * const p_chromosome, chromosome * const a, chromosome * const b, int num_cities);
void mutated_chromosome(chromosome * const p_chromosome, const chromosome * const a, int num_cities);
int compare_chromosomes(const void * const a, const void * const b);
void free_chromosome(chromosome * const p_chromosome);

#endif //TSPGA_CHROMOSOME_H
