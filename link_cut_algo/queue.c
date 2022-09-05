#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


struct Qnode *front=NULL;
struct Qnode *tail=NULL;

int x;


void insert_Q(int v)
{
    struct Qnode *new_node=(struct Qnode*)malloc(sizeof(struct Qnode));
    new_node->vertex=v;
    new_node->next=NULL;
    if(front==NULL)
    {
        front=new_node;
        tail=new_node;
    }
    else
    {
        tail->next=new_node;
        tail=new_node;
    }
}

int delete_Q()
{
    int item=-1;
    if(front==NULL)
    {
        printf("\nQueue Empty\n");
        return -1;
    }
    else
    {
        struct Qnode *temp=front;
        item=front->vertex;
        front=front->next;
        if(front==NULL)
            tail=NULL;
        free(temp);
    }
    return item;
}

int isEmpty()
{
    if(front==NULL)
        return 1;
    else
        return 0;
}

