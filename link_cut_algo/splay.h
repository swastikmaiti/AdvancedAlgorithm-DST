#ifndef SPLAY_H_INCLUDED
#define SPLAY_H_INCLUDED

struct vertex
{
    int dcost;
    int dmin;
    int vertex;
    struct vertex *lc;
    struct vertex *rc;
    struct vertex *parent;
    struct vertex *successor;
};

void normal_splay(struct vertex *v);

void splay(struct vertex* v);
void pass1(struct vertex *v);
void right_rotate(struct vertex *w);
void left_rotate(struct vertex *w);
void pass2(struct vertex *v);
void pass3(struct vertex *v);
int maximum(int n1,int n2,int n3);

#endif // SPLAY_H_INCLUDED
