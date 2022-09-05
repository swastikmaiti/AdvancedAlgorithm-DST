#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generate_graph.h"
#include "level_graph.h"
#include "vertex_count.h"
#include "queue.h"
#include "insert_edge.h"

int a;

struct Graph* generate_level_graph(struct Graph* graph,long long int **edge_cost,long long int **level_cost)
{
    int v = vertex_count();
    int level[v+1];
    struct Graph* level_graph = create_graph(v);
    int visited[v+1];
    visited[1]=1;
    int u=1;
    int l=1;
    for(int i=1;i<=v;i++)
    {
        visited[i]=0;
        level[i]=-1;
    }
    while(true)
    {
        struct AdjListNode* temp = graph->array[u].head;
        while(temp)
        {
            int v=temp->des;
            if(edge_cost[u][v]>0 && visited[v]==0)
            {
                visited[v]=1;
                insert_Q(v);
                level[v]=l;
                insert_edge(level_graph,u,v);
                level_cost[u][v]=edge_cost[u][v];
            }
            else
            {
                if(edge_cost[u][v]>0 && level[v]>level[u])
                {
                    insert_edge(level_graph,u,v);
                    level_cost[u][v]=edge_cost[u][v];
                    //printf("\ninserting edge %d,%d\n",u,v);
                    //scanf("%d",&a);
                }
            }
            //printf("\n u,v=%d,%d\n",u,v);
            temp=temp->next;
        }
        //print();
        //scanf("%d",&a);
        if(isEmpty())
            break;
        else
        {
            l++;
            u=delete_Q();
        }
    }
    return level_graph;
};
