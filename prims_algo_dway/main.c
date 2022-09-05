#include <stdio.h>
#include <stdlib.h>
#include "adjust.h"
#include "build_heap.h"
#include "cost.h"
#include "edge_count.h"
#include "generate_graph.h"
#include "insert_edge.h"
#include "print_graph.h"
#include "structure.h"
#include "structures.h"
#include "vertex_count.h"
#include "del_min.h"
#include "reduce_key.h"
int main()
{
    int source = 1;//initializing vertex 1 as the starting vertex
    long long int v = vertex_count();// get the vertex count
    long long int e = edge_count();// get the edge count
    printf("No of Vertex = %lli\n",v);
    printf("No of edge = %lli\n",e);
    int d = e/v;
    long long int **edge_cost = cost(v);//initialize the edges to -1 in edge cost adjacency matrix
    struct Graph* graph=generate_graph(edge_cost);//creates graph and returns the adjacency list to graph and also updates the edges
    long long int dist[v+1];
    int prev[v+1],color[v+1],vertex_index[v+1];
    long long int i;
    for(i=0;i<=v;i++)//Initlialization loop
    {
        dist[i] = e+10;
        prev[i] = -1;
        color[i] = 0;
    }
    dist[source] = 0;// assign dist 0 to source vertex
    node array[v];// array to store nodes of heap
    for(i=0;i<v;i++)//Initializing nodes
    {
        vertex_index[i+1] = i;
        array[i].vertex = i+1;
        array[i].key = e+10;
    }
    array[vertex_index[source]].key=0;//assign dist 0 to node containing vertex 1
    build_heap(array,v,d,vertex_index);//build min heap where d = 3
    int const n=v;//a constant to store number of vertices
    while(v>0)
    {
        int u = del_min(array,&v,vertex_index,d);// delete min node from min heap
        color[u] = 1;//node already added to MST
        struct AdjListNode* temp = graph->array[u].head;//get the adjacencies of node u
        while(temp)//loop through all adjacencies of vertex u
        {
            int i = temp->des;
            if(edge_cost[u][i]!=-1 && color[i]!=1 && dist[i]>edge_cost[u][i])
            {
                dist[i]=edge_cost[u][i];
                prev[i]=u;
                reduce_key(array,v,vertex_index[i],dist[i],d,vertex_index);
            }
            temp=temp->next;
        }
    }
    printf("\nMST EDGES\n");
    long long int sum=0;
    for(i=1;i<n;i++)
    {
        sum+=dist[i+1];
        printf("%lli->%lli %d\n",i,i+1,prev[i+1]);
    }
    printf("\nTOTAL MST COST = %lli\n",sum);
    return 0;
}
