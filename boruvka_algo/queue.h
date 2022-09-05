#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "structures.h"

struct heap_node
{
    int u;
    int v;
    int key;
    int type;
    int sval;
    struct heap_node *left;
    struct heap_node *right;
};

struct Qnode
{
    struct heap_node *root;
    struct Qnode* left;
    struct Qnode* right;

};

struct Qnode* Qroot=NULL;

struct Qlist
{
    int V;
    struct Qnode* array;
};

struct Qlist* qlist(int v);
void create_qnode(int **edge_cost,struct Graph* graph,int v);
struct heap_node* insert_heap(int u,int v,int key,struct heap_node* temp);
struct heap_node* meld(struct heap_node* h1,struct heap_node* h2);
//struct Qnode* insert_queue(struct Qnode *new_node,struct heap_node *root);

struct heap_node* insert_queue(struct Qnode *new_node,struct heap_node *root);

struct Qlist* qlist(int v)
{
    struct Qlist* Q =(struct Qlist*)malloc(sizeof(struct Qlist));
    Q->V=v;
    Q->array=(struct Qnode*)malloc((v+1)*sizeof(struct Qnode));
    for(int i=0;i<=v;i++)
    {
        Q->array[i].root=NULL;
    }
    return Q;
};

void create_qnode(int **edge_cost,struct Graph* graph,int v)
{
    struct Qlist* Q=qlist(v);
    for(int i=1;i<=v;i++)
    {
        struct AdjListNode* temp = graph->array[i].head;
        while(temp)
        {
            int u=i;
            int v=temp->des;
            int key=edge_cost[u][v];
            Q->array[i].root=insert_heap(u,v,key,Q->array[i].root);
            temp=temp->next;
        }
    }


    for(int i=1;i<=v;i++)
    {
        struct Qnode *new_node=(struct Qnode*)malloc(sizeof(struct Qnode));
        Q->array[i].root=insert_queue(new_node,NULL);
    }

}

struct heap_node* insert_queue(struct Qnode *new_node,struct heap_node *root)
{
    new_node->root=root;
    if(Qroot==NULL)
    {
    }
};

struct heap_node* insert_heap(int u,int v,int key,struct heap_node* temp)
{
    struct heap_node *new_node=(struct heap_node*)malloc(sizeof(struct heap_node));
    new_node->u=u;
    new_node->v=v;
    new_node->key=key;
    new_node->sval=0;
    new_node->type=1;
    new_node->left=NULL;
    new_node->right=NULL;
    return meld(temp,new_node);
};

struct heap_node* meld(struct heap_node* h1,struct heap_node* h2)
{
    if(h1==NULL)
        return h2;
    if(h2==NULL)
        return h1;
    struct heap_node *new_node=(struct heap_node*)malloc(sizeof(struct heap_node));
    new_node->type=1;
    if(h1->sval<h2->sval)
    {
        new_node->right=h1;
        new_node->left=h2;
    }
    else
    {
        new_node->right=h2;
        new_node->left=h1;
    }
    new_node->sval=new_node->right->sval+1;
    return new_node;
};

#endif // QUEUE_H_INCLUDED
