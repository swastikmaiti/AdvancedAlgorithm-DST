#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include<stdlib.h>

struct node
{
    int vertex;
    struct node *prev;
};
typedef struct node node;

struct node* head=NULL;

void push(int v)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->vertex=v;
    temp->prev=NULL;
    if(head==NULL)
    {
        head = temp;
    }
    else
    {
        temp->prev = head;
        head = temp;
    }
}

int pop()
{
    if(head==NULL)
    {
        return -1;
    }
    else
    {
        node *temp = head;
        int item = head->vertex;
        head = head->prev;
        free(temp);
        temp = NULL;
        return item;
    }
}

int top()
{
    if(head==NULL)
        return -1;
    else
        return head->vertex;
}

#endif // STACK_H_INCLUDED
