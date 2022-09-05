#include "print_graph.h"

void print_graph(struct Graph* graph)
{
    int v = graph->V;
    for(int i=1;i<=v;i++)
    {
        printf("vertex %d ->[",i);
        struct AdjListNode* temp = graph->array[i].head;
        //printf("\ncheck i = %d\n",i);
        while(temp)
        {
            printf("%d,",temp->des);
            temp=temp->next;
        }
        printf("]\n");
    }
}

void print_aug_graph(struct Graph* graph,long long int **augmenting_edge_cost)
{
    printf("\n");
    int v = graph->V;
    for(int i=1;i<=v;i++)
    {
        struct AdjListNode* temp = graph->array[i].head;
        //printf("\ncheck i = %d\n",i);
        while(temp && augmenting_edge_cost[i][temp->des]>0)
        {
            printf("edge (%d ,%d) flow=%lli\n",i,temp->des,augmenting_edge_cost[i][temp->des]);
            temp=temp->next;
        }
    }
}

