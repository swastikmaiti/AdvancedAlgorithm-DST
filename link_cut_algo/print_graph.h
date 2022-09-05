#ifndef PRINT_GRAPH_H_INCLUDED
#define PRINT_GRAPH_H_INCLUDED
#include <stdio.h>
#include "structures.h"

void print_graph(struct Graph* graph);
void print_aug_graph(struct Graph* graph,long long int **augmenting_edge_cost);

#endif // PRINT_GRAPH_H_INCLUDED
