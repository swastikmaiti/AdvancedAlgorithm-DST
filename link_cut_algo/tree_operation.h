#ifndef TREE_OPERATION_H_INCLUDED
#define TREE_OPERATION_H_INCLUDED
#include "splay.h"

int cal_dmin(struct vertex *v);
void print_path(struct vertex *v,int path[],int *t);
void print_path2(struct vertex *v);

struct vertex* maketree(int x);
struct vertex* find_root(struct vertex *v);
struct vertex* find_min(struct vertex *v);
void add_cost(struct vertex *v,int x);
void link(struct vertex *v,struct vertex *w);
void cut(struct vertex *v);
int find_cost(struct vertex *v);


#endif // TREE_OPERATION_H_INCLUDED
