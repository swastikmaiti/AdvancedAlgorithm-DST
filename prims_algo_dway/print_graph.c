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
