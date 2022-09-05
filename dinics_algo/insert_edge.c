#include "insert_edge.h"
#include <stdlib.h>

void insert_edge(struct Graph* Graph,int source,int des)
{
    struct AdjListNode* newNode = newAdjListNode(des);
    newNode->next=Graph->array[source].head;
    Graph->array[source].head=newNode;
}

struct AdjListNode* newAdjListNode(int des)
{
    struct AdjListNode* newNode =(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->des = des;
    newNode->next = NULL;
    return newNode;
}

struct Graph* create_graph(int v)
{
    struct Graph* graph =(struct Graph*)malloc(sizeof(struct Graph));
    graph->V=v;
    graph->array=(struct AdjList*)malloc((v+1)*sizeof(struct AdjList));
    for(int i=0;i<=v;i++)
    {
        graph->array[i].head=NULL;
    }
    return graph;
};
