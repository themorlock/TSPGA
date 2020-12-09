//
// Created by Saaketh Vangati on 12/9/20.
//

#ifndef TSPGA_GRAPH_H
#define TSPGA_GRAPH_H

typedef struct
{
    int data_size;
    float *data;
} graph;

void initialize_graph(graph * const p_graph);
void add_value_to_graph(graph * const p_graph, float value);
float get_max_value_from_graph(const graph * const p_graph);
void free_graph(graph * const p_graph);

#endif //TSPGA_GRAPH_H
