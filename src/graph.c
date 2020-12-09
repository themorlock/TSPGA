//
// Created by Saaketh Vangati on 12/9/20.
//

#include "../include/graph.h"

#include <stdlib.h>

void initialize_graph(graph * const p_graph)
{
    p_graph->data_size = 0;
    p_graph->data = (float *) malloc(0);
}

void add_value_to_graph(graph * const p_graph, float value)
{
    p_graph->data = (float *) realloc(p_graph->data, (p_graph->data_size + 1) * sizeof(float));
    p_graph->data[p_graph->data_size] = value;
    p_graph->data_size += 1;
}

float get_max_value_from_graph(const graph * const p_graph)
{
    float max = p_graph->data[0];
    for(int i = 1; i < p_graph->data_size; ++i)
    {
        if(p_graph->data[i] > max)
        {
            max = p_graph->data[i];
        }
    }
    return max;
}

void free_graph(graph * const p_graph)
{
    free(p_graph->data);
}
