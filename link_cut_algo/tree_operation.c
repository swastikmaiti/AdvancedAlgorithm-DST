#include <stdlib.h>
#include <stdio.h>
#include "tree_operation.h"

int tr;

struct vertex* maketree(int x)
{
    struct vertex *new_node=(struct vertex*)malloc(sizeof(struct vertex));
    new_node->vertex=x;
    new_node->dcost=0;
    new_node->dmin=0;
    new_node->lc=NULL;
    new_node->rc=NULL;
    new_node->parent=NULL;
    new_node->successor=NULL;
    return new_node;
};

struct vertex* find_root(struct vertex *v)
{
    splay(v);
    while(v->rc!=NULL)
        v=v->rc;
    splay(v);
    return v;
};

struct vertex* find_min(struct vertex *v)
{
    splay(v);
    int pass=0;
    do
    {
        pass=0;
        if(v->rc!=NULL && (v->rc->dcost-v->rc->dmin+v->dmin==0))
        {
            v=v->rc;
            pass+=1;
        }
        if(v->rc==NULL || (v->rc!=NULL && (v->rc->dcost-v->rc->dmin+v->dmin>0)))
        {
            if(v->dmin>0 && v->lc!=NULL)
            {
                v=v->lc;
                pass+=1;
            }
        }

    }while(pass!=0);

    normal_splay(v);
    //splay(v);
    //printf("\nfind_min exit V=%d\n",v->vertex);
    //print_all2();
    //scanf("%d",&tr);
    return v;
};

void add_cost(struct vertex *v,int x)
{
    splay(v);
    v->dcost=v->dcost+x;
    if(v->lc!=NULL)
        v->lc->dcost-=x;
};

void link(struct vertex *v,struct vertex *w)
{
    splay(v);
    splay(w);
    v->successor=w;
}

void cut(struct vertex *v)
{
    splay(v);
    if(v->rc!=NULL)
    {
        v->rc->dcost+=v->dcost;
        v->rc->parent=NULL;
        v->rc=NULL;
    }
}

int find_cost(struct vertex *v)
{
    splay(v);
    return v->dcost;
};


void print_path(struct vertex *v,int path[],int *t)
{
    if(v->lc!=NULL)
        print_path(v->lc,path,t);
    printf("%d,",v->vertex);
    //printf("\ninsertinf %d at %d\n",v->vertex,*t);
    path[*t]=v->vertex;
    *t=*t+1;
    if(v->rc!=NULL)
        print_path(v->rc,path,t);
    path[*t]=0;
}

