#include <stdio.h>
#include <stdlib.h>
#include "cost.h"
#include "edge_count.h"
#include "generate_graph.h"
#include "insert_edge.h"
#include "print_graph.h"
#include "structures.h"
#include "vertex_count.h"
#include "splay.h"
int p;
int main()
{
    int source = 1,i;//initializing vertex 1 as the starting vertex
    int v = vertex_count();// get the vertex count
    long long int e = edge_count();// get the edge count
    printf("No of Vertex = %d\n",v);
    printf("No of edge = %lli\n",e);
    long long int **edge_cost = cost(v);//initialize the edges to -1 in edge_cost adjacency matrix
    struct Graph* graph=generate_graph(edge_cost);//creates graph and returns the adjacency list to graph and also updates the edges
    long long int dist[v+1];
    int prev[v+1],color[v+1];
    for(int i=0;i<=v;i++)//Initlialization loop
    {
        dist[i] = e+10+i;
        prev[i] = -1;
        color[i] = 0;
    }
    dist[source] = 0;// assign dist 0 to source vertex
    for(i=2;i<=v;i++)//Initializing nodes
    {
        insert_node(i,e+i);
    }
    insert_node(1,0);
    int const n=v;//a constant to store number of vertices
    while(v>0)
    {
        int u = del_min();// delete min node from min heap

        color[u] = 1;//node already added to MST
        struct AdjListNode* temp = graph->array[u].head;//get the adjacencies of node u
        while(temp)
        {
            int i = temp->des;
            if(edge_cost[u][i]!=-1 && color[i]!=1 && dist[i]>edge_cost[u][i])
            {
                int key=dist[i];
                dist[i]=edge_cost[u][i];
                prev[i]=u;
                reduce_key(key,dist[i],i);
            }
            temp=temp->next;
        }
        v--;
    }
    printf("\nMST EDGES\n");
    long long int sum=0;
    for(i=1;i<n;i++)
    {
        printf("%d->%d,%d\n",i,i+1,prev[i+1]);
        sum+=dist[i+1];
    }
    printf("\nTOTAL MST COST = %lli\n",sum);
    return 0;
}
