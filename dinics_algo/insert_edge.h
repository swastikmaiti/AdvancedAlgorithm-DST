#ifndef INSERT_EDGE_H_INCLUDED
#define INSERT_EDGE_H_INCLUDED
#include "structures.h"

void insert_edge(struct Graph*,int source,int des);
struct AdjListNode* newAdjListNode(int dest);
struct Graph* create_graph(int v);


#endif // INSERT_EDGE_H_INCLUDED
