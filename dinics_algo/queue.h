#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

struct Qnode
{
    int vertex;
    struct Qnode *next;
};

void insert_Q(int v);
int delete_Q();
int isEmpty();
void print();

#endif // QUEUE_H_INCLUDED
